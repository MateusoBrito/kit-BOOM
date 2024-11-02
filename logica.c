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

int validarAdjacencia2(Kit *kit){
    NO *aux = *kit;

    // Itera por cada bomba no kit
    while (aux != NULL) {
        NO *aux2 = aux->prox;

        // Compara a bomba atual com todas as bombas subsequentes
        while (aux2 != NULL) {
            // Verifica se as bombas são adjacentes
            if(strcmp(aux->bomba.cor, aux2->bomba.cor)==0){
                int adjacente = 
                (aux->bomba.xFinal + 1 == aux2->bomba.xInicial && aux->bomba.yFinal == aux2->bomba.yInicial) || // direita
                (aux->bomba.xInicial - 1 == aux2->bomba.xFinal && aux->bomba.yInicial == aux2->bomba.yFinal) || // esquerda
                (aux->bomba.yFinal + 1 == aux2->bomba.yInicial && aux->bomba.xFinal == aux2->bomba.xInicial) || // abaixo
                (aux->bomba.yInicial - 1 == aux2->bomba.yFinal && aux->bomba.xInicial == aux2->bomba.xFinal);   // acima

                // Se forem adjacentes e da mesma cor, retorna erro de adjacência
                if (adjacente) {
                    printf("BOMBA! As bombas %d%s e %d%s estão adjacentes e têm a mesma cor!\n", 
                            aux->bomba.comprimento, aux->bomba.cor, 
                            aux2->bomba.comprimento, aux2->bomba.cor);
                }
            }   
        
            aux2 = aux2->prox;
        }
        aux = aux->prox;
    }
    return 1; // Retorna 1 se não houver bombas adjacentes de mesma cor
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

int validarComposicao(Kit *kit, Composicao *composicao, int numBombas){
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

int validarSobreposicao(Kit *kit){
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