// Envia string para votos, identificação e respostas
void enviaStringModulo(char primeiro[], char n[], char codigo[]);
// Verificação do sistema
void verifica(int hora, int min, int votos);
// Recebe a resposta do modulo
void recebeSerialModulo(char *str);
// Recebe a hora do modulo
long recebeHora();
// Verifica a urna
void verifica(int hora, int min, int votos);
// Desembaralha strings
void desembaralha(char embaralhado[], char *eleitor, char *candidato, char *partido);