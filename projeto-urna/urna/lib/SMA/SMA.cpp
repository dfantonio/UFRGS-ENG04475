#include <string.h>

// Função que incrementa as letras
char somaLetra(char letra, char soma) {
  if (letra >= 'a' && letra <= 'z') {
    if ((letra + soma) > 'z')
      letra -= 26;       // Caso a subtração seja menor que A vai para Z
    return letra + soma; // Subtrai a letra com a chave
  }
  if (letra >= 'A' && letra <= 'Z') {
    if ((letra + soma) > 'Z')
      letra -= 26; // Caso a subtração seja menor que A vai para Z

    return letra + soma; // Subtrai a letra com a chave
  }

  return letra + soma; // Soma a letra com a chave
}

// Função que decrementa as letras
char subtraiLetra(char letra, char soma) {
  if (letra >= 'a' && letra <= 'z') {
    if ((letra - soma) < 'a')
      letra += 26; // Caso a subtração seja menor que A vai para Z

    return letra - soma; // Subtrai a letra com a chave
  }
  if (letra >= 'A' && letra <= 'Z') {
    if ((letra - soma) < 'A')
      letra += 26; // Caso a subtração seja menor que A vai para Z

    return letra - soma; // Subtrai a letra com a chave
  }
}

// void decriptografaSemChave(char *str, char *eleitor, int *chave) {
void decriptografaSemChave(char *str, char *eleitor, int *chave) {
  int indice = 0; // Índice da palavra que estamos buscando
  int aux;        // Variáveis auxiliares
  int i = strlen(eleitor);
  char temp[50];

  for (*chave = 0; *chave <= 26; ++*chave) { // Valor da *chave a ser testada
    for (aux = 0; str[aux] != NULL; aux++) {
      if (str[aux] != 32) {                           // Caso o caracter seja uma letra do alfabeto executa a decriptografia. Caso contrário, copia o espaço
        if ((aux % 2) == 0) {                         // se é par
          temp[aux] = subtraiLetra(str[aux], *chave); // Descriptografa a letra

          if (temp[aux] == eleitor[indice]) indice++; // Caso a letra seja igual a que estamos buscando, o índice é incrementado
          else
            indice = 0; // Caso contrário o índice é zerado

        } else {                                   // se é ímpar
          temp[aux] = somaLetra(str[aux], *chave); // Descriptografa a letra

          if (temp[aux] == eleitor[indice]) indice++; // Caso a letra seja igual a que estamos buscando, o índice é incrementado
          else
            indice = 0; // Caso contrário o índice é zerado
        }
      } else {
        temp[aux] = str[aux];
        if (indice > 0) indice++;
      }
      if (indice == i) {
        *chave = *chave;
        strcpy(str, temp);
        return;
      }
    }
  }
}

void decriptografaComChave(char *dest, char *src, int chave) {
  int aux; // Variáveis auxiliares
  int i = strlen(dest);

  for (aux = 0; src[aux] != NULL; aux++) { // Navega na frase

    if (src[aux] != 32) { // Caso o caracter seja uma letra do alfabeto executa a decriptografia. Caso contrário, copia o espaço

      if (aux % 2 == 0) {
        dest[aux] = subtraiLetra(src[aux], chave);
      } else {
        dest[aux] = somaLetra(src[aux], chave);
      }
    } else {
      dest[aux] = src[aux];
    }
    dest[aux + 1] = 0;
  }
}