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
NO* alocarBomba();
void liberarBomba(NO *q);
int insereBomba(Kit *k, Bomba bomba);
void liberarKit(Kit *k);
Kit* leituraConfiguracao(char *fileConfiguracao);
Composicao* leituraComposicao(char* fileComposicao, int *numBombas);
Par **alocarCaixa(int linhas, int colunas);
void liberarCaixa(Par **matriz, int linhas);
Par **montarCaixa(Kit *kit, int linhas, int colunas);
void imprimirCaixa(Par **matriz, int linhas, int colunas);
int validarAdjacencia(Par **caixa, int linhas, int colunas);
int validarComposicao(Kit *kit, Composicao *composicao, int numBombas);
int validarSobreposicao(Kit *kit);
int validarCoordenadas(Kit *kit, int linhas, int colunas);
void imprimirCabecalho();
void imprimirSaida(int validezComposicao, int validezSobreposicao,int validezCoordenadas,int validezAdjacencia);

#endif