#include "serial.h"
#include "timers.h"
#include <avr/io.h>

#define RS PC0 // Define RS
#define RW PC1 // Define Read/Write
#define EN PC2 // Define Enable

void setaPinos(unsigned char comando) {
  unsigned char portb = comando & 0x3f;        // pega os 6 primeiros bits do comando
  unsigned char portd = (comando & 0xc0) >> 4; // Pega os 2 últimos bits e desloca pros bits 2 e 3

  PORTB = portb;
  PORTD &= ~(0xc);
  PORTD |= portd;
}

void comandoLCD(unsigned char comando) {
  setaPinos(comando);
  PORTC &= ~(1 << RS); // RS
  PORTC &= ~(1 << RW); // Read/Write
  PORTC |= (1 << EN);  // Dá um pulso
  delayUs(1);
  PORTC &= ~(1 << EN);
  delayMs(3);
}

void charLCD(unsigned char char_data) // Recebe os dados da string
{
  setaPinos(char_data);
  PORTC |= (1 << RS);
  PORTC &= ~(1 << RW);
  PORTC |= (1 << EN);
  delayUs(1);
  PORTC &= ~(1 << EN);
  delayMs(1);
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

  comandoLCD(0x38); // Inicializa LCD 8 bits
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
