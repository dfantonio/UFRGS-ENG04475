/*
 * GccApplication2.c
 *
 * Created: 28/07/2022 20:45:29
 * Author : VinÃ­cius Verona
 */

#include <avr/io.h>
#include <interrupt.h>

#define IOPORT_CREATE_PIN(port, pin) ((IOPORT_##port) * 8 + (pin))

int main(void) {
  char valor;
  UCSR0B |= 16 + 8; // Habilita recepÃ§Ã£o e transmissÃ£o serial (RXEN0 e TXEN0)
  UBRR0 = 103;      // Taxa 9600bps => 16MHz/(8*(URBR0+1))

  TIMSK1 = (1 << 0); // Habilita interrupÃ§Ã£o de overflow do timer 1
  sei();             // Habilita as interrupÃ§Ãµes

  TCCR1A = 0;
  TCCR1B = 1;    // Inicia o timer sem prescaler
  TCNT1H = 0xD8; // Conta 5ms
  TCNT1L = 0xF0;

  do {
    while ((UCSR0A & (1 << 7)) == 0)
      ;                   // Aguarda um caractere ser precionado (Bit 7 do registrador UCSR0A (Recieve Complete))
    valor = UDR0;         // valor recebe a tecla precionada
    UDR0 = valor;         // Transmite A pela serial
  } while (valor != '1'); // Fica no laÃ§o atÃ© receber o caractere 1

  while (1) {
    UDR0 = 'A'; // Transmite A pela serial
    for (long i = 0; i < 1000000000; i++) {
      /* code */
    }
  }
}
