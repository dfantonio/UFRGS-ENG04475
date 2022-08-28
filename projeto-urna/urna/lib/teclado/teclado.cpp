#include "serial.h"
#include "timers.h"
#include <avr/io.h>
#include <lcd.h>

#define N_LINHAS  4
#define N_COLUNAS 3
#define TAM_TOTAL N_LINHAS *N_COLUNAS

// Colunas: PC3, PC4 e PC5
// Linhas: PD4, PD5, PD6 e PD7
void setupTeclado() {
  DDRC |= (1 << DD3) | (1 << DD4) | (1 << DD5);
  DDRD &= ~((1 << DD6) | (1 << DD5) | (1 << DD6) | (1 << DD7));
}

// Transforma uma coordenada de linha e coluna no número pressionado
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

// Varre todo o teclado
void leMatriz(bool valores[]) {
  for (int coluna = 0; coluna < N_COLUNAS; coluna++) {
    PORTC &= ~((1 << DD3) | (1 << DD4) | (1 << DD5));
    PORTC |= (1 << (coluna + 3));

    for (int linha = 0; linha < N_LINHAS; linha++) {
      delayUs(1); // Delay necessário para ler o valor da entrada recém modificada
      int pino = PIND & (1 << (linha + 4));

      int indice = normalizaPino(linha, coluna);

      valores[indice] = pino ? true : false;
    }
  }
}

bool botaoFoiPressionado(bool arr1[]) {
  for (int i = 0; i < TAM_TOTAL; i++) {
    if (arr1[i]) return true;
    /* code */
  }
  return false;
}

// Retorna true se igual e false se diferente
bool comparaArrays(bool arr1[], bool arr2[]) {
  for (int i = 0; i < TAM_TOTAL; i++) {
    if (arr1[i] != arr2[i]) return false;
  }
  return true;
}

// Copia o array de leitura
void copiaArrayInt(bool arr1[], bool arr2[]) {
  for (int i = 0; i < TAM_TOTAL; i++) {
    arr1[i] = arr2[i];
  }
}

// Encontra o índice do botão pressionado e retorna como um char
char index2Char(bool arr1[]) {
  for (int i = 0; i < TAM_TOTAL; i++) {
    if (arr1[i]) return i + '0'; // O 0 é utilizado pra chegar nos números da tabela ASCII
  }
}

char debounce() {
  bool referencia[TAM_TOTAL] = {0};
  bool novaLeitura[TAM_TOTAL] = {0};

  int count = 0;
  bool resultadoComp;

  while (1) {
    leMatriz(novaLeitura);
    resultadoComp = comparaArrays(referencia, novaLeitura);

    delayMs(1);

    if (resultadoComp && botaoFoiPressionado(referencia)) {
      count++;
    } else {
      if (count > 7)
        return index2Char(referencia);

      copiaArrayInt(referencia, novaLeitura);
      count = 0;
    }
  }
}

void criaAsteriscos(char *str, int tamanho) {
  for (int i = 0; i < tamanho; i++) {
    str[i] = '*';
  }
  str[tamanho] = 0;
}

void limpaStr(char *str, int tamanho) {
  for (int i = 0; i < tamanho; i++) {
    str[i] = 0;
  }
}

void leTeclado(char *str, int tamanho, bool senha = false) {
  char asteriscos[tamanho + 1] = {0};
  char letra;

  limpaStr(str, tamanho);

  for (int i = 0; i < tamanho; i++) {
    letra = debounce();
    if (letra == ';') { // Caso seja o #, atua como backspace e apaga um caracter
      if (i > 0) {
        str[i - 1] = 0;
        i -= 2;
      }
    } else
      str[i] = letra;

    if (senha) {
      criaAsteriscos(asteriscos, i + 1);
      display(asteriscos, 1);
    } else
      display(str, 1);
  }
}

void aguardaTecla() {
  debounce();
}