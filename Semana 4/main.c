#include <reg51.h>

sbit pino0 = P1 ^ 7;

void main(void) {
  char oldStatus = 0, count = 0, debouncedInput = 0;

  TMOD = 0x10; // habilita o timer 1 para contador de 16 bits
  TR1 = 1;     // ativa o timer 1

  // TL e TH definem a contagem de 16 bits. Nesse caso vão contar por 10 ms.
  TH1 = 0xb8;
  TL1 = 0x62;
  TF1 = 0;

  while (1) {
    if (TF1) { // Quando o timer1 estourar

      // Reseta o timer para contar novamente
      TH1 = 0xb8;
      TL1 = 0x62;
      TF1 = 0;

      // se o pino tiver o mesmo valor da última leitura
      if (pino0 == oldStatus) count++;
      else {
        oldStatus = pino0; // Atualiza o status do pino
        count = 0;         // zera o contador
      }

      if (count >= 10) { // Caso o contador seja maior ou igual a 10 podemos confiar na entrada
        debouncedInput = pino0;
      }
    }
  };
}
