#include "comunicaModulo.h"
#include "dados.h"
#include "lcd.h"
#include "serial.h"
#include "teclado.h"
#include "timers.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdlib.h>
#include <string.h>

int *contadorp, *auxp;

ISR(TIMER2_OVF_vect) {
  *contadorp++;

  TCNT2 = 100; // Recarrega o timer
  TIFR2 = 1;   // Limpa a flag de estouro

  if (*contadorp >= 10000) {
    if (*contadorp >= 10000 + 1500 * (*auxp)) {
      // led = !led
    }
    *auxp++;
  }

  if (*contadorp == 12000) {
    *contadorp = 0;
    TCCR2B = 0x00; // Para o timer 2
    mandaStringSerial("UT");
    // TODO: Mandar a urna para o menu novamente
  }
};

void recebeCandidato(char cargo[], char codigoModulo[], char eleitor[], char *candidato, char *partido) {
  char codigoCandidato[] = "00",
       resposta[20] = {0},
       confirma = 0;
  do {
    limpaLCD();
    display(cargo, 0);
    leTeclado(codigoCandidato, 2, 0);

    enviaStringModulo(codigoModulo, "2", codigoCandidato);
    recebeSerialModulo(resposta);
    desembaralha(resposta, eleitor, candidato, partido);

    limpaLCD();
    display(candidato, 0);
    display("1-SIM   2-NAO");
    do {
      leTeclado(&confirma, 1, 0);
    } while (confirma != 1 || confirma != 0);
  } while (confirma == 0);
}

void contabilizaVoto(struct Candidato candidatos[3][7], char candidato[], int cargo, char partido[]) {
  int i = 0;
  if (!(strcmp(0, candidatos[0][i].nome) == 0)) {
    do {
      i++;
    } while (!(strcmp(candidato, candidatos[0][i].nome)) || !(strcmp({0}, candidatos[0][i].nome) == 0));
  }
  strcpy(candidatos[cargo][i].nome, candidato);
  strcpy(candidatos[cargo][i].partido, partido);
  candidatos[cargo][i].votos++;
}

void votacao(struct Candidato candidatos[3][7], char eleitor[]) {
  int contador = 0, aux = 0, votoP, votoG, votoS, i = 0, cargo = 0;
  char resposta[20] = {0},
       candidato[20] = {0},
       partido[14] = {0};

  contadorp = &contador;

  auxp = &aux;

  // Inicialização do timer 2
  TCCR2A = 0x00;
  TCCR2B = 0x07;
  TCNT2 = 100;
  TIMSK2 = 0x01;
  sei();

  mandaStringSerial("UI");
  recebeSerialModulo(resposta);

  // Votação para presidente
  recebeCandidato("Presidente:", "UP", eleitor, candidato, partido);
  contabilizaVoto(candidatos, candidato, cargo, partido);

  // Votação para governador
  cargo++;
  recebeCandidato("Governador:", "UG", eleitor, candidato, partido);
  contabilizaVoto(candidatos, candidato, cargo, partido);

  // Votação para senador
  cargo++;
  recebeCandidato("Senador:", "US", eleitor, candidato, partido);
  contabilizaVoto(candidatos, candidato, cargo, partido);

  mandaStringSerial("UC");

  // TODO: Tocar som e mandar para o menu
}
