#include "serial.h"
#include <avr/io.h>

#define N_LINHAS  4
#define N_COLUNAS 3

void setupTeclado() {
  DDRD |= (1 << DD0) + (1 << DD1) + (1 << DD2) + (1 << DD3);
}

char lePinos() {
  // for (int linha = 0; linha < N_LINHAS; linha++) {
  //   PORTD = (1 << linha);
  //   for (int coluna = 0; coluna < N_COLUNAS; coluna++) {
  //     if (PIND & (1 << (coluna + 4))) {
  //       mandaStringSerial("\napertei");
  //       char str[2];
  //       convInt2Char(str, linha);
  //       mandaStringSerial(str);
  //       convInt2Char(str, coluna);
  //       mandaStringSerial(str);
  //     };
  //   }
  // }
  // PORTD = (1 << 3);
  PORTD = 0;
  if (PIND & (1 << (0 + 4))) {
    mandaStringSerial("\napertei");
  }
}

// TODO: Remover o argumento do char
char *LeTeclado(char *str, int tamanho, bool senha) {
  // Dansk vai codar a lógica pra ler o teclado

  // As variáveis são o seguinte:
  // tamanho -> é quantos caracteres temos que ler. Isso é importante pq ao
  // longo do fluxo temos leituras com tamanhos diferentes
  // senha -> é um booleano que indica se devemos ocultar os números digitados
  // (colocar asterisco no lugar)

  // Pensei que essa função pode "segurar" o código pra aguardar até o usuário
  // digitar todos os números. Mas tbm podemos fazer de outra forma

  // A função retorna uma string pois caso o número começasse com 0 ele teria um
  // caracter a menos. (um zero a esquerda não é nada num inteiro)

  // To mockando o retorno enquanto não temos nada
  return leSerial(str, tamanho);
}

// Função que trava o código até o usuário pressionar qualquer tecla
void aguardaTecla() {}