#include "SMA.h"
#include "serial.h"
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void enviaStringModulo(char primeiro[], char n[], char codigo[]) {
  mandaStringSerial(primeiro);
  mandaStringSerial(n);
  mandaStringSerial(codigo);
}

void auditaSerial(int hora, int min, int votos) {
  mandaStringSerial((char *)"UV");
  mandaCharSerial(hora);
  mandaCharSerial(min);
  mandaCharSerial(votos);
}

void recebeSerialModulo(char *str) { // Recebe string
  leSerial(str, 1);
  leSerial(str, str[0]);
}

long recebeHora() { // Recebe hora
  long segundos = 0;
  char minuto, hora;

  leCharSerial(&hora);
  leCharSerial(&minuto);

  segundos = (long)hora * 3600 + (long)minuto * 60;

  return segundos;
}

void removeEspacoString(char *str) {
  if (str[0] == ' ')
    for (int i = 0; str[i] != 0; i++) {
      str[i] = str[i + 1];
    }
}

void desembaralha(char embaralhado[], char *eleitor, char *candidato, char *partido, int *chave) {
  char aux[20] = {0};
  char separados[3][20]; // Matrix com os 3 textos separados
  int indexEleitor = 0;  // Índice da matriz que está com o nome do eleitor (que a gente conhece)
  int i = 0, j = 0, k = 0;
  int chaveTemp = 0;

  // Separa as palavras
  for (j = 0; j < 3; j++) {
    k = 0;
    do {
      // Caso a palavra comece num índice ímpar eu adiciono um espaço
      // pro código descriptografar certo
      if (k == 0 && i % 2 == 1) {
        k++;
        aux[0] = ' ';
      }
      aux[k] = embaralhado[i];
      i++;
      k++;

    } while (embaralhado[i - 1] != 0);

    decriptografaSemChave(aux, eleitor, &chaveTemp);

    // Tento decriptografar todas as frases. Quando a chave é algo válido eu sei que é o primeiro nome do eleitor
    if (chaveTemp < 27) {
      *chave = chaveTemp;
      indexEleitor = j;
    }
    strcpy(separados[j], aux);
  }

  switch (indexEleitor) {
  case 0:
    decriptografaComChave(candidato, separados[1], *chave);
    decriptografaComChave(partido, separados[2], *chave);
    break;
  case 1:
    decriptografaComChave(candidato, separados[0], *chave);
    decriptografaComChave(partido, separados[2], *chave);
    break;
  case 2:
    decriptografaComChave(candidato, separados[0], *chave);
    decriptografaComChave(partido, separados[1], *chave);
    break;
  }

  removeEspacoString(candidato);
  removeEspacoString(partido);
}
