#include "dados.h"
#include "estados.h"
#include "display.h"
#include "main.h"
#include "stdio.h"

void configuraReceita(struct Forno *forno)
{
    int tempoReceitas[3][3] = {
        // fim de cada etapa
        {3600 * 1, 3600 * 2, 3600 * 2},           // etapa de cozimento 1
        {3600 * 3, 3600 * 3, 3600 * 3 + 30 * 60}, // etapa de cozimento 2
        {3600 * 4, 3600 * 0, 3600 * 0},           // etapa de cozimento 3
    };

    int temperaturas[3][3] = {
        {180, 210, 120}, // etapa de cozimento 1
        {150, 165, 75},  // etapa de cozimento 2
        {120, 0, 0},     // etapa de cozimento 3
    };

    int tempoGrill[3] = {3600 * 2 + 10 * 60, 3600 * 1 + 10 * 60, 3600 * 1 + 40 * 60}; // grill

    int tempoTotal[3] = {4 * 3600, 3 * 3600, 3 * 3600 + 30 * 60};

    if (forno->estagioReceita == 0)
    {
        forno->tempoFaltando = tempoTotal[forno->receita];
        forno->temperaturaDesejada = temperaturas[forno->estagioReceita][forno->receita];
        forno->estagioReceita = 1;
    }

    if (forno->tempoFaltando == tempoGrill[forno->receita])
    {
        // Liga Led Grill
        HAL_GPIO_WritePin(led_grill_GPIO_Port, led_grill_Pin, GPIO_PIN_SET);
    }
    if (forno->tempoFaltando == 0)
    {
        // Desliga Led Grill
        HAL_GPIO_WritePin(led_grill_GPIO_Port, led_grill_Pin, GPIO_PIN_RESET);
    }

    if ((tempoTotal[forno->receita] - forno->tempoFaltando) >= tempoReceitas[forno->estagioReceita - 1][forno->receita])
    {
        if (forno->estagioReceita < 3)
        {
            forno->temperaturaDesejada = temperaturas[forno->estagioReceita][forno->receita];
            forno->estagioReceita += 1;
            return;
        }
        else
        {
            forno->estagioReceita = 0;
            return;
        }
    }
    return;
}