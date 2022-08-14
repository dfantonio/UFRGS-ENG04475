#include "serial.h"
#include "timers.h" //TODO: Deletar
#include <avr/io.h>
#include <string.h> //TODO: Deletar

#define N_LINHAS  4
#define N_COLUNAS 3

// Linhas: PC3, PC4 e PC5
// Colunas: PD4, PD5, PD6 e PD7
void setupTeclado() {
  DDRC |= (1 << DD3) | (1 << DD4) | (1 << DD5);
  DDRD &= (1 << DD4) | (1 << DD5) | (1 << DD6) | (1 << DD7);
}

int normalizaPino(int linha, int coluna) {
  int indice = (linha * 3) + (coluna + 1);
  if (indice > 10) switch (indice) {
    case 11:
      indice = 0;
      break;

    case 12:
      indice = 11;
    default:
      break;
    }

  return indice;
}

void lePinos(int *valores) {
  for (int coluna = 0; coluna < N_COLUNAS; coluna++) {

    PORTC &= ~((1 << DD3) | (1 << DD4) | (1 << DD5));
    PORTC = (1 << (coluna + 3));

    for (int linha = 0; linha < N_LINHAS; linha++) {
      int pino = PIND & (1 << (linha + 4));

      int indice = normalizaPino(linha, coluna);

      valores[indice] = pino ? 1 : 0;

      // if (pino) {
      //   mandaStringSerial("\napertei");
      //   char str[2];
      //   convInt2Char(str, linha);
      //   mandaStringSerial(str);
      //   convInt2Char(str, coluna);
      //   mandaStringSerial(str);

      //   mandaStringSerial(" ");
      //   convInt2Char(str, indice);
      //   mandaStringSerial(str);
      // };
    }
  }
}

bool botaoFoiPressionado(int arr1[]) {
  for (int i = 0; i < 12; i++) {
    if (arr1[i]) return true;
    /* code */
  }
  return false;
}

// Rretorna true se igual e false se diferente
bool comparaArrays(int arr1[], int arr2[]) {
  for (int i = 0; i < 12; i++) {
    if (arr1[i] != arr2[i]) return false;
  }
  return true;
}

void copiaArrayInt(int arr1[], int arr2[]) {
  for (int i = 0; i < 12; i++) {
    arr1[i] = arr2[i];
  }
}

void LeTeclado(char *str, int tamanho, bool senha) {
  int referencia[13] = {0};
  int novaLeitura[13];

  lePinos(novaLeitura);

  int count = 0;
  bool resultadoComp;

  char teste[2];
  while (1) {
    lePinos(novaLeitura);
    resultadoComp = comparaArrays(referencia, novaLeitura);

    // mandaStringSerial("\nto no while");
    // convInt2Char(teste, resultadoComp ? 1 : 0);
    // mandaStringSerial(teste);

    // mandaStringSerial("\n\nValor ref");
    // mandaStringSerial(referencia);
    // mandaStringSerial("\nValor novo");
    // mandaStringSerial(novaLeitura);

    for (int i = 0; i < 10; i++) {
      delayMs(10);
    }

    if (resultadoComp) {
      count++;
    } else {
      copiaArrayInt(referencia, novaLeitura);
      count = 0;
      lePinos(novaLeitura);
    }

    mandaStringSerial("\nAQUI");
    convInt2Char(teste, count);
    mandaStringSerial(teste);

    // TODO: Debuggar a função do botaofoipressionado

    if (count > 7 && botaoFoiPressionado(referencia)) {
      str[0] = 'a';
      str[0] = 0;
      break;
    }
  }

  // asd
}

// Função que trava o código até o usuário pressionar qualquer tecla
void aguardaTecla() {}