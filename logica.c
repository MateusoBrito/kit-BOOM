#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kitBoom.h"



//mudar nome da funcao
void validarAdjascencia(Par **caixa, int linhas, int colunas){
    for(int i=0; i<linhas;i++){
        for(int j=0; j<colunas;j++){
            if(i-1 >= 0 && caixa[i-1][j].nome != caixa[i][j].nome){
                if(caixa[i-1][j].cor == caixa[i][j].cor ){
                    printf("Bomba %d e Bomba %d estao adjascente e sao de mesma cor!\n",caixa[i-1][j].nome,caixa[i][j].nome);
                }
            }
            if(j+1 < colunas && caixa[i][j+1].nome != caixa[i][j].nome){
                if(caixa[i][j+1].cor == caixa[i][j].cor ){
                    printf("Bomba %d e Bomba %d estao adjascente e sao de mesma cor!\n",caixa[i][j+1].nome,caixa[i][j].nome);
                }
            }
            if(i+1 < linhas && caixa[i+1][j].nome != caixa[i][j].nome){
                if(caixa[i+1][j].cor == caixa[i][j].cor ){
                    printf("Bomba %d e Bomba %d estao adjascente e sao de mesma cor!\n",caixa[i+1][j].nome,caixa[i][j].nome);
                }
            }
            if(j-1 >= 0 && caixa[i][j-1].nome != caixa[i][j].nome && j-1>=0){
                if(caixa[i][j-1].cor == caixa[i][j].cor ){
                    printf("Bomba %d e Bomba %d estao adjascente e sao de mesma cor!\n",caixa[i][j-1].nome,caixa[i][j].nome);
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

        for(int i=0; i<numBombas; i++){
            if(strcmp(b.cor, composicao[i].cor) == 0 && b.comprimento == composicao[i].comprimento){
                composicao[i].quantidade--;
                if(composicao[i]. quantidade < 0){
                    printf("Existe bomba %d%s a mais!\n", composicao[i].cor, composicao[i].comprimento);
                    return 0;
                }
            }
        }
        bombaAtual = bombaAtual->prox;
    }

    for(int i=0; i<numBombas; i++){ //verifica se tem bomba faltando
        if(composicao[i].quantidade > 0){
            printf("Falta bomba %d%s!\n", composicao[i].cor, composicao[i].comprimento);
                    return 0;
        }
    }

    return 1;
}