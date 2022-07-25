const int segA = 0;
const int segB = 1;
const int segC = 2;
const int segD = 3;
const int segE = 4;
const int segF = 5;
const int segG = 6;

const int bot0pin = 9;
const int bot1pin = 10;
const int bot2pin = 11;
const int ledPin = 13;

unsigned long ultimaPiscada = 0;   // Armazena quando o led piscou pela última vez
unsigned long intervalo = 1000000; // Intervalo para piscar o led em us

int led = LOW; // Estado atual do led

int botoesPosicao[] = {9, 10, 11};  // Array que possui o número dos pinos
unsigned long time[] = {0, 0, 0};   // Array que salva o tempo da última medição dos botões
int count[] = {0, 0, 0};            // Array que armazena a contagem de cada led
int entradasDebounce[] = {0, 0, 0}; // Array com as entradas aplicadas com debounce
int valorTemporario[] = {0, 0, 0};  // Array com os estados atuais das entradas

void setup() {
  pinMode(ledPin, OUTPUT);

  // Define os segmentos do display como saida
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);

  // Define os botões como entrada
  pinMode(bot0pin, INPUT);
  pinMode(bot1pin, INPUT);
  pinMode(bot2pin, INPUT);
}

// Seta os pinos do display pra formar os números
void setDigito(char numero) {
  switch (numero) {
  case 1:
    digitalWrite(segA, LOW);
    digitalWrite(segB, HIGH);
    digitalWrite(segC, HIGH);
    digitalWrite(segD, LOW);
    digitalWrite(segE, LOW);
    digitalWrite(segF, LOW);
    digitalWrite(segG, LOW);
    break;

  case 2:
    digitalWrite(segA, HIGH);
    digitalWrite(segB, HIGH);
    digitalWrite(segC, LOW);
    digitalWrite(segD, HIGH);
    digitalWrite(segE, HIGH);
    digitalWrite(segF, LOW);
    digitalWrite(segG, HIGH);
    break;

  case 3:
    digitalWrite(segA, HIGH);
    digitalWrite(segB, HIGH);
    digitalWrite(segC, HIGH);
    digitalWrite(segD, HIGH);
    digitalWrite(segE, LOW);
    digitalWrite(segF, LOW);
    digitalWrite(segG, HIGH);
    break;
  }
}

int debounce(int pino) { // Função que recebe o índice do botão para calcular o debounce
  unsigned long tempoAtual = micros();
  unsigned long *ultimaVerificacao = &time[pino];    // Última vez que a entrada foi lida
  int valorAtual = digitalRead(botoesPosicao[pino]); // Valor atual da entrada
  int *valorTemp = &valorTemporario[pino];           // Valor intermediário (que precisa contar até 7 para se tornar o valor definitivo)
  int *contagem = &count[pino];                      // Contagem do respectivo pino

  // Caso já tenha passado mais de 1000 us (1 ms)
  if (tempoAtual - *ultimaVerificacao >= 1000) {
    // Atualiza a última vez q entrou
    *ultimaVerificacao = tempoAtual;

    // Caso o valor atual seja igual ao valor temporário aumenta a contagem. Caso contrário, zera
    if (valorAtual == *valorTemp) *contagem = *contagem + 1;
    else
      *contagem = 0;

    // Quando a contagem atinge o limite zera e atualiza o valor da saída.
    if (*contagem >= 7) {
      *contagem = 0;
      entradasDebounce[pino] = valorAtual; // Atualiza a entrada definitiva
    }
    *valorTemp = valorAtual;
  }
  return entradasDebounce[pino];
}

void loop() {
  int bot0 = debounce(0);
  int bot1 = debounce(1);
  int bot2 = debounce(2);

  unsigned long tempoAtual = micros();

  if (bot0) {
    setDigito(1);
    intervalo = 5000;
  }
  if (bot1) {
    setDigito(2);
    intervalo = 2500;
  }
  if (bot2) {
    setDigito(3);
    intervalo = 1667;
  }

  // Caso já tenha passado tempo suficiente desde a última piscada
  if (tempoAtual - ultimaPiscada >= intervalo) {
    // Salva a última vez q piscou
    ultimaPiscada = tempoAtual;

    // Inverte o estado do led
    if (led == LOW) {
      led = HIGH;
    } else {
      led = LOW;
    }

    // atualiza a saída do led
    digitalWrite(ledPin, led);
  }
}
