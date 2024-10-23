#ifndef KITBOOM_H
#define KITBOOM_H

typedef struct {
    int xInicial, yInicial, xFinal, yFinal;
    int comprimento;
    char cor[3];
} Bomba;

typedef struct NO{
    Bomba bomba;
    struct NO *prox;
} NO;

typedef struct NO* Kit;

Kit *criarKit();
int kitVazio(Kit *k);
NO* alocarNO();
void liberarNO(NO *q);
int insereBomba(Kit *k, Bomba bomba);
void liberaKit(Kit *k);
Kit* leituraConfiguracao(char *fileConfiguracao);
int converteCorParaNumero(char *cor);
//int **alocarMatriz(int linhas, int colunas);
void liberarMatriz(int **matriz, int linhas);
int **montarCaixa(Kit *kit, int linhas, int colunas);
//void imprimirMatriz(int **matriz, int linhas, int colunas);
Bomba*** montarCaixa2(Kit *kit,int linhas, int colunas);
Bomba ***alocarMatriz(int linhas, int colunas);
void imprimirMatriz(Bomba ***matriz, int linhas, int colunas);
void validacaoAdjascente(Bomba ***caixa, int linhas, int colunas);

#endif