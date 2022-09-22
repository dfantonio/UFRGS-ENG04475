#include "botoes.h"
#include "dados.h"
#include "display.h"
#include "main.h"
#include "menu.h"
#include <stdio.h>

void demoTrocaDeEstado(struct Forno *forno);
void defineTemperatura(struct Forno *forno);
void defineTempo(struct Forno *forno);
void menuReceitas(struct Forno *forno);
void menu(struct Forno *forno);

void demoTrocaDeEstado(struct Forno *forno) {
  bool botaoPlaca;
  while (1) {
    botaoPlaca = HAL_GPIO_ReadPin(botao_placa_GPIO_Port, botao_placa_Pin);
    if (!botaoPlaca) {
      forno->proximo = menu; // Esse botão é normalmente fechado, por isso o !
      return;
    }
    HAL_Delay(100);
    HAL_GPIO_TogglePin(led_verde_GPIO_Port, led_verde_Pin);
  }
}

void menu(struct Forno *forno) {
  bool botaoPlaca;

  while (1) {
    botaoPlaca = HAL_GPIO_ReadPin(botao_placa_GPIO_Port, botao_placa_Pin);
    if (!botaoPlaca) {
      forno->proximo = demoTrocaDeEstado; // Esse botão é normalmente fechado, por isso o !
      return;
    }
    HAL_Delay(250);
    HAL_GPIO_TogglePin(led_verde_GPIO_Port, led_verde_Pin);
  }

  // Código de verdade:
  bool botaoMais = false, botaoMenos = false, botaoFuncao = false;

  while (1) {
    botaoMais = leBotao(botao_menu_mais_GPIO_Port, botao_menu_mais_Pin);
    botaoMenos = leBotao(botao_menu_menos_GPIO_Port, botao_menu_menos_Pin);
    botaoFuncao = leBotao(botao_menu_funcao_GPIO_Port, botao_menu_funcao_Pin);

    if (botaoMais || botaoMenos) {
      forno->proximo = defineTemperatura;
      return;
    }
    if (botaoFuncao) {
      forno->proximo = menuReceitas;
      return;
    }
  }
}

// TODO: Coisas pra melhorar nessa função:
/**
 * Os botões estão lendo "direto", então ao manter o dedo pressionado eles mudam a temperatura muito rápido
 * Uma solução básica pra arrumar isso é realizar a leitura a cada tantos milissegundos, ou, melhor ainda, adicionar um delay somente quando um botão for pressionado, pois assim a experiência fica mais fluida.
 * A solução mais topzera é codarmos alguma forma de que, ao manter o dedo pressionado, a mudança na temperatura começa devagar (ex: 10x por segundo) e vai "acelerando" conforme tu mantém o botão pressionado. Similar a como tem em algum eletrodomésticos
 */
void defineTemperatura(struct Forno *forno) {
  bool botaoMais = false, botaoMenos = false, botaoStart = false;
  char temperaturaTexto[10];

  while (1) {
    sprintf(temperaturaTexto, "%dºC", forno->temperaturaDesejada); // TODO: Testar se o º fica bonito no display

    display("Temperatura:");
    display(temperaturaTexto);

    botaoMais = leBotao(botao_menu_mais_GPIO_Port, botao_menu_mais_Pin);
    botaoMenos = leBotao(botao_menu_menos_GPIO_Port, botao_menu_menos_Pin);
    botaoStart = leBotao(botao_menu_start_GPIO_Port, botao_menu_start_Pin);

    if (botaoMais) forno->temperaturaDesejada += 1;
    if (botaoMenos) forno->temperaturaDesejada -= 1;
    if (botaoStart) forno->proximo = defineTempo;
  }
}

void defineTempo(struct Forno *forno) {
}

void menuReceitas(struct Forno *forno) {
  char receitas[3][20] = {
      "Frango",
      "Carne",
      "Peixe"};

  int resultado = exibeMenu(receitas);
  // TODO: Usa esse índice que a função exibeMenu retorna e define o tempo de cozimento e temperatura
}