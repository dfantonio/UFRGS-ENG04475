#include <stdio.h>

void formataTempo(char *str, int tempoSegundos) {
  int horas, minutos;

  horas = tempoSegundos / 3600;
  minutos = (tempoSegundos % 3600) / 60;

  sprintf(str, "%02d:%02d", horas, minutos);
}

bool passouIntervalo(uint32_t *tempoAntigo, uint32_t tempoAtual, int intervalo) {
  if ((tempoAtual - *tempoAntigo) > intervalo) {
    *tempoAntigo = tempoAtual;
    return true;
  }

  return false;
}