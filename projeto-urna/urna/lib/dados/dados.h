// Arquivo que contém todas as estruturas de dados necessárias

typedef void state_fn(struct Urna *);

struct Eleitor {
  char nome[20];
  char codigo[6];
  int votos[3];
};

struct Urna {
  state_fn *proximo;
  long tempo;
  struct Eleitor eleitor;
};
