#include "main.h"

// Função que tranca o código até o botão ser pressionado
bool leBotao(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

// Função que lê o valor instantâneo do botão e retorna
bool leBotaoInstantaneo(GPIO_TypeDef *GPIOx, uint16_t Pino);
