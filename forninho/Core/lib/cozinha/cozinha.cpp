#include "dados.h"
#include "estados.h"
#include "display.h"

void configuraReceita(struct Forno *forno)
{
    int tempoReceitas[3][3] = {
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
        forno->estagioReceita = 1;
    }
    if ((tempoTotal[forno->receita] - forno->tempoFaltando) > tempoReceitas[forno->estagioReceita][forno->receita])
    {
        forno->estagioReceita += 1;
        if (forno->estagioReceita > 3)
        {
            forno->proximo = menu;
            forno->estagioReceita = 0;
        }
    }
    return;
}