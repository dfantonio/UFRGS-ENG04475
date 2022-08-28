#include "comunicaModulo.h"
#include "dados.h"
#include "estados.h"
#include "lcd.h"
#include "serial.h"
#include "teclado.h"
#include "timers.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdlib.h>
#include <string.h>

int *contadorp, *auxp;
struct Urna *pUrna2;

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

  if (*contadorp == 1200) {
    *contadorp = 0;
    TCCR2B = 0x00; // Para o timer 2
    mandaStringSerial("UT");
    // TODO: arrumar issae, ir para menu daqui
    pUrna2->flagTimeoutVotacao = true;
  }
};

void recebeCandidato(char cargo[], char codigoModulo[], char eleitor[], char candidato[], char partido[]) {
  char codigoCandidato[3], resposta[20] = {0}, confirma = 0;

  do {
    limpaLCD();
    display(cargo, 0);
    leTeclado(codigoCandidato, 2, 0);

    enviaStringModulo(codigoModulo, "2", codigoCandidato);
    recebeSerialModulo(resposta);
    desembaralha(resposta, eleitor, candidato, partido);

    do {
      limpaLCD();
      display(candidato, 0);
      display("1-SIM   2-NAO", 1);
      leTeclado(&confirma, 1, 0);
    } while (confirma != '1' && confirma != '2');
  } while (confirma == '2');
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

void votacao(struct Urna *urna, char eleitor[]) {
  pUrna2 = urna;
  int contador = 0, aux = 0;
  char resposta[20] = {0},
       candidatoSenador[20] = {0},
       candidatoGovernador[20] = {0},
       candidatoPresidente[20] = {0},
       partidoSenador[14] = {0},
       partidoGovernador[14] = {0},
       partidoPresidente[14] = {0};

  contadorp = &contador;

  auxp = &aux;

  // Inicialização do timer 2
  TCCR2A = 0x00;
  TCCR2B = 0x07;
  TCNT2 = 100;
  TIMSK2 = 0x01;
  sei();

  mandaStringSerial("UI");
  leSerial(resposta, 2);
  display("vou receber", 1);
  aguardaTecla();
  // Votação para senador
  recebeCandidato("Senador:", "US", eleitor, candidatoSenador, partidoSenador);
  // Votação para governador
  recebeCandidato("Governador:", "UG", eleitor, candidatoGovernador, partidoGovernador);
  // Votação para presidente
  recebeCandidato("Presidente:", "UP", eleitor, candidatoPresidente, partidoPresidente);

  // Contabilização dos votos
  contabilizaVoto(urna->candidatos, candidatoSenador, Senador, partidoSenador);
  contabilizaVoto(urna->candidatos, candidatoGovernador, Governador, partidoGovernador);
  contabilizaVoto(urna->candidatos, candidatoPresidente, Presidente, partidoPresidente);

  mandaStringSerial("UC");

  // TODO: Tocar som
  urna->proximo = menu;
}
