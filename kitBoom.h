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
    int cor;
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
Par **alocarMatriz(int linhas, int colunas);
void liberarMatriz(int **matriz, int linhas);
Par **montarCaixa(Kit *kit, int linhas, int colunas);
void imprimirMatriz(Par **matriz, int linhas, int colunas);
void validarAdjacencia(Par **caixa, int linhas, int colunas);
Composicao* leituraComposicao(char* fileComposicao, int *numBombas);
int verificarComposicao(Kit *kit, Composicao *composicao, int numBombas);

#endif