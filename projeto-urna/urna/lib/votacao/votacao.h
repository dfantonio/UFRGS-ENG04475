// Processo de votação
void votacao(struct Urna *urna);

// Verifica se o eleitor já votou
bool eleitorValido(struct Urna *urna, int matricula);

// Adiciona um eleitor na lista de que já votaram
void adicionaEleitorLista(struct Urna *urna, int matricula);