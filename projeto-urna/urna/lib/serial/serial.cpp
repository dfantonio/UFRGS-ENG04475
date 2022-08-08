#include <avr/io.h>
#include <stdio.h>
#include <string.h>

void mandaStringSerial(char frase[]) {
  int i = 0;

  while (frase[i] != 0) {
    while (!(UCSR0A & (1 << UDRE0)))
      ;              // Aguarda o buffer estar liberado
    UDR0 = frase[i]; // Envia o próximo caracter
    i++;
  }
}

char *leSerial(int tamanho) {
  char texto[50], *ptn;
  ptn = texto;

  for (int i = 0; i < tamanho; i++) {
    while ((UCSR0A & (1 << 7)) == 0)
      ;
    texto[i] = UDR0;
  }

  return ptn;
}

char *convInt2Char(int valor) {
  char str[5], *ptn;
  ptn = str;

  sprintf(str, "%d", valor);

  return ptn;
}