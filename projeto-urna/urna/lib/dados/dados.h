// Arquivo que contém todas as estruturas de dados necessárias

typedef void funcaoDoEstado(struct Urna *);

enum Estados {
  operacional,
  bloqueado,
  aguardando,
  encerrado
};

struct Eleitor {
  char nome[20];
  char codigo[6];
  int votos[3];
};

struct Urna {
  funcaoDoEstado *proximo;
  enum Estados estado;
  long tempo;
  struct Eleitor eleitor;
};
