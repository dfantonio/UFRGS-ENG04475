#include <avr/interrupt.h>
#include <avr/io.h>

#include <setup.h>

int main(void) {
  char valor;
  long a;

  setup();

  do {
    while ((UCSR0A & (1 << 7)) == 0)
      ;                   // Aguarda um caractere ser pressionado (Bit 7 do registrador UCSR0A (Recieve Complete))
    valor = UDR0;         // valor recebe a tecla precionada
    UDR0 = valor;         // Transmite A pela serial
  } while (valor != '1'); // Fica no laÃ§o atÃ© receber o caractere 1

  while (1) {
    UDR0 = 'A'; // Transmite A pela serial
    for (a = 0; a < 1000000000; a++) {
      /* code */
    }
  }
}
