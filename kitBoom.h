#ifndef KITBOOM_H
#define KITBOOM_H

typedef struct {
    int nome;
    int xInicial, yInicial, xFinal, yFinal;
    int comprimento;
    char cor[3];
} Bomba;

typedef struct NO{
    Bomba bomba;
    struct NO *prox;
} NO;

typedef struct NO* Kit;

typedef struct Par{
    char cor[3];
    int nome;
} Par;

typedef struct {
    int quantidade;
    int comprimento;
    char cor[3];
} Composicao;

Kit *criarKit();
int kitVazio(Kit *k);
NO* alocarNO();
void liberarNO(NO *q);
int insereBomba(Kit *k, Bomba bomba);
void liberaKit(Kit *k);
Kit* leituraConfiguracao(char *fileConfiguracao);
int converteCorParaNumero(char *cor);
Par **alocarCaixa(int linhas, int colunas);
void liberarCaixa(Par **matriz, int linhas);
Par **montarCaixa(Kit *kit, int linhas, int colunas);
void imprimirCaixa(Par **matriz, int linhas, int colunas);
int validarAdjacencia(Par **caixa, int linhas, int colunas);
Composicao* leituraComposicao(char* fileComposicao, int *numBombas);
int verificarComposicao(Kit *kit, Composicao *composicao, int numBombas);
int verificarSobreposicao(Kit *kit);
int validarCoordenadas(Kit *kit, int linhas, int colunas);
void saidaResultado(int validezComposicao, int validezSobreposicao,int validezCoordenadas,int validezAdjacencia);

#endif