#include "dados.h"
#include "lcd.h"
#include "serial.h"
#include "setup.h"
#include "teclado.h"
#include <avr/io.h>
#include <string.h>

void autentica(struct Urna *urna);
void menu(struct Urna *urna);

void autentica(struct Urna *urna) {
  char *codigo;
  int status;
  mandaStringSerial("\nNo aguardo do mesário autenticar");

  // Lê o código
  do {
    display("Insira o código:");
    codigo = LeTeclado(5, false);

    status = strcmp(codigo, CODIGO_MESARIO) != 0;
    if (status) {
      display("CODIGO INVALIDO");
      aguardaTecla();
    }
  } while (status); // Repete enquanto o código for inválido

  // Lê a senha
  do {
    display("Insira a senha:");
    codigo = LeTeclado(5, true);

    status = strcmp(codigo, SENHA_MESARIO) != 0;
    if (status) {
      display("SENHA INVALIDA");
      aguardaTecla();
    }
  } while (status);

  urna->proximo = menu;
};

void menu(struct Urna *urna) {
  mandaStringSerial("\nEstou no menu principal");

  while ((UCSR0A & (1 << 7)) == 0)
    ; // Aguarda um caractere ser pressionado (Bit 7 do registrador UCSR0A
      // (Receive Complete))
  char valor = UDR0; // valor recebe a tecla precionada
  UDR0 = valor;      // Devolve a letra digitada

  if (valor == 'f') {
    mandaStringSerial("\nTeste");
  }

  urna->proximo = 0;
}