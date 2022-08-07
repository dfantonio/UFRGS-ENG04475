#include "serial.h"

// Dicas sobre como retornar uma string em C
// https://flaviocopes.com/c-return-string/

char *LeTeclado(int tamanho, bool senha) {
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
  return leSerial(tamanho);
}

// Função que trava o código até o usuário pressionar qualquer tecla
void aguardaTecla() {}