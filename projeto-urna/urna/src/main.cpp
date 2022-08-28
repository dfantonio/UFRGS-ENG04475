#include <avr/interrupt.h>
#include <avr/io.h>

#include "comunicaModulo.h"
#include "dados.h"
#include "estados.h"
#include "lcd.h"
#include "serial.h"
#include "setup.h"

long *relogio;

ISR(TIMER1_OVF_vect) {
  if (++*relogio >= 86400) *relogio = 0;

  TCNT1 = CONTADOR_TIM1_1S; // Recarrega o timer
  TIFR1 = 1;                // Limpa a flag de estouro
};

int main(void) {
  struct Urna urna = {menu, 0};

  setup(urna.candidatos);

  relogio = &urna.tempo;

  display("Aguardando...", 1);
  urna.tempo = recebeHora();

  while (urna.proximo) {
    if (urna.flagTimeoutVotacao) {
      urna.flagTimeoutVotacao = false;
      urna.proximo = menu;
    }
    urna.proximo(&urna);
  }
}
