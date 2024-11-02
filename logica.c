#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kitBoom.h"

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

NO* alocarBomba () {
    return (NO *) malloc ( sizeof (NO));
}

void liberarBomba (NO* q){
    free (q);
}

int insereBomba(Kit *k, Bomba bomba){
    if(k==NULL) return 0;
    NO* novo = alocarBomba();
    if(novo == NULL) {
        printf("Erro ao alocaro nó!\n");
        return 0;
    }
    novo->bomba = bomba;
    novo->prox = *k;
    *k = novo;
    return 1;
}

void liberarKit(Kit *k){
    if(k != NULL){
        NO *aux;
        while((*k)!=NULL){
            aux = *k;
            *k = (*k)->prox;
            liberarBomba(aux);
        }
        free(k);
    }
}


Par **alocarCaixa(int linhas, int colunas) {
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

void liberarCaixa(Par **matriz, int linhas) {
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

Par** montarCaixa(Kit *kit,int linhas, int colunas) {
    Par **caixa = alocarCaixa(linhas, colunas);
    if(caixa == NULL){
        printf("Erro ao alocar a matriz caixa.\n");
        return NULL;
    }
    
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) { 
            strcpy(caixa[i][j].cor, "NULL");
            caixa[i][j].nome = 0;
        }
    }

    NO *bombaAtual = *kit;
    while(bombaAtual != NULL){
        Bomba b = bombaAtual->bomba;

        for(int i=b.xInicial-1; i<b.xFinal;i++){
            for(int j=b.yInicial-1; j<b.yFinal;j++){
                if(i >= 0 && i < linhas && j >= 0 && j < colunas){
                    strcpy(caixa[i][j].cor, b.cor);
                    caixa[i][j].nome = b.nome;
                }
            }
        }
        bombaAtual = bombaAtual -> prox;
    }

    liberarBomba(bombaAtual);
    return caixa;
}

int validarComposicao(Kit *kit, int quantidade, int comprimento, char *cor){
    int bombasEncontradas = 0;

    NO *bombaAtual = *kit;
    while(bombaAtual != NULL) {
        Bomba b = bombaAtual->bomba;
        if(strcmp(b.cor, cor) == 0 && b.comprimento == comprimento){
            bombasEncontradas++;
        }
        bombaAtual = bombaAtual->prox;
    }

    if(bombasEncontradas > quantidade){
        printf("Existe(m) bomba(s) %d%s a mais em sua configuracao!\n", comprimento, cor);
        return 0;
    }else if(bombasEncontradas < quantidade){
        printf("Composicao incompleta: falta(m) bomba(s) %d%s em sua configuracao!\n", comprimento, cor);
        return 0;
    }
    return 1;
}

int validarAdjacencia(Par **caixa, int linhas, int colunas){
    for(int i=0; i<linhas;i++){
        for(int j=0; j<colunas;j++){
            if(i-1 >= 0 && caixa[i-1][j].nome != caixa[i][j].nome){
                if(strcmp(caixa[i-1][j].cor,caixa[i][j].cor)==0){
                    printf("Bomba %d e Bomba %d estao adjacentes e sao de mesma cor!\n",caixa[i-1][j].nome,caixa[i][j].nome);
                    return 0;
                }
            }
            if(j+1 < colunas && caixa[i][j+1].nome != caixa[i][j].nome){
                if(strcmp(caixa[i][j+1].cor,caixa[i][j].cor)==0){
                    printf("Bomba %d e Bomba %d estao adjacentes e sao de mesma cor!\n",caixa[i][j+1].nome,caixa[i][j].nome);
                    return 0;
                }
            }
            if(i+1 < linhas && caixa[i+1][j].nome != caixa[i][j].nome){
                if(strcmp(caixa[i+1][j].cor, caixa[i][j].cor)==0){
                    printf("Bomba %d e Bomba %d estao adjacentes e sao de mesma cor!\n",caixa[i+1][j].nome,caixa[i][j].nome);
                    return 0;
                }
            }
            if(j-1 >= 0 && caixa[i][j-1].nome != caixa[i][j].nome && j-1>=0){
                if(strcmp(caixa[i][j-1].cor, caixa[i][j].cor)==0){
                    printf("Bomba %d e Bomba %d estao adjacentes e sao de mesma cor!\n",caixa[i][j-1].nome,caixa[i][j].nome);
                    return 0;
                }
            }
        }
    }
    return 1;
}

int validarSobreposicao(Kit *kit){
    NO *aux = *kit;

    while(aux != NULL){
        NO *aux2 = aux->prox;

        while(aux2 != NULL){
            if (!(aux->bomba.xFinal < aux2->bomba.xInicial ||
                aux2->bomba.xFinal < aux->bomba.xInicial ||
                aux->bomba.yFinal < aux2->bomba.yInicial ||
                aux2->bomba.yFinal < aux->bomba.yInicial)){
                    printf("BOOM! Sobreposicao detectada: Bomba %d(%s) e Bomba %d(%s)\n", 
                            aux->bomba.nome, aux->bomba.cor, 
                            aux2->bomba.nome, aux2->bomba.cor);
                    return 0;
                }
            aux2 = aux2->prox;
        }
        aux = aux->prox;
    }
    return 1;
}

int validarCoordenadas(Kit *kit, int linhas, int colunas){
    NO *aux = *kit;
    
    while(aux != NULL){
        Bomba atual = aux->bomba;

        if (atual.xInicial < 1 || atual.xInicial > colunas ||
            atual.yInicial < 1 || atual.yInicial > colunas ||
            atual.xFinal < 1 || atual.xFinal > colunas || 
            atual.yFinal< 1 || atual.yFinal > colunas){
                printf("BOOM! Seu kit nao cabe corretamente na caixa. A bomba %d(%s) ultrapassa os limites!\n", atual.nome, atual.cor);
                return 0;
        }
        aux = aux->prox;
    }
    return 1;
}