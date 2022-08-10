#include "dados.h"
#include "lcd.h"
#include "serial.h"
#include "setup.h"
#include "teclado.h"
#include "timers.h"
#include <avr/io.h>
#include <stdlib.h>
#include <string.h>

void autentica(struct Urna *urna);
void menu(struct Urna *urna);
void exibeHora(struct Urna *urna);
void defineHora(struct Urna *urna);

char TEMP5[5];
char TEMP2[2];

void autentica(struct Urna *urna) {
  int status;
  mandaStringSerial("\nNo aguardo do mesário autenticar");

  // Lê o código
  do {
    display("Insira o codigo:");
    LeTeclado(TEMP5, 5, false);

    status = strcmp(TEMP5, CODIGO_MESARIO) != 0;
    if (status) {
      display("CODIGO INVALIDO");
      aguardaTecla();
    }
  } while (status); // Repete enquanto o código for inválido

  // Lê a senha
  do {
    display("Insira a senha:");
    char str[6];
    convInt2Char(str, urna->tempo);
    mandaStringSerial(str);
    LeTeclado(TEMP5, 5, true);

    status = strcmp(TEMP5, SENHA_MESARIO) != 0;
    if (status) {
      mandaStringSerial("SENHA INVALIDA");
      aguardaTecla();
    }
  } while (status);

  urna->proximo = menu;
};

void menu(struct Urna *urna) {
  display("menu principal");

  while ((UCSR0A & (1 << 7)) == 0)
    ;                // Aguarda um caractere ser pressionado (Bit 7 do registrador UCSR0A
                     // (Receive Complete))
  char valor = UDR0; // valor recebe a tecla precionada
  UDR0 = valor;      // Devolve a letra digitada

  switch (valor) {
  case 't':
    urna->proximo = exibeHora;
    break;

  case 's':
    urna->proximo = defineHora;
    break;

  default:
    urna->proximo = menu;
    break;
  }
}

void exibeHora(struct Urna *urna) {
  char horario[6];
  display("Hora atual:");
  formataTempo(horario, urna->tempo);
  display(horario, 1);

  LeTeclado(TEMP2, 1, false);

  urna->proximo = menu;
}

// TODO: Implementar proteção pro usuário não colocar um horário dps das 23 hrs
// e minutos dps do 59
void defineHora(struct Urna *urna) {
  TEMP2[2] = 0;
  long hora, minuto;
  display("Digite a hora:");
  LeTeclado(TEMP2, 2, false);
  hora = atoi(TEMP2);

  display("Digite os min:");
  LeTeclado(TEMP2, 2, false);
  minuto = atoi(TEMP2);

  long teste = hora * 3600 + minuto * 60;
  convLong2Char(TEMP2, teste);

  urna->tempo = hora * 3600 + minuto * 60;
  urna->proximo = menu;
}