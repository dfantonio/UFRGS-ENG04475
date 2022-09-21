#include "dados.h"
#include "main.h"

void menu(struct Forno *forno) {

  while (1) {
    HAL_Delay(200);
    HAL_GPIO_TogglePin(led_verde_GPIO_Port, led_verde_Pin);
  }
}