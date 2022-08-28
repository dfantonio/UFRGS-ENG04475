#include "serial.h"
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void enviaStringModulo(char primeiro[], char n[], char codigo[]) {
  mandaStringSerial(primeiro);
  mandaStringSerial(n);
  mandaStringSerial(codigo);
}

void auditaSerial(int hora, int min, int votos) {
  mandaStringSerial("UV");
  mandaCharSerial(hora);
  mandaCharSerial(min);
  mandaCharSerial(votos);
}

void recebeSerialModulo(char *str) { // Recebe string
  leSerial(str, 3);
  leSerial(str, str[2]);
}

long recebeHora() { // Recebe hora
  char str[2];
  long segundos = 0;
  char minuto[2], hora[2];

  leSerial(str, 2);
  leCharSerial(hora);
  leCharSerial(minuto);

  segundos = atoi(hora) * 3600 + atoi(minuto) * 60;

  return segundos;
}

void desembaralha(char embaralhado[], char *eleitor, char *candidato, char *partido) {
  int i = 0, j = 0, k = 0;
  char aux[20] = {0};
  // Separa as palavras
  for (j = 0; j < 2; j++) {
    k = 0;
    do {
      aux[k] = embaralhado[i];
      i++;
      k++;
    } while (embaralhado[i - 1] != 0);
    // TODO: IMPLEMENTAR DO MODO COM CRIPTIPTOGRAFIA
    // Decriptografa aux
    // Caso seja partido, começa com "P"
    if (j == 1)
      strcpy(partido, aux);
    // Caso seja nome do candidato, não é partido, nem o nome do eleitor
    // else if (strcmp(eleitor, aux) != 0)
    else
      strcpy(candidato, aux);
  }
}