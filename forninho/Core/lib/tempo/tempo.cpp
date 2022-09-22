#include <stdio.h>

void formataTempo(char *str, int tempo) {
  int horas, minutos;

  horas = tempo / 3600;
  minutos = (tempo % 3600) / 60;

  sprintf(str, "%02d:%02d", horas, minutos);
}