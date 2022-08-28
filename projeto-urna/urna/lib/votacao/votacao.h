// Recebe o candidato que a pessoa escolheu
void recebeCandidato(char cargo[], char codigoModulo[], char eleitor[], char *candidato, char *partido);
// Conta os votos e registra os candidatos
void contabilizaVoto(struct Candidato candidatos[3][7], char candidato[], int cargo, char partido[]);
// Processo de votação
void votacao(struct Urna *urna, char eleitor[]);