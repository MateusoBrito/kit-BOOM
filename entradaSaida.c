#include <stdio.h>
#include <stdlib.h>
#include "kitBoom.h"
#include <string.h>

int converteCorParaNumero(char *cor){
    if(strcmp(cor, "Az") == 0) return 1;
    if(strcmp(cor, "Vm") == 0) return 2;
    if(strcmp(cor, "Am") == 0) return 3;
    if(strcmp(cor, "Vd") == 0) return 4;
    return 0;
}

Kit *criarKit(){
    Kit *k;
    k = (Kit*) malloc (sizeof(Kit));
    if(k != NULL){
        *k = NULL;
    }
    return k;
}

int kitVazio (Kit *k){
    if(k == NULL ) 
        return -1;
    if (*k == NULL )
        return 1;
    return 0; 
}

NO* alocarNO () {
return (NO *) malloc ( sizeof (NO));
}

void liberarNO (NO* q){
free (q);
}

int insereBomba(Kit *k, Bomba bomba){
    if(k==NULL) return 0;
    NO* novo = alocarNO();
    if(novo == NULL) {
        printf("Erro ao alocaro nó!\n");
        return 0;
    }
    novo->bomba = bomba;
    novo->prox = *k;
    *k = novo;
    return 1;
}

void liberaKit(Kit *k){
    if(k != NULL){
        NO *aux;
        while((*k)!=NULL){
            aux = *k;
            *k = (*k)->prox;
            liberarNO(aux);
        }
        free(k);
    }
}

Kit* leituraConfiguracao(char* fileConfiguracao){
    FILE *arquivo = fopen(fileConfiguracao, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de configuracao\n");
        return NULL;
    }

    Kit *kit = criarKit();
    Bomba bomba; //liberar este espaco de memoria?

    int i=1;
    while (!feof(arquivo)) {
        fscanf(arquivo, "%d %d %d %d %d%s", &bomba.xInicial, &bomba.yInicial,
               &bomba.xFinal, &bomba.yFinal,&bomba.comprimento,bomba.cor);
        bomba.nome = i;
        insereBomba(kit, bomba);
        i++;
    }

    fclose(arquivo);
    return kit;
}

Composicao *leituraComposicao(char *fileComposicao, int *numBombas){
    FILE *arquivo = fopen(fileComposicao, "r");
    if(!arquivo){
        printf("Erro ao abrir o arquivo de composicao\n");
        return NULL;
    }

    Composicao *composicao = malloc(sizeof(Composicao)*36);
    *numBombas = 0;
    int completeza = 0;

    while(!feof(arquivo)){
        fscanf(arquivo, "%d %d%s", &composicao[*numBombas].quantidade, 
                &composicao[*numBombas].comprimento, composicao[*numBombas].cor);
        completeza += (composicao[*numBombas].quantidade * composicao[*numBombas].comprimento);
        (*numBombas)++;
    }

    fclose(arquivo);
    
    if(completeza < 36){
        printf("Erro na completeza do kit: ha espacos nao preenchidos na caixa.\n");
        return 0;
    }else if(completeza > 36){
        //VOLTAR: BOMBAS SOBREPOSTAS OU VAZANDO DA CAIXA
    }

    /*
    printf("Composicao lida:\n");
    for (int i = 0; i < *numBombas; i++) {
        printf("Bomba %d: Comprimento = %d, Quantidade = %d, Cor = %s\n",
               i + 1, composicao[i].comprimento, 
               composicao[i].quantidade, composicao[i].cor);
    }
    */

    return composicao;
}

Par **alocarMatriz(int linhas, int colunas) {
    Par **matriz = (Par **)malloc(linhas * sizeof(Par *));

    if (matriz == NULL) {
        printf("Erro ao alocar memória para as linhas da matriz.\n");
        return 0;
    }
    for (int i = 0; i < linhas; i++) {
        matriz[i] = (Par *)malloc((2*colunas) * sizeof(Par));
        if (matriz[i] == NULL) {
            printf("Erro ao alocar memória para a coluna %d.\n", i);
            return 0;
        }
    }

    return matriz;
}

void liberarMatriz(int **matriz, int linhas) {
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

Par** montarCaixa(Kit *kit,int linhas, int colunas) {
    Par **caixa = alocarMatriz(linhas, colunas);
    if(caixa == NULL){
        printf("Erro ao alocar a matriz caixa.\n");
        return NULL;
    }
    
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            caixa[i][j].cor = 0;
            caixa[i][j].nome = 0;
        }
    }

    NO *bombaAtual = *kit;
    while(bombaAtual != NULL){
        Bomba b = bombaAtual->bomba;
        int corNumero = converteCorParaNumero(b.cor);

        for(int i=b.xInicial-1; i<b.xFinal;i++){
            for(int j=b.yInicial-1; j<b.yFinal;j++){
                if(i >= 0 && i < linhas && j >= 0 && j < colunas){
                    caixa[i][j].cor = corNumero;
                    caixa[i][j].nome = b.nome;
                }
            }
        }
        bombaAtual = bombaAtual -> prox;
    }

    liberarNO(bombaAtual);
    return caixa;
}

/*
Bomba*** montarCaixa2(Kit *kit,int linhas, int colunas) {
    Bomba ***caixa = alocarMatriz(linhas, colunas);
    if(caixa == NULL){
        printf("Erro ao alocar a matriz caixa.\n");
        return NULL;
    }
    
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            caixa[i][j] = NULL;
        }
    }

    NO *bombaAtual = *kit;
    while(bombaAtual != NULL){
        Bomba *b = &(bombaAtual->bomba);

        for(int i=b->xInicial-1; i<b->xFinal;i++){
            for(int j=b->yInicial-1; j<b->yFinal;j++){
                if(i >= 0 && i < linhas && j >= 0 && j < colunas){
                    caixa[i][j] = b;

                }
            }
        }
        bombaAtual = bombaAtual -> prox;
    }

    liberarNO(bombaAtual);
    return caixa;
}
*/

void imprimirMatriz(Par **matriz, int linhas, int colunas) {
    printf("Caixa de Bombas:\n");
    printf("(nome,cor)\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("(%d,%d) ", matriz[i][j].nome, matriz[i][j].cor); 
        }
        printf("\n");
    }
}