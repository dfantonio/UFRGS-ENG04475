#include "buzzer.h"
#include "dados.h"
#include "estados.h"
#include "lcd.h"
#include "teclado.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <string.h>

void defineEstadoInicial(struct Urna *urna);

void setup(struct Urna *urna) {
  UCSR0B |= 16 + 8; // Habilita recepção e transmissão serial (RXEN0 e TXEN0)
  UBRR0 = 51;       // Valor para baud rate de 19200

  sei();             // Habilita as interrupções
  TIMSK1 = (1 << 0); // Habilita interrupção de overflow do timer 1

  TCCR1A = 0;        // Operação normal do timer1
  TCCR1B = (1 << 2); // Inicia o timer1 com prescaler de 256

  TCNT1 = 3036; // Define o tempo da 1ª contagem do timer

  DDRD |= (1 << DD3); // Pino 3 da porta d é saída
  TIMSK2 = 0x01;      // Interrupção timer 2
  TCCR2A = 0;

  setupDisplay();
  setupTeclado();
  setupBuzzer();

  defineEstadoInicial(urna);
}

void defineEstadoInicial(struct Urna *urna) {
  urna->proximo = autentica;
  urna->estado = operacional;
  urna->tempo = 0;
  urna->flagTimeoutVotacao = false;
  urna->chaveCriptografia = 1;

  for (int i = 0; i < N_CANDIDATO_LINHAS; i++) {
    for (int j = 0; j < N_CANDIDATO_COLUNAS; j++) {
      urna->candidatos[i][j].votos = 0;
      urna->candidatos[i][j].codigo[0] = 0;
    }
  }

  for (uint8_t i = 0; i < N_ELEITORES; i++) {
    urna->listaEleitores[i] = 0;
  }

  // Dados de teste:

  // urna->candidatos[0][0].votos = 5;
  // strcpy(urna->candidatos[0][0].partido, "PT");
  // strcpy(urna->candidatos[0][0].nome, "Airton Pinto");
  // urna->candidatos[0][1].votos = 39;
  // strcpy(urna->candidatos[0][1].partido, "PSDB");
  // strcpy(urna->candidatos[0][1].nome, "Jair bolsonaro");
}