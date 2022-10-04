#include "main.h"
#include "dados.h"
#include "main.cpp"

void controleTemperatura(struct Forno *forno, int referencia)
{
    int erro_ant = 0, Ud = 0, Up = 0, y = 0, u = 0, erro = 0, Kp = 10, Kd = 10;
    y = tensaoDiodo;
    erro = referencia - y;
    Up = Kp * erro;
    Ud = Kd * (erro - erro_ant);
    erro_ant = erro;

    u = Up + Ud;
    if (u >= 18000)
        u = 18000;
    if (u <= 0)
        u = 0;
    u = 18000 - u;
    TIM2->CCR1 = u;
}