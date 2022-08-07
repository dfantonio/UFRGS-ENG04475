#include "serial.h"

void display(char texto[], int linha = 0) {
  // Faz os paranaue pra renderizar o texto no display LCD.

  // TEMPORÁRIO:
  mandaStringSerial("\n");
  mandaStringSerial(texto);
}

void setupDisplay() {
  // Configura todas as coisas necessárias pro display
}