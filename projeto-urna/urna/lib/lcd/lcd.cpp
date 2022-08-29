#include "serial.h"
#include "timers.h"
#include <avr/io.h>

#define RS PC0 // Define RS
#define EN PC2 // Define Enable

// Separa o comando na parte alta ou baixa
void setaPinos(unsigned char comando, bool parteAlta) {
  if (parteAlta) {
    PORTB &= 0xf0;
    PORTB |= (comando >> 4);
  } else {
    PORTB &= 0xf0;
    PORTB |= comando & 0xf;
  }
}

// Dá um pulso no enable
void pulsoEN() {
  PORTC |= (1 << EN);
  delayUs(1);
  PORTC &= ~(1 << EN);
}

// Envia um comando ao display
void comandoLCD(unsigned char comando) {
  setaPinos(comando, true);

  PORTC &= ~(1 << RS);
  pulsoEN();

  delayUs(200);

  setaPinos(comando, false);
  pulsoEN();

  delayMs(2);
}

// Grava um caracter no display
void charLCD(unsigned char caracter) {
  setaPinos(caracter, true);

  PORTC |= (1 << RS);
  pulsoEN();

  delayUs(200);

  setaPinos(caracter, false);
  pulsoEN();

  delayMs(2);
}

void stringLCD(char *str) // Envia string para a função do LCD
{
  int i;
  for (i = 0; str[i] != 0; i++) // Envia cada char da string
  {
    charLCD(str[i]);
  }
}

void limpaLCD() {
  comandoLCD(0x01); // Limpa display
  comandoLCD(0x80); // Cursor no início do LCD
}

void setupDisplay() {
  // Configura todas as coisas necessárias pro display
  DDRC |= (1 << DD0) | (1 << DD1) | (1 << DD2);                                        // Porta C é saída
  DDRB |= (1 << DD0) | (1 << DD1) | (1 << DD2) | (1 << DD3) | (1 << DD4) | (1 << DD5); // Porta B é saída
  DDRD |= (1 << DD2) | (1 << DD3);

  delayMs(10);
  delayMs(10);

  comandoLCD(0x33); // Inicializa o display no modo de 4 bits
  comandoLCD(0x32); // Inicializa o display no modo de 4 bits
  comandoLCD(0x28); // 2 linhas e 4 bits
  comandoLCD(0x0C); // Display ligado sem cursor
  comandoLCD(0x06); // Incrementa cursor
  comandoLCD(0x01); // Limpa display
  comandoLCD(0x80); // Cursor no início do LCD
}

void display(char texto[], int linha = 0) {
  char limpa[] = "                ";
  if (linha == 0) {
    comandoLCD(0x80); // Cursor no início do LCD
    stringLCD(limpa); // Limpa primeira linha
    comandoLCD(0x80); // Cursor no início do LCD
    stringLCD(texto); // Escreve na primeira linha
  } else {
    comandoLCD(0xC0); // Cursor na segunda linha
    stringLCD(limpa); // Limpa segunda linha
    comandoLCD(0xC0); // Cursor na segunda linha
    stringLCD(texto); // Escreve na segunda linha
  }
}
