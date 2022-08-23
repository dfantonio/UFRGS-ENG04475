#include <avr/interrupt.h>
#include <avr/io.h>

#include "comunicaModulo.h"
#include "dados.h"
#include "estados.h"
#include "serial.h"
#include "setup.h"

long *relogio;

ISR(TIMER1_OVF_vect) {
  if (++*relogio >= 86400) *relogio = 0;

  TCNT1 = CONTADOR_TIM1_1S; // Recarrega o timer
  TIFR1 = 1;                // Limpa a flag de estouro
};

int main(void) {
  setup();

  struct Urna urna = {autentica, 0};
  urna.tempo = recebeHora();
  relogio = &urna.tempo;

  while (urna.proximo)
    urna.proximo(&urna);
}
