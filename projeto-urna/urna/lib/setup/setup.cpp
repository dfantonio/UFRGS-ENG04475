#include "lcd.h"
#include "teclado.h"
#include <avr/interrupt.h>
#include <avr/io.h>

void setup() {
  UCSR0B |= 16 + 8; // Habilita recepção e transmissão serial (RXEN0 e TXEN0)
  UBRR0 = 51;       // Valor para baud rate de 19200

  sei();             // Habilita as interrupções
  TIMSK1 = (1 << 0); // Habilita interrupção de overflow do timer 1

  TCCR1A = 0;        // Operação normal do timer1
  TCCR1B = (1 << 2); // Inicia o timer1 com prescaler de 256

  TCNT1 = 3036; // Define o tempo da 1ª contagem do timer

  setupDisplay();
  setupTeclado();
}