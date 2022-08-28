#include <avr/interrupt.h>

#include "comunicaModulo.h"
#include "dados.h"
#include "setup.h"
#include "timers.h"

struct Urna *pUrna;

ISR(TIMER1_OVF_vect) {
  if (++pUrna->tempo >= 86400) pUrna->tempo = 0;
  verificaHorario(pUrna);

  pUrna->tempo += 30;

  TCNT1 = CONTADOR_TIM1_1S; // Recarrega o timer
  TIFR1 = 1;                // Limpa a flag de estouro
};

int main(void) {
  struct Urna urna;
  setup(&urna);

  urna.tempo = recebeHora();
  pUrna = &urna;

  while (urna.proximo)
    urna.proximo(&urna);
}
