const int segA = 0;
const int segB = 1;
const int segC = 2;
const int segD = 3;
const int segE = 4;
const int segF = 5;
const int segG = 6;

const int bot1pin = 9;
const int bot2pin = 10;
const int bot3pin = 11;

unsigned long ultimaPiscada = 0; // Armazena quando o led piscou pela última vez
unsigned long intervalo = 1000;  // Intervalo para piscar o led em ms

int led = LOW; // Estado atual do led

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  // Define os segmentos do display como saida
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);

  // Define os botões como entrada
  pinMode(bot1pin, INPUT);
  pinMode(bot2pin, INPUT);
  pinMode(bot3pin, INPUT);
}

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

void loop() {
  int bot1 = digitalRead(bot1pin);
  int bot2 = digitalRead(bot2pin);
  int bot3 = digitalRead(bot3pin);

  unsigned long tempoAtual = millis();

  if (bot1) {
    setDigito(1);
    intervalo = 5;
  }
  if (bot2) {
    setDigito(2);
    intervalo = 2;
  }
  if (bot3) {
    setDigito(3);
    intervalo = 1;
  }

  if (tempoAtual - ultimaPiscada >= intervalo) {
    // save the last time you blinked the LED
    ultimaPiscada = tempoAtual;

    // if the LED is off turn it on and vice-versa:
    if (led == LOW) {
      led = HIGH;
    } else {
      led = LOW;
    }

    // set the LED with the led of the variable:
    digitalWrite(LED_BUILTIN, led);
  }
}
