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
    PORTB ^= (1 << 5); // Inverte o led
    ++*auxp;
  }

  if (*contadorp == 12000) {
    *contadorp = 0;
    TCCR2B = 0x00; // Para o timer 2
    mandaStringSerial((char *)"UT");
    PORTB = (0 << 5); // desliga o led
    pUrna2->flagTimeoutVotacao = true;
  }
};

void recebeCandidato(char cargo[], char codigoModulo[], char eleitor[], char candidato[], char partido[], struct Urna *urna) {
  char codigoCandidato[2], resposta[20] = {0}, confirma = 0;

  do {
    limpaLCD();
    display(cargo, 0);
    leTeclado(codigoCandidato, 2, urna);

    if (pUrna2->flagTimeoutVotacao) return;

    enviaStringModulo(codigoModulo, (char *)"2", codigoCandidato);
    recebeSerialModulo(resposta);
    desembaralha(resposta, eleitor, candidato, partido);

    do {
      limpaLCD();
      display(candidato, 0);
      display((char *)"1-SIM   2-NAO", 1);
      leTeclado(&confirma, 1, urna);
      if (false) return;
    } while (confirma != '1' && confirma != '2');
  } while (confirma == '2');
}

void contabilizaVoto(char candidato[], enum Cargos cargo, char partido[]) {
  int i = 0;
  for (; i < N_CANDIDATO_COLUNAS; i++) {
    bool isNomeCorreto = !strcmp(candidato, pUrna2->candidatos[cargo][i].nome);
    bool isNomeVazio = pUrna2->candidatos[cargo][i].nome[0] == 0;
    if (isNomeCorreto || isNomeVazio) break;
  }

  strcpy(pUrna2->candidatos[cargo][i].nome, candidato);
  strcpy(pUrna2->candidatos[cargo][i].partido, partido);
  pUrna2->candidatos[cargo][i].votos++;
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
  DDRB |= (1 << 5); // Pino 5 da porta b é saída

  mandaStringSerial((char *)"UI");
  leSerial(resposta, 2);

  // Votação para senador
  recebeCandidato((char *)"Senador:", (char *)"US", eleitor, candidatoSenador, partidoSenador, urna);
  // Votação para governador
  recebeCandidato((char *)"Governador:", (char *)"UG", eleitor, candidatoGovernador, partidoGovernador, urna);
  // Votação para presidente
  recebeCandidato((char *)"Presidente:", (char *)"UP", eleitor, candidatoPresidente, partidoPresidente, urna);

  if (pUrna2->flagTimeoutVotacao) return;

  // Contabilização dos votos
  contabilizaVoto(candidatoSenador, Senador, partidoSenador);
  contabilizaVoto(candidatoGovernador, Governador, partidoGovernador);
  contabilizaVoto(candidatoPresidente, Presidente, partidoPresidente);

  mandaStringSerial((char *)"UC");
  somFimVotacao();
  PORTB = (0 << 5); // desliga o led
  urna->proximo = menu;
}
