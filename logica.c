#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kitBoom.h"



//mudar nome da funcao
void validarAdjacencia(Par **caixa, int linhas, int colunas){
    for(int i=0; i<linhas;i++){
        for(int j=0; j<colunas;j++){
            if(i-1 >= 0 && caixa[i-1][j].nome != caixa[i][j].nome){
                if(caixa[i-1][j].cor == caixa[i][j].cor ){
                    printf("Bomba %d e Bomba %d estao adjacentes e sao de mesma cor!\n",caixa[i-1][j].nome,caixa[i][j].nome);
                }
            }
            if(j+1 < colunas && caixa[i][j+1].nome != caixa[i][j].nome){
                if(caixa[i][j+1].cor == caixa[i][j].cor ){
                    printf("Bomba %d e Bomba %d estao adjacentes e sao de mesma cor!\n",caixa[i][j+1].nome,caixa[i][j].nome);
                }
            }
            if(i+1 < linhas && caixa[i+1][j].nome != caixa[i][j].nome){
                if(caixa[i+1][j].cor == caixa[i][j].cor ){
                    printf("Bomba %d e Bomba %d estao adjacentes e sao de mesma cor!\n",caixa[i+1][j].nome,caixa[i][j].nome);
                }
            }
            if(j-1 >= 0 && caixa[i][j-1].nome != caixa[i][j].nome && j-1>=0){
                if(caixa[i][j-1].cor == caixa[i][j].cor ){
                    printf("Bomba %d e Bomba %d estao adjacentes e sao de mesma cor!\n",caixa[i][j-1].nome,caixa[i][j].nome);
                }
            }
        }
    }
    return;
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