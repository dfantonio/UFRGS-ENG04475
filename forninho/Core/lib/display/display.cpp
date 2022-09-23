#include "main.h"

#define RS PC0 // Define RS
#define EN PC2 // Define Enable

GPIO_PinState normalizaBit(int dado) {
  return dado ? GPIO_PIN_SET : GPIO_PIN_RESET;
}

// Separa o comando na parte alta ou baixa
void setaPinos(unsigned char comando, bool parteAlta) {
  uint8_t temp = 0;
  if (parteAlta) {
    temp = comando >> 4;
  } else {
    temp = comando & 0xf;
  }

  HAL_GPIO_WritePin(display_D4_GPIO_Port, display_D4_Pin, normalizaBit(temp & 0b0001));
  HAL_GPIO_WritePin(display_D5_GPIO_Port, display_D5_Pin, normalizaBit(temp & 0b0010));
  HAL_GPIO_WritePin(display_D6_GPIO_Port, display_D6_Pin, normalizaBit(temp & 0b0100));
  HAL_GPIO_WritePin(display_D7_GPIO_Port, display_D7_Pin, normalizaBit(temp & 0b1000));
}

// Dá um pulso no enable
void pulsoEN() {
  HAL_GPIO_WritePin(display_EN_GPIO_Port, display_EN_Pin, GPIO_PIN_SET);
  HAL_Delay(1); // Antigamente era 1us. Testar se não afetou nada
  HAL_GPIO_WritePin(display_EN_GPIO_Port, display_EN_Pin, GPIO_PIN_RESET);
}

// Envia um comando ao display
void comandoLCD(unsigned char comando) {
  setaPinos(comando, true);

  HAL_GPIO_WritePin(display_RS_GPIO_Port, display_RS_Pin, GPIO_PIN_RESET);
  pulsoEN();

  HAL_Delay(1); // Antigamente era 200us. Testar se não afetou nada

  setaPinos(comando, false);
  pulsoEN();

  HAL_Delay(2);
}

// Grava um caracter no display
void charLCD(unsigned char caracter) {
  setaPinos(caracter, true);

  HAL_GPIO_WritePin(display_RS_GPIO_Port, display_RS_Pin, GPIO_PIN_SET);
  pulsoEN();

  HAL_Delay(1); // Antigamente era 200us. Testar se não afetou nada

  setaPinos(caracter, false);
  pulsoEN();

  HAL_Delay(2);
}

void stringLCD(const char *str) // Envia string para a função do LCD
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
  HAL_Delay(10);
  HAL_Delay(10);

  HAL_GPIO_WritePin(display_EN_GPIO_Port, display_EN_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(display_RS_GPIO_Port, display_RS_Pin, GPIO_PIN_RESET);

  comandoLCD(0xf0); // TESTE

  comandoLCD(0x33); // Inicializa o display no modo de 4 bits
  comandoLCD(0x32); // Inicializa o display no modo de 4 bits
  comandoLCD(0x28); // 2 linhas e 4 bits
  comandoLCD(0x0C); // Display ligado sem cursor
  comandoLCD(0x06); // Incrementa cursor
  comandoLCD(0x01); // Limpa display
  comandoLCD(0x80); // Cursor no início do LCD
}

void display(const char texto[], int linha = 0) {
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
