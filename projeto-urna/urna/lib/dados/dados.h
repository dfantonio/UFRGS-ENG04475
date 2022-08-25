// Arquivo que contém todas as estruturas de dados necessárias

typedef void state_fn(struct Urna *);

struct Eleitor {
  char nome[20];
  char codigo[6];
  int votos[3];
};

enum cargos {
  Presidente,
  Governador,
  Senador
};

struct Candidato {
  char nome[30];
  char partido[14];
  int votos;
};

struct Urna {
  state_fn *proximo;
  long tempo;
  struct Eleitor eleitor;
  struct Candidato candidatos[3][7]; // Linha: cargos, Coluna: candidatos
};
