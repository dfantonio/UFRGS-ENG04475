#include <avr/io.h>

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