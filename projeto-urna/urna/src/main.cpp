#include <avr/interrupt.h>

#include "comunicaModulo.h"
#include "dados.h"
#include "estados.h"
#include "lcd.h"
#include "serial.h"
#include "setup.h"
#include "teclado.h"
#include "timers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char TEMP[3];
struct Urna urna;
ISR(USART_TX_vect) {
  limpaLCD();
  display("aque");
  aguardaTecla();
  leSerial(TEMP, 2);
  if (!(strcmp(TEMP, "MH"))) {
    urna.tempo = recebeHora();
    mandaStringSerial((char *)"UH");
  }
}

// Fazer recepção serial assíncrona via interrupção
// Pra não depender de receber a hora pra iniciar a urna. (colocar o status default como aguardando)
ISR(TIMER1_OVF_vect) {
  if (++urna.tempo >= 86400) urna.tempo = 0;
  verificaHorario(&urna);

  TCNT1 = CONTADOR_TIM1_1S; // Recarrega o timer
  TIFR1 = 1;                // Limpa a flag de estouro
};

int main(void) {
  setup(&urna);

  urna.tempo = (long)10 * 60 * 60;

  while (urna.proximo) {
    if (urna.flagTimeoutVotacao) {
      mandaStringSerial((char *)"UT");
      urna.flagTimeoutVotacao = false;
      limpaLCD();
      display("Tempo expirado");
      aguardaTecla();
      urna.proximo = menu;
    }
    urna.proximo(&urna);
  }
}
