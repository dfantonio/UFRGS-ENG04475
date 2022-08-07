#include <avr/io.h>

void setup() {
  UCSR0B |= 16 + 8; // Habilita recepção e transmissão serial (RXEN0 e TXEN0)
  UBRR0 = 103;      // Taxa 9600bps => 16MHz/(8*(URBR0+1))
}