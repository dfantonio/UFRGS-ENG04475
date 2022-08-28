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
  funcaoDoEstado *proximo;
  enum Estados estado;
  long tempo;
  struct Eleitor eleitor;
  struct Candidato candidatos[3][7]; // Linha: cargos, Coluna: candidatos
  bool flagTimeoutVotacao;
};
