#include <avr/io.h>
#include <stdio.h>

#include "dados.h"

void delayUs(int us) {
  if (256 - us * 2 > 0) {
    TCCR0A = 0;
    TCCR0B = 2; // Prescaler de 8
    TCNT0 = 256 - us * 2;
  } else {
    us = us / 4;
    TCCR0A = 0;
    TCCR0B = 3;
    TCNT0 = 256 - us;
  }

  while ((TIFR0 & (1 << 0)) == 0)
    ; // Aguarda flag de estouro

  TIFR0 = 1; // Limpa flag
}

void delayMs(int ms) {
  ms = ms * 125 / 8;
  TCCR0A = 0;
  TCCR0B = 5; // Prescaler 1024
  TCNT0 = 256 - ms;

  while ((TIFR0 & (1 << 0)) == 0)
    ; // Aguarda flag de estouro

  TIFR0 = 1; // Limpa flag
}

void formataTempo(char *str, long tempo) {
  int horas, minutos;

  horas = tempo / 3600;
  minutos = (tempo % 3600) / 60;

  sprintf(str, "%02d:%02d", horas, minutos);
}

void verificaHorario(struct Urna *urna) {
  const long limiteHoraInferior = 8 * 60 * 60;
  const long limiteHoraSuperior = (long)17 * 60 * 60 + 15 * 60;

  if (urna->tempo < limiteHoraInferior) urna->estado = aguardando;
  if (urna->tempo > limiteHoraSuperior) urna->estado = encerrado;
}