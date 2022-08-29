#include "dados.h"
#include "serial.h"
#include <avr/pgmspace.h>
#include <string.h>

// Por causa do tamanho do texto que temos que enviar no relatório,
// essa variável tem q ser declarada no começo, e não pode estar dentro
// da função. caso sobre tempo, refatorar o código pra calcular o tamanho
// necessário antes de enviar (assim podemos enviar letra por letra sem ter q alocar tudo de antemão)
char compilado[500] = {0};

void populaCargos(char *str, int cargo) {
  switch (cargo) {
  case Presidente:
    strcpy(str, (char *)"Presidente");
    break;

  case Governador:
    strcpy(str, (char *)"Governador");
    break;

  case Senador:
    strcpy(str, (char *)"Senador");
    break;

  default:
    break;
  }
}

void copia(char dest[], char origem[], int *index) {
  int i = 0;
  for (; origem[i] != 0; i++) {
    dest[*index + i] = origem[i];
  }
  *index += i;
}

void votos2string(char str[], int valor) {
  int unidade = valor % 10;
  int dezena = valor / 10;

  if (dezena) {
    str[0] = dezena + '0';
    str[1] = unidade + '0';
    str[2] = 0;
  } else {
    str[0] = unidade + '0';
    str[1] = 0;
  }
}

void geraRelatorio(struct Urna *urna) {
  int index = 0;

  char votosString[15] = {0};

  copia(compilado, (char *)"Relatorio:\r\n", &index);
  char cargo[12];

  for (int i = 0; i < N_CANDIDATO_LINHAS; i++) {
    populaCargos(cargo, i);
    copia(compilado, cargo, &index);
    copia(compilado, (char *)": \r\n", &index);

    for (int j = 0; j < N_CANDIDATO_COLUNAS; j++) {
      if (urna->candidatos[i][j].votos) {
        copia(compilado, urna->candidatos[i][j].nome, &index);
        votos2string(votosString, urna->candidatos[i][j].votos);
        copia(compilado, (char *)" com ", &index);
        copia(compilado, votosString, &index);
        copia(compilado, (char *)" votos", &index);
        copia(compilado, (char *)"\r\n", &index);
      }
    }
    copia(compilado, (char *)"\r\n", &index);
  }

  mandaStringSerial((char *)"UR");

  unsigned char tamanho1, tamanho2;
  tamanho1 = index / 255;
  tamanho2 = index % 255;
  mandaCharSerial(tamanho1);
  mandaCharSerial(tamanho2);

  mandaStringSerial(compilado);
}