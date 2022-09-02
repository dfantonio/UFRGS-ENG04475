#include "dados.h"
#include "estados.h"
#include "lcd.h"
#include "serial.h"
#include "setup.h"
#include "teclado.h"
#include "timers.h"
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO 7

struct ItemMenu {
  const char *titulo;
  funcaoDoEstado *proximo;
};

char tempDisplay[20];

void navegaMenu(struct Urna *urna) {
  struct ItemMenu menu[TAMANHO] = {
      {PSTR(">Valida eleitor"), validaEleitor},
      {PSTR(">Consulta hora"), exibeHora},
      {PSTR(">Troca hora"), defineHora},
      {PSTR(">Consulta estado"), exibeEstado},
      {PSTR(">Troca estado"), trocaEstadoUrna},
      {PSTR(">Gera relatorio"), mandaRelatorio},
      {PSTR(">Auditoria"), auditoria},
  };

  int i = 0;
  char temp;
  do {
    do {
      mandaCharSerial(*menu[i].titulo);
      for (size_t j = 0; pgm_read_byte_near(menu[i].titulo + j) != 0; j++) {
        tempDisplay[j] = pgm_read_byte_near(menu[i].titulo + j);
        tempDisplay[j + 1] = 0;
      }
      display(tempDisplay, 1);
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