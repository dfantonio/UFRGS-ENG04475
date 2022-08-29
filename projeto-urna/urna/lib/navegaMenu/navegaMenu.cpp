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

#define TAMANHO 7

struct ItemMenu {
  char titulo[17];
  funcaoDoEstado *proximo;
};

void navegaMenu(struct Urna *urna) {
  struct ItemMenu menu[TAMANHO] = {
      {">Valida eleitor", validaEleitor},
      {">Consulta hora", exibeHora},
      {">Troca hora", defineHora},
      {">Consulta estado", exibeEstado},
      {">Troca estado", trocaEstadoUrna},
      {">Gera relatorio", mandaRelatorio},
      {">Auditoria", auditoria},
  };

  int i = 0;
  char temp;
  do {
    do {
      display(menu[i].titulo, 1);
      leTeclado(&temp, 1, urna);
      if (temp == '5') {
        urna->proximo = menu[i].proximo;
        return;
      };
    } while (!(temp == '2' || temp == '8'));

    switch (temp) {
    case '2':
      i--;
      if (i == -1) i = TAMANHO - 1;
      break;

    case '8':
      i++;
      if (i == TAMANHO) i = 0;
      break;
    }

  } while (1);
}