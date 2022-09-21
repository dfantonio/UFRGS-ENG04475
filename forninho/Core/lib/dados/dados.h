// Arquivo que contém todas as estruturas de dados necessárias

typedef void funcaoDoEstado(struct Forno *);

struct Forno {
  funcaoDoEstado *proximo;
  int tempoFaltando;
  int tempoGrill;
};
