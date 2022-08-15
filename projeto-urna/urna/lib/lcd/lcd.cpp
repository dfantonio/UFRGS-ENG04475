#include "serial.h"
#include "timers.h"
#include <avr/io.h>

#define RS PC0 // Define RS
#define RW PC1 // Define Read/Write
#define EN PC2 // Define Enable

void comandoLCD(unsigned char comando) {
  PORTB = comando;
  PORTC &= ~(1 << RS); // RS
  PORTC &= ~(1 << RW); // Read/Write
  PORTC |= (1 << EN);  // Dá um pulso
  delayUs(1);
  PORTC &= ~(1 << EN);
  delayMs(3);
}

void charLCD(unsigned char char_data) // Recebe os dados da string
{
  PORTB = char_data;
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

// TODO: Arrumar o registrador C pra só definir os pinos utilizados como saída
void setupDisplay() {
  // Configura todas as coisas necessárias pro display
  // TODO: Definir somente os pinos utilizados como saída
  DDRC = 0xFF; // Porta C é saída
  DDRB = 0xFF; // Porta B é saída
  delayMs(10);
  delayMs(10);

  comandoLCD(0x38); // Inicializa LCD 8 bits
  comandoLCD(0x0C); // Display ligado sem cursor
  comandoLCD(0x06); // Incrementa cursor
  comandoLCD(0x01); // Limpa display
  comandoLCD(0x80); // Cursor no início do LCD
}

// TODO: Verona tem que fazer uma forma de limpar uma linha só, para quando o usuário apagar algum dígito
void display(char texto[], int linha = 0) {
  if (linha == 0) {
    limpaLCD(); // Limpa display
    stringLCD(texto);
  } // Escreve na primeira linha
  else {
    comandoLCD(0xC0); // Cursor na segunda linha
    stringLCD(texto); // Escreve na segunda linha
  }
}
