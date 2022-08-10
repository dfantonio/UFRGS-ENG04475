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

char *leSerial(char *str, int tamanho) {
  for (int i = 0; i < tamanho; i++) {
    while ((UCSR0A & (1 << 7)) == 0)
      ;
    str[i] = UDR0;
  }
}

void convInt2Char(char *str, int valor) {
  sprintf(str, "%d", valor);
}

void convLong2Char(char *str, long valor) {
  sprintf(str, "%ld", valor);
}