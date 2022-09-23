#include "botoes.h"
#include "dados.h"
#include "display.h"
#include "main.h"
#include "menu.h"
#include "tempo.h"
#include <stdio.h>

void demoTrocaDeEstado(struct Forno *forno);
void defineTemperatura(struct Forno *forno);
void defineTempo(struct Forno *forno);
void menuReceitas(struct Forno *forno);
void menu(struct Forno *forno);
void exibeRelogio(struct Forno *forno);

void menu(struct Forno *forno) {
  bool botaoMais = false, botaoMenos = false, botaoFuncao = false;

  while (1) {
    botaoMais = leBotaoInstantaneo(botao_menu_mais_GPIO_Port, botao_menu_mais_Pin);
    botaoMenos = leBotaoInstantaneo(botao_menu_menos_GPIO_Port, botao_menu_menos_Pin);
    botaoFuncao = leBotaoInstantaneo(botao_menu_funcao_GPIO_Port, botao_menu_funcao_Pin);

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
  uint32_t tempoAtual, tempoUltimaAtualizacao = 0;
  char temperaturaTexto[10];

  forno->temperaturaDesejada = 180;

  while (1) {
    HAL_Delay(50); // TODO: Tirar esse delay e melhorar a lógica
    tempoAtual = HAL_GetTick();

    if (passouIntervalo(&tempoUltimaAtualizacao, tempoAtual, 1000)) {
      limpaLCD();
      sprintf(temperaturaTexto, "%d C", forno->temperaturaDesejada);
      display("Temperatura:");
      display(temperaturaTexto, 1);
    }

    botaoMais = leBotaoInstantaneo(botao_menu_mais_GPIO_Port, botao_menu_mais_Pin);
    botaoMenos = leBotaoInstantaneo(botao_menu_menos_GPIO_Port, botao_menu_menos_Pin);
    botaoStart = leBotaoInstantaneo(botao_menu_start_GPIO_Port, botao_menu_start_Pin);

    if (botaoMais) forno->temperaturaDesejada += 1;
    if (botaoMenos) forno->temperaturaDesejada -= 1;
    if (botaoStart) {
      forno->proximo = defineTempo;
      return;
    }
  }
}

void defineTempo(struct Forno *forno) {
  bool botaoMais = false, botaoMenos = false, botaoStart = false;
  uint32_t tempoAtual, tempoUltimaAtualizacao = 0;
  char tempoStr[10];

  forno->tempoGrill = 60;
  forno->tempoFaltando = 10 * 60;
  forno->contagemAtiva = true;

  while (1) {
    HAL_Delay(50); // TODO: Tirar esse delay e melhorar a lógica
    tempoAtual = HAL_GetTick();

    if (passouIntervalo(&tempoUltimaAtualizacao, tempoAtual, 1000)) {
      limpaLCD();
      display("Tempo:");
      formataTempo(tempoStr, forno->tempoFaltando);
      display(tempoStr, 1);
    }

    botaoMais = leBotaoInstantaneo(botao_menu_mais_GPIO_Port, botao_menu_mais_Pin);
    botaoMenos = leBotaoInstantaneo(botao_menu_menos_GPIO_Port, botao_menu_menos_Pin);
    botaoStart = leBotaoInstantaneo(botao_menu_start_GPIO_Port, botao_menu_start_Pin);

    if (botaoMais) forno->tempoFaltando += 60;
    if (botaoMenos) forno->tempoFaltando -= 60;
    if (botaoStart) {
      forno->proximo = exibeRelogio;
      return;
    }
  }
}

void exibeRelogio(struct Forno *forno) {
  char tempoStr[10];
  bool botaoStart = false;
  uint32_t tempoAtual, tempoUltimaAtualizacao;
  uint32_t tempoBotaoPressionado, botaoUltimoEstado = false;

  tempoAtual = HAL_GetTick();
  tempoUltimaAtualizacao = HAL_GetTick();
  tempoBotaoPressionado = HAL_GetTick();

  while (1) {
    tempoAtual = HAL_GetTick();
    botaoStart = leBotaoInstantaneo(botao_menu_start_GPIO_Port, botao_menu_start_Pin);

    if (botaoStart && botaoUltimoEstado == false) {
      botaoUltimoEstado = true;
      tempoBotaoPressionado = tempoAtual;
    }
    if (!botaoStart && botaoUltimoEstado == true) {
      botaoUltimoEstado = false;
      if ((tempoAtual - tempoBotaoPressionado) > 3000) forno->proximo = menu;
      else
        forno->contagemAtiva = false;
    }

    if (passouIntervalo(&tempoUltimaAtualizacao, tempoAtual, 1000)) { // Lógica pro display não ficar atualizando toda hora
      limpaLCD();
      display("tempo restante:");
      formataTempo(tempoStr, forno->tempoFaltando);
      display(tempoStr, 1);
    }
  }
}

void menuReceitas(struct Forno *forno) {
  char receitas[3][20] = {
      "Frango",
      "Carne",
      "Peixe"};

  int resultado = exibeMenu(receitas);
  // TODO: Usa esse índice que a função exibeMenu retorna e define o tempo de cozimento e temperatura
}