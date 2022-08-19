#include <avr/io.h>
#include <stdio.h>
#include <string.h>

void mandaCharSerial(char letra) {
  while (!(UCSR0A & (1 << UDRE0)))
    ;           // Aguarda o buffer estar liberado
  UDR0 = letra; // Envia o próximo caracter
}

void mandaStringSerial(char frase[]) {
  int i = 0;

  while (frase[i] != 0) {
    mandaCharSerial(frase[i]);
    i++;
  }
}
void leCharSerial(char *letra) {
  while ((UCSR0A & (1 << 7)) == 0)
    ;
  *letra = UDR0;
}

void leSerial(char *str, int tamanho) {
  for (int i = 0; i < tamanho; i++) {
    leCharSerial(&str[i]);
  }
}

void convInt2Char(char *str, int valor) {
  sprintf(str, "%d", valor);
}

void convLong2Char(char *str, long valor) {
  sprintf(str, "%ld", valor);
}
