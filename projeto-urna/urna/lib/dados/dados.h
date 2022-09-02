// Arquivo que contém todas as estruturas de dados necessárias

typedef void funcaoDoEstado(struct Urna *);

#define N_CANDIDATO_LINHAS  3
#define N_CANDIDATO_COLUNAS 7

enum Estados {
  operacional,
  bloqueado,
  aguardando,
  encerrado
};

struct Eleitor {
  char nome[20];
};

enum Cargos {
  Presidente,
  Governador,
  Senador
};

struct Candidato {
  char codigo[3];
  int votos;
};

struct Urna {
  funcaoDoEstado *proximo;
  enum Estados estado;
  long tempo;
  struct Eleitor eleitor;
  struct Candidato candidatos[N_CANDIDATO_LINHAS][N_CANDIDATO_COLUNAS]; // Linha: cargos, Coluna: candidatos
  bool flagTimeoutVotacao;
};
