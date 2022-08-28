#include "comunicaModulo.h"
#include "dados.h"
#include "lcd.h"
#include "navegaMenu.h"
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
void geraRelatorio(struct Urna *urna);

char TEMP5[5];
char TEMP2[2];

// TODO: Só é possível votar caso o estado da urna seja operacional

void autentica(struct Urna *urna) {
  int status;
  display("Insira o codigo:");

  // Lê o código
  do {
    limpaLCD();
    display("Insira o codigo:");
    leTeclado(TEMP5, 5, false);

    status = strcmp(TEMP5, CODIGO_MESARIO) != 0;
    if (status) {
      limpaLCD();
      display("CODIGO INVALIDO");
      aguardaTecla();
    }
  } while (status); // Repete enquanto o código for inválido

  // Lê a senha
  do {
    limpaLCD();
    display("Insira a senha:");
    leTeclado(TEMP5, 5, true);

    status = strcmp(TEMP5, SENHA_MESARIO) != 0;
    if (status) {
      limpaLCD();
      display("SENHA INVALIDA");
      aguardaTecla();
    }
  } while (status);

  urna->proximo = menu;
};

void menu(struct Urna *urna) {
  limpaLCD();
  display("menu principal:");

  urna->proximo = navegaMenu;
}

void exibeHora(struct Urna *urna) {
  char horario[6];
  limpaLCD();
  display("Hora atual:");
  formataTempo(horario, urna->tempo);
  display(horario, 1);

  leTeclado(TEMP2, 1, false);

  urna->proximo = menu;
}

void defineHora(struct Urna *urna) {
  TEMP2[2] = 0;
  long hora, minuto;
  urna->proximo = menu;

  if (urna->estado == encerrado) {
    limpaLCD();
    display("Nao pode alterar");
    aguardaTecla();
    return;
  }

  // Proteção para que o horário seja válido
  do {
    limpaLCD();
    display("Digite a hora:");
    leTeclado(TEMP2, 2, false);
    hora = atoi(TEMP2);
  } while (hora > 23);

  do {
    limpaLCD();
    display("Digite os min:");
    leTeclado(TEMP2, 2, false);
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
  display("Estado atual:");
  populaEstado(estado, urna->estado);
  display(estado, 1);

  leTeclado(TEMP2, 1, false);

  urna->proximo = menu;
}

void trocaEstadoUrna(struct Urna *urna) {
  char TEMP[1];
  char linha1[] = "0 - operacional";
  char linha2[] = "1 - bloqueado";
  urna->proximo = menu;

  if (urna->estado == encerrado || urna->estado == aguardando) {
    limpaLCD();
    display("Nao pode alterar");
    aguardaTecla();
    return;
  }

  do {
    limpaLCD();
    display(linha1, 0);
    display(linha2, 1);

    leTeclado(TEMP, 1, false);
    if (TEMP[0] == '0') urna->estado = operacional;
    if (TEMP[0] == '1') urna->estado = bloqueado;
  } while (!(TEMP[0] == '0' || TEMP[0] == '1'));
}

void geraRelatorio(struct Urna *urna) {
  limpaLCD();
  display("relatorio", 1);
}

void validaEleitor(struct Urna *urna) {
  char eleitor[] = "00000";
  char resposta[16];
  int status = 0;
  char n[] = "5";

  do {
    limpaLCD();
    display("Eleitor:");
    leTeclado(eleitor, 5, false);
    enviaStringModulo("UN", n, eleitor);
    recebeSerialModulo(resposta);
    status = strcmp(resposta, "Codigo invalido") == 0;
    if (status) {
      limpaLCD();
      display("Codigo invalido");
      aguardaTecla();
    }
  } while (status);
  display("votacao", 0);
  aguardaTecla();
  votacao(urna, eleitor);
}

// TODO: TEM QUE TESTAR!!!
void auditoria(struct Urna *urna) {
  char i, j, votos, horas, minutos;
  char verifica[10] = {0},
       temp[3];

  for (j = 0; j == 2; j++) {
    for (i = 0; i == 6; i++) {
      votos += urna->candidatos[j][i].votos;
    }
  }

  horas = urna->tempo / 3600;
  minutos = (urna->tempo - horas * 3600) / 60;

  strcpy(verifica, "UV");
  convInt2Char(temp, horas);
  strcat(verifica, temp);
  convInt2Char(temp, minutos);
  strcat(verifica, temp);
  convInt2Char(temp, votos);
  strcat(verifica, temp);
  mandaStringSerial(verifica);

  urna->proximo = menu;
}
