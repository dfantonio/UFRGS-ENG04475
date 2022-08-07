// Arquivo que contém todas as estruturas de dados necessárias

typedef void state_fn(struct Urna *);

struct Urna {
  state_fn *proximo;
  int i;
};
