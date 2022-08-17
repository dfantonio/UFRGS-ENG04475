#include "dados.h"
#include "estados.h"
#include "lcd.h"
#include "serial.h"
#include "setup.h"
#include "teclado.h"
#include "timers.h"
#include <avr/io.h>
#include <stdlib.h>
#include <string.h>

void navegaMenu(struct Urna *urna) {
  int move, i = 0, j = 0;
  char temp[2];
  display(">Valida eleitor", 1);
  do {
    do {
      leTeclado(temp, 1, false);
      move = atoi(temp);
    } while (!(move == 2 || move == 8 || move == 5));

    switch (move) {
    case 2:
      i--;
      if (i == -1) i = 5;
      break;

    case 8:
      i++;
      if (i == 6) i = 0;
      break;

    case 5:
      j = 1;
      break;
    }

    switch (i) {
    case 0:
      display(">Valida eleitor", 1);
      if (j == 1)
        urna->proximo = validaEleitor;
      break;

    case 1:
      display(">Consulta hora", 1);
      if (j == 1)
        urna->proximo = exibeHora;
      break;

    case 2:
      display(">Troca hora", 1);
      if (j == 1)
        urna->proximo = defineHora;
      break;

    case 3:
      display(">Troca estado", 1);
      if (j == 1)
        urna->proximo = trocaEstadoUrna;
      break;

    case 4:
      display(">Gera relatorio", 1);
      if (j == 1)
        urna->proximo = geraRelatorio;
      break;

    case 5:
      display(">Auditoria", 1);
      if (j == 1)
        urna->proximo = auditoria;
      break;
    }
  } while (!(j == 1));
}