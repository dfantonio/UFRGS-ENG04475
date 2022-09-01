#include "comunicaModulo.h"
#include "dados.h"
#include "lcd.h"
#include "navegaMenu.h"
#include "relatorio.h"
#include "serial.h"
#include "setup.h"
#include "teclado.h"
#include "timers.h"
#include "votacao.h"
#include <avr/io.h>
#include <stdlib.h>
#include <string.h>

void autentica(struct Urna *urna);
void menu(struct Urna *urna);
void exibeHora(struct Urna *urna);
void defineHora(struct Urna *urna);
void trocaEstadoUrna(struct Urna *urna);
void auditoria(struct Urna *urna);
void validaEleitor(struct Urna *urna);
void mandaRelatorio(struct Urna *urna);

char TEMP5[5];
char TEMP2[2];

void autentica(struct Urna *urna) {
  int status;

  // Lê o código
  do {
    limpaLCD();
    display((char *)"Insira o codigo:");
    leTeclado(TEMP5, 5, urna);

    status = strcmp(TEMP5, CODIGO_MESARIO) != 0;
    if (status) {
      limpaLCD();
      display((char *)"CODIGO INVALIDO");
      aguardaTecla();
    }
  } while (status); // Repete enquanto o código for inválido

  // Lê a senha
  do {
    limpaLCD();
    display((char *)"Insira a senha:");
    leTeclado(TEMP5, 5, urna, true);

    status = strcmp(TEMP5, SENHA_MESARIO) != 0;
    if (status) {
      limpaLCD();
      display((char *)"SENHA INVALIDA");
      aguardaTecla();
    }
  } while (status);

  urna->proximo = menu;
};

void menu(struct Urna *urna) {
  limpaLCD();
  display((char *)"menu principal:");

  urna->proximo = navegaMenu;
}

void exibeHora(struct Urna *urna) {
  char horario[6];
  limpaLCD();
  display((char *)"Hora atual:");
  formataTempo(horario, urna->tempo);
  display(horario, 1);

  leTeclado(TEMP2, 1, urna);

  urna->proximo = menu;
}

void defineHora(struct Urna *urna) {
  TEMP2[2] = 0;
  long hora, minuto;
  urna->proximo = menu;

  if (urna->estado == encerrado) {
    limpaLCD();
    display((char *)"Nao pode alterar");
    aguardaTecla();
    return;
  }

  // Proteção para que o horário seja válido
  do {
    limpaLCD();
    display((char *)"Digite a hora:");
    leTeclado(TEMP2, 2, urna);
    hora = atoi(TEMP2);
  } while (hora > 23);

  do {
    limpaLCD();
    display((char *)"Digite os min:");
    leTeclado(TEMP2, 2, urna);
    minuto = atoi(TEMP2);
  } while (minuto > 59);

  urna->tempo = hora * 3600 + minuto * 60;
  verificaHorario(urna);
}

// Função que retorna uma string com o estado da urna atual
void populaEstado(char str[], enum Estados estado) {
  switch (estado) {
  case operacional:
    strcpy(str, "operacional");
    break;

  case bloqueado:
    strcpy(str, "bloqueado");
    break;

  case aguardando:
    strcpy(str, "aguardando");
    break;

  case encerrado:
    strcpy(str, "encerrado");
    break;

  default:
    strcpy(str, "ERRO");
    break;
  }
}

void exibeEstado(struct Urna *urna) {
  char estado[12];
  limpaLCD();
  display((char *)"Estado atual:");
  populaEstado(estado, urna->estado);
  display(estado, 1);

  leTeclado(TEMP2, 1, urna);

  urna->proximo = menu;
}

void trocaEstadoUrna(struct Urna *urna) {
  char TEMP[1];
  char linha1[] = "0 - operacional";
  char linha2[] = "1 - bloqueado";
  urna->proximo = menu;

  if (urna->estado == encerrado || urna->estado == aguardando) {
    limpaLCD();
    display((char *)"Nao pode alterar");
    aguardaTecla();
    return;
  }

  do {
    limpaLCD();
    display(linha1, 0);
    display(linha2, 1);

    leTeclado(TEMP, 1, urna);
    if (TEMP[0] == '0') urna->estado = operacional;
    if (TEMP[0] == '1') urna->estado = bloqueado;
  } while (!(TEMP[0] == '0' || TEMP[0] == '1'));
}

void mandaRelatorio(struct Urna *urna) {
  geraRelatorio(urna);
  limpaLCD();
  display((char *)"   relatorio");
  display((char *)"    enviado", 1);
  aguardaTecla();
  urna->proximo = menu;
}

void validaEleitor(struct Urna *urna) {
  char eleitor[] = "00000";
  char resposta[16];
  int status = 0;
  char n[] = "5";
  urna->proximo = menu;

  if (urna->estado != operacional) {
    limpaLCD();
    display((char *)"Nao pode votar");
    aguardaTecla();
    return;
  }

  do {
    limpaLCD();
    display((char *)"Eleitor:");
    leTeclado(eleitor, 5, urna);
    enviaStringModulo((char *)"UN", n, eleitor);
    recebeSerialModulo(resposta);
    status = strcmp(resposta, "Codigo invalido") == 0;
    if (status) {
      limpaLCD();
      display((char *)"Codigo invalido");
      aguardaTecla();
    }
  } while (status);
  votacao(urna, eleitor);
}

void auditoria(struct Urna *urna) {
  int votos = 0, horas, minutos;
  char resposta[4] = {0};

  for (int i = 0; i < N_CANDIDATO_LINHAS; i++) {
    for (int j = 0; j < N_CANDIDATO_COLUNAS; j++) {
      votos += urna->candidatos[i][j].votos;
    }
  }

  horas = urna->tempo / 3600;
  minutos = (urna->tempo % 3600) / 60;

  mandaStringSerial((char *)"UV");
  mandaCharSerial(horas);
  mandaCharSerial(minutos);
  mandaCharSerial(votos);

  leSerial(resposta, 3);
  if (!(strcmp(resposta, "MVO")))
    urna->proximo = menu;
  else if (!(strcmp(resposta, "MVI")))
    urna->proximo = auditoria;
  else if (!(strcmp(resposta, "MVX"))) {
    urna->proximo = autentica;
    urna->estado = bloqueado;
  }
}
