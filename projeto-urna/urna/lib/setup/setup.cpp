#include "dados.h"
#include <avr/io.h>
#include <stdio.h>

typedef enum {
  TESTE, // aa
  ABC,   // teste
} estados;

estados a;

state_fn foo, bar;

void foo(struct Urna *urna) {
  printf("%s %i\n", __func__, ++urna->i);
  urna->next = bar;
}

void bar(struct Urna *urna) {
  printf("bar %i\n", ++urna->i);
  urna->next = urna->i < 11 ? foo : 0;
}

void setup() {
  UCSR0B |= 16 + 8; // Habilita recepção e transmissão serial (RXEN0 e TXEN0)
  UBRR0 = 103;      // Taxa 9600bps => 16MHz/(8*(URBR0+1))

  a = ABC;
}