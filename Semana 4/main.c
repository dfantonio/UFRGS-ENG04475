#include <reg52.h>

#define BOUNCE 7


sbit pinSaida = P3^4; //Define o pino de saída

// Função para fazer o debouce.
// Os valores de linha e coluna variam entre 0 e 3.
unsigned char debounce (char linha, char coluna) {
	char oldStatus = 0, count = 0, pinoColuna;
	
	pinoColuna = P0 & (1 << coluna); // Define o pino da coluna desejada;
	
	
  TMOD = 0x01; // habilita o timer 0 para contador de 16 bits
  // TL e TH definem a contagem de 16 bits. Nesse caso vão contar por 1ms.
  TH0 = 0xf8;
  TL0 = 0xcd;
  TF0 = 0;
  TR0 = 1;     // ativa o timer 0
	
	P0 = ~(1 << (7 - linha)); // Define todos os valores de P0 como 1 exceto a linha desejada.
	
  while (1) {
    if (TF0) { // Quando o timer0 estourar

      // Reseta o timer para contar novamente
      TH0 = 0xb8;
      TL0 = 0x00;
      TF0 = 0;

      // se o pino tiver o mesmo valor da última leitura
      if (pinoColuna == oldStatus) count++;
      else {
        oldStatus = pinoColuna; // Atualiza o status do pino
        count = 0;         // zera o contador
      }

      if (count >= BOUNCE) { // Caso o contador seja maior ou igual ao valor de bounce podemos confiar na entrada
        return !pinoColuna; // Retorna o valor negado para que o valor seja 1 quando o botão estiver pressionado. (fica mais intuitivo)
      }
    }
  };
}


//Função de interrupção do timer 2
void mudaSaida(void) interrupt 5 {
		TF2 = 0; // Zera a flag de estouro
		pinSaida = !pinSaida; // Inverte a saída
}

void main(void) {
  char col1, col2;
	
	TF2=0; // Zera a flag de estouro
	TR2=1; // Habilita a contagem
	
	TH2 = 0xDC; // Valor da parte alta para fazer uma contagem de 5 ms
	TL1 = 0x00; // Valor da parte baixa para fazer uma contagem de 5 ms
	RCAP2H = 0xDC; // Valor da parte alta para fazer uma contagem de 5 ms após o estouro
	RCAP2L = 0x00; // Valor da parte baixa para fazer uma contagem de 5 ms após o estouro
	
	EA=1; // Permite ativar todas as interrupções
	ET2=1; // Habilita a interrupção do timer 2
		
	while(1){
		col1 = debounce(2,0); // Lê o valor do pino na 3 linha e 1 coluna
		col2 = debounce(2,1); // Lê o valor do pino na 3 linha e 2 coluna		
		
		if(col1) { // Define o timer 2 para a frequência de 100 HZ
			RCAP2H = 0xDC;
			RCAP2L = 0x00;
		}
		
		if(col2) { // Define o timer 2 para a frequência de 200 HZ
			RCAP2H = 0xEE;
			RCAP2L = 0x00;
		}
	}
}
