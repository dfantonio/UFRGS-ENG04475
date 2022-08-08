#include <avr/interrupt.h>
#include <avr/io.h>

#include "dados.h"
#include "estados.h"
#include "serial.h"
#include <setup.h>

int relogio;

ISR(TIMER1_OVF_vect) {
  relogio++;
  mandaStringSerial("\n TEMPO: ");
  mandaStringSerial(convInt2Char(relogio));

  TCNT1 = CONTADOR_TIM1_1S; // Recarrega o timer
  TIFR1 = 1;                // Limpa a flag de estouro
};

int main(void) {
  setup();

  struct Urna urna = {autentica, 0};

  while (urna.proximo)
    urna.proximo(&urna);
}
