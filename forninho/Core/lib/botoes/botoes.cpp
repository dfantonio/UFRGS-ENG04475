#include "main.h"

bool leBotaoInstantaneo(GPIO_TypeDef *GPIOx, uint16_t Pino) {
  return HAL_GPIO_ReadPin(GPIOx, Pino);
}

bool leBotao(GPIO_TypeDef *GPIOx, uint16_t Pino) {
  bool estadoAnterior, estadoAtual;
  uint32_t tempoAnterior, tempoAtual;

  tempoAnterior = HAL_GetTick();
  estadoAnterior = false;

  while (1) {
    estadoAtual = HAL_GPIO_ReadPin(GPIOx, Pino);
    tempoAtual = HAL_GetTick();

    if (estadoAtual != estadoAnterior) {
      estadoAnterior = estadoAtual;
      tempoAnterior = tempoAtual;
    }

    if (estadoAtual && (tempoAtual - tempoAnterior) > 10) // Caso o botão esteja pressionado há mais de 10ms
      return true;
  }
}
