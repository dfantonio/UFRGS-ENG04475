#include "botoes.h"
#include "display.h"
#include "main.h"

#define TAMANHO 3;

int exibeMenu(char itens[3][20])
{
  int i = 0;
  int temp;

  bool botaoMais = false, botaoMenos = false, botaoStart = false;

  do
  {

    display(itens[i], 1);

    do
    {
      botaoMais = leBotaoSoltando(botao_menu_mais_GPIO_Port, botao_menu_mais_Pin);
      botaoMenos = leBotaoSoltando(botao_menu_menos_GPIO_Port, botao_menu_menos_Pin);
      botaoStart = leBotaoSoltando(botao_menu_start_GPIO_Port, botao_menu_start_Pin);
    } while (botaoMais == false && botaoMenos == false && botaoStart == false);
    HAL_Delay(100);
    if (botaoStart)
      return i;
    if (botaoMais)
    {
      i++;
      temp = TAMANHO;
      if (i == temp)
        i = 0;
    }
    if (botaoMenos)
    {
      i--;
      if (i == -1)
      {
        i = TAMANHO;
        i--;
      }
    }
  } while (1);
}