#include <avr/interrupt.h>
#include <avr/io.h>

#include "dados.h"
#include "estados.h"
#include "serial.h"
#include <setup.h>

int main(void) {
  setup();

  struct Urna urna = {autentica, 0};

  while (urna.proximo)
    urna.proximo(&urna);
}
