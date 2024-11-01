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

    liberarNO(bombaAtual);
    return caixa;
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

int verificarComposicao(Kit *kit, Composicao *composicao, int numBombas){
    NO *bombaAtual = *kit;
    while(bombaAtual != NULL) {
        Bomba b = bombaAtual->bomba;
        int encontrada = 0;

        for(int i=0; i<numBombas; i++){
            if(strcmp(b.cor, composicao[i].cor) == 0 && b.comprimento == composicao[i].comprimento){
                composicao[i].quantidade--;
                encontrada = 1;
                if(composicao[i]. quantidade < 0){
                    printf("Existe bomba %d%s a mais!\n", composicao[i].comprimento, composicao[i].cor);
                    return 0;
                }
                break;
            }
        }

        if(!encontrada){
            printf("Bomba %d%s desconhecida!\n", b.comprimento, b.cor);
            return 0;
        }

        bombaAtual = bombaAtual->prox;
    }
    
    for(int i=0; i<numBombas; i++){ //verifica se tem bomba faltando
        if(composicao[i].quantidade > 0){
            printf("Falta bomba %d%s!\n", composicao[i].comprimento, composicao[i].cor);
                    return 0;
        }
    }

    return 1;
}

int verificarSobreposicao(Kit *kit){
    NO *aux = *kit;

    while(aux != NULL){
        NO *aux2 = aux->prox;

        while(aux2 != NULL){
            if (!(aux->bomba.xFinal < aux2->bomba.xInicial ||
                aux2->bomba.xFinal < aux->bomba.xInicial ||
                aux->bomba.yFinal < aux2->bomba.yInicial ||
                aux2->bomba.yFinal < aux->bomba.yInicial)){
                    printf("BOOM! Sobreposicao detectada: %d%s e %d%s\n", 
                            aux->bomba.comprimento, aux->bomba.cor, 
                            aux2->bomba.comprimento, aux2->bomba.cor);
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
        Bomba b = aux->bomba;

        if (b.xInicial < 1 || b.xInicial > colunas ||
            b.yInicial < 1 || b.yInicial > colunas ||
            b.xFinal < 1 || b.xFinal > colunas || 
            b. yFinal< 1 || b.yFinal > colunas){
                printf("BOOM! Seu kit nao cabe corretamente na caixa. A bomba %d%s ultrapassa os limites!\n", b.comprimento, b.cor);
                return 0;
        }
        aux = aux->prox;
    }
    return 1;
}

//tem que dar free nos auxs?