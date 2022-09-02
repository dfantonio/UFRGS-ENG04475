#include "buzzer.h"
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
  ++*contadorp;

  TCNT2 = 100; // Recarrega o timer
  TIFR2 = 1;   // Limpa a flag de estouro

  if (*contadorp >= 10000 + 25 * (*auxp)) {
    PORTD ^= (1 << 3); // Inverte o led
    ++*auxp;
  }

  if (*contadorp == 12000) {
    *contadorp = 0;
    TCCR2B = 0x00;        // Para o timer 2
    PORTD &= ~(1 << DD3); // desliga o led
    pUrna2->flagTimeoutVotacao = true;
  }
};

void recebeCandidato(char cargo[], char codigoModulo[], char eleitor[], char codigoCandidato[], struct Urna *urna) {
  char partido[13] = {0}, candidato[20] = {0}, confirma = 0;
  char resposta[50] = {0};
  do {
    candidato[0] = 0;
    partido[0] = 0;

    limpaLCD();
    display(cargo, 0);
    leTeclado(codigoCandidato, 2, urna);

    if (pUrna2->flagTimeoutVotacao) return;

    enviaStringModulo(codigoModulo, (char *)"2", codigoCandidato);
    recebeSerialModulo(resposta);
    if (pUrna2->flagTimeoutVotacao) return;

    desembaralha(resposta, pUrna2->eleitor.nome, candidato, partido, &pUrna2->chaveCriptografia);

    do {
      limpaLCD();
      display(candidato, 0);
      display((char *)"1-SIM   2-NAO", 1);
      leTeclado(&confirma, 1, urna);
      if (pUrna2->flagTimeoutVotacao) return;
    } while (confirma != '1' && confirma != '2');
  } while (confirma == '2');
  if (!(strcmp("Voto NULO", candidato))) strcpy(codigoCandidato, "99");
}

void contabilizaVoto(char codigoCandidato[], enum Cargos cargo) {
  int i = 0;
  for (; i < N_CANDIDATO_COLUNAS; i++) {
    bool isCodigoCorreto = !strcmp(codigoCandidato, pUrna2->candidatos[cargo][i].codigo);
    bool isCodigoVazio = pUrna2->candidatos[cargo][i].codigo[0] == 0;
    if (isCodigoCorreto || isCodigoVazio) break;
  }

  strcpy(pUrna2->candidatos[cargo][i].codigo, codigoCandidato);
  pUrna2->candidatos[cargo][i].votos++;
}

void votacao(struct Urna *urna) {
  pUrna2 = urna;
  int contador = 0, aux = 0;
  char resposta[20] = {0},
       candidatoSenador[3] = {0},
       candidatoGovernador[3] = {0},
       candidatoPresidente[3] = {0};

  contadorp = &contador;

  auxp = &aux;

  // Inicialização do timer 2
  TCCR2A = 0x00;
  TCCR2B = 0x07;
  TCNT2 = 100;

  mandaStringSerial((char *)"UI");
  leSerial(resposta, 2);
  // Votação para senador
  recebeCandidato((char *)"Senador:", (char *)"US", urna->eleitor.nome, candidatoSenador, urna);
  // Votação para governador
  recebeCandidato((char *)"Governador:", (char *)"UG", urna->eleitor.nome, candidatoGovernador, urna);
  // Votação para presidente
  recebeCandidato((char *)"Presidente:", (char *)"UP", urna->eleitor.nome, candidatoPresidente, urna);

  if (pUrna2->flagTimeoutVotacao) return;

  // Contabilização dos votos
  contabilizaVoto(candidatoSenador, Senador);
  contabilizaVoto(candidatoGovernador, Governador);
  contabilizaVoto(candidatoPresidente, Presidente);

  mandaStringSerial((char *)"UC");
  leSerial(resposta, 2);

  somFimVotacao();
  PORTD &= ~(1 << DD3); // desliga o led
  TCCR2B = 0x00;        // Para o timer 2

  int votos = 0;
  for (int j = 0; j < N_CANDIDATO_COLUNAS; j++) {
    votos += urna->candidatos[Senador][j].votos;
  }
  if (votos == N_ELEITORES) urna->estado = encerrado;

  urna->proximo = menu;
}

bool eleitorValido(struct Urna *urna, int matricula) {
  for (uint8_t i = 0; i < N_ELEITORES; i++) {
    if (urna->listaEleitores[i] == matricula)
      return false;
  }
  return true;
}

void adicionaEleitorLista(struct Urna *urna, int matricula) {
  for (uint8_t i = 0; i < N_ELEITORES; i++) {
    if (urna->listaEleitores[i] == 0) {
      urna->listaEleitores[i] = matricula;
      return;
    }
  }
}