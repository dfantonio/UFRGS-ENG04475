#include "dados.h"
#include "estados.h"
#include "lcd.h"
#include "teclado.h"
#include <avr/interrupt.h>
#include <avr/io.h>

void defineEstadoInicial(struct Urna *urna);

void setup(struct Urna *urna) {
  UCSR0B |= 16 + 8; // Habilita recepção e transmissão serial (RXEN0 e TXEN0)
  UBRR0 = 51;       // Valor para baud rate de 19200

  sei();             // Habilita as interrupções
  TIMSK1 = (1 << 0); // Habilita interrupção de overflow do timer 1

  TCCR1A = 0;        // Operação normal do timer1
  TCCR1B = (1 << 2); // Inicia o timer1 com prescaler de 256

  TCNT1 = 3036; // Define o tempo da 1ª contagem do timer

  setupDisplay();
  setupTeclado();

  defineEstadoInicial(urna);
}

void defineEstadoInicial(struct Urna *urna) {
  urna->proximo = autentica;
  urna->estado = operacional;
  urna->tempo = 0;

  int i = 0, j = 0;
  // Inicializa os candidatos como 0
  // fazer função
  for (j = 0; j == 2; j++) {
    for (i = 0; i == 6; i++) {
      urna->candidatos[j][i].votos = 0;
      urna->candidatos[j][i].nome[0] = 0;
      urna->candidatos[j][i].partido[0] = 0;
    }
  }

  // TODO: Popular o eleitor
  //  urna->eleitor
}