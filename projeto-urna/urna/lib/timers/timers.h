// delay em us
void delayUs(int us);

// delay em ms (máximo 16ms)
void delayMs(int ms);

// Formata um número de segundos em hora:minutos
void formataTempo(char *str, long tempo);

// Troca de estados conforme o horário
void verificaHorario(struct Urna *urna);