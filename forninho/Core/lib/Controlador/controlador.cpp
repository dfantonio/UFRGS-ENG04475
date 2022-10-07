#include "main.h"
#include "dados.h"

void controleTemperatura(struct Forno *forno)
{
    int Ud = 0, Up = 0, y = 0, u = 0, erro = 0, Kp = 300, Kd = 50, referenciaTensao = 0;
    // referenciaTensao = ((-0.003035714) * forno->temperaturaDesejada + 1.422857) * 1000; // Equação retirada da curva de tensão x temperatura do diodo
    // referenciaTensao = ((0.0172) * forno->temperaturaDesejada + 1.7433) * 1000; // Equação retirada da curva de tensão x temperatura do diodo
    referenciaTensao = ((0.0161) * forno->temperaturaDesejada + 1.3694) * 1000;
    y = 3300 * (forno->temperaturaAtual) / 4095; // Conversão da leitura do ADC para a tensão lida
    erro = referenciaTensao - y;
    Up = Kp * erro;
    Ud = Kd * (erro - forno->erroAnterior);
    forno->erroAnterior = erro;

    u = Up + Ud;

    if (u >= 18000)
        u = 18000;
    if (u <= 0)
    {
        u = 0;
    }
    forno->sinalControle = u;
    TIM2->CCR1 = u;
}
// 1,82 - ambiente