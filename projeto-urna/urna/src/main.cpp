#include <avr/interrupt.h>

#include "comunicaModulo.h"
#include "dados.h"
#include "estados.h"
#include "lcd.h"
#include "serial.h"
#include "setup.h"
#include "teclado.h"
#include "timers.h"

struct Urna *pUrna;

ISR(TIMER1_OVF_vect) {
  if (++pUrna->tempo >= 86400) pUrna->tempo = 0;
  verificaHorario(pUrna);

  // TODO: Modicação pra fazer o código contar mais rápido
  pUrna->tempo += 30;

  TCNT1 = CONTADOR_TIM1_1S; // Recarrega o timer
  TIFR1 = 1;                // Limpa a flag de estouro
};

int main(void) {
  char TEMP[3];
  struct Urna urna;
  pUrna = &urna;
  setup(&urna);

  display((char *)"Aguardando...");
  urna.tempo = recebeHora();

  while (urna.proximo) {
    if (urna.flagTimeoutVotacao) {
      mandaStringSerial((char *)"UT");
      leSerial(TEMP, 2);
      urna.flagTimeoutVotacao = false;
      limpaLCD();
      display("Tempo expirado");
      aguardaTecla();
      urna.proximo = menu;
    }
    urna.proximo(&urna);
  }
}
