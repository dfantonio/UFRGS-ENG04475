// CONFIG
#pragma config FOSC = HS   // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF  // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON  // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is MCLR)
#pragma config BOREN = ON  // Brown-out Detect Enable bit (BOD enabled)
#pragma config LVP = ON    // Low-Voltage Programming Enable bit (RB4/PGM pin has PGM function, low-voltage programming enabled)
#pragma config CPD = OFF   // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF    // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

unsigned char debounce(char botao)
{
  char oldStatus = 0, count = 0;
  while (1)
  {
    if (TMR1IF) // Quando o timer1 estourar
    {

      // se o pino tiver o mesmo valor da ?ltima leitura
      if (botao == oldStatus)
        count++;
      else
      {
        oldStatus = botao; // Atualiza o status do pino
        count = 0;         // zera o contador
      }

      if (count >= 7)
      {                // Caso o contador seja maior ou igual ao valor de bounce podemos confiar na entrada
        return !botao; // Retorna o valor negado para que o valor seja 1 quando o bot?o estiver pressionado. (fica mais intuitivo)
      }
    }
  };
}

// Função que define os pinos para o display
void setDigito(char numero)
{
  switch (numero)
  {
  case 1:
    PORTB = 0x28;
    break;
  case 2:
    PORTB = 0xCD;
    break;
  case 3:
    PORTB = 0x6D;
    break;
  }
}

__interrupt() interrupcao()
{
  if (T0IF)
  {
    INTCON &= ~(1 << 2);
    RA0 = !RA0;
  }
}

void main(void)
{
  char bot1, bot2, bot3;

  TRISA = 0xFE; // Define o pino RA0 como saída e os outros como entrada
  TRISB = 0x00; // Define todos os pinos da porta B como saída

  GIE = 1;  // Habilita interrupção global
  PEIE = 1; // Habilita a interrupção dos periféricos
  T0IE = 1; // Habilita interrupção por estouro do timer0

  TMR1ON = 1; // Habilita o timer 1
  // Configura o timer1 para contar 1ms
  TMR1H = 0xFE;
  TMR1L = 0x0C;

  while (1)
  {
    bot1 = debounce(RA1);
    bot2 = debounce(RA2);
    bot3 = debounce(RA3);

    if (bot1)
    {
      setDigito(1);
      // Muda a frequência do timer0 para 100Hz
      OPTION_REG = 0x03; 
      TMR0 = 100;
    }

    if (bot2)
    {
      setDigito(2);
      // Muda a frequência do timer0 para 200Hz
      OPTION_REG = 0x02;
      TMR0 = 100;
    }

    if (bot3)
    {
      setDigito(3);
      // Muda a frequência do timer0 para 300Hz
      OPTION_REG = 0x01;
      TMR0 = 48;
    }
  }
}
