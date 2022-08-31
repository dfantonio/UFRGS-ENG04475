#include "serial.h"
#include "teclado.h"
#include "timers.h"
#include <avr/io.h>
#include <stdio.h>
#include <string.h>

void invertePino() {
  PORTB ^= (1 << DD4);
}

void tocaSom(int freq, int periodoMs) {
  int meioPeriodoUs = (1 * 1E6) / freq / 2;
  int limitCont = ((long)periodoMs * 1000) / (meioPeriodoUs * 2);

  for (int i = 0; i < limitCont; i++) {
    invertePino();
    delayUs(meioPeriodoUs);
    invertePino();
    delayUs(meioPeriodoUs);
  }
}

void somFimVotacao() {
  for (int i = 0; i < 4; i++) {
    tocaSom(2337, 100);
    tocaSom(2437, 100);
  }
}

// Configura o PB4 pro buzzer
void setupBuzzer() {
  DDRB |= (1 << DD4);
}