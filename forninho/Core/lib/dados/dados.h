// Arquivo que contém todas as estruturas de dados necessárias

typedef void funcaoDoEstado(struct Forno *);

struct Forno
{
  funcaoDoEstado *proximo;
  int tempoFaltando;
  int tempoGrill;
  int temperaturaDesejada;
  float temperaturaAtual;
  int estagioReceita; // 0 = sem receita; 1,2 e 3 = etapas de cozimento 1, 2 e 3; 4 = grill
  int receita;
  bool contagemAtiva;
};
