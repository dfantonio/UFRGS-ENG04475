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
  char minuto, hora;

  leSerial(str, 2);
  leCharSerial(&hora);
  leCharSerial(&minuto);

  segundos = (long)hora * 3600 + (long)minuto * 60;

  return segundos;
}