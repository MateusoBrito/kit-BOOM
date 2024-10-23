#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kitBoom.h"



//mudar nome da funcao
void validacaoAdjascente(Bomba ***caixa, int linhas, int colunas){
    for(int i=0; i<linhas;i++){
        for(int j=0; j<colunas;j++){
            //if(caixa[i-1][j] != caixa[i][j] && i-1>=0){
            //    if(!strcmp(caixa[i-1][j]->cor,caixa[i][j]->cor)){
            //        printf("Existem bombas adjascentes! (%d,%d) (%d,%d)\n",i-1,j,i,j);
            //    }
            //}
            printf("(%d,%d) (%d,%d)\n",i,j+1,i,j);
            if(caixa[i][j+1] != caixa[i][j]){
                if(!strcmp(caixa[i][j+1]->cor,caixa[i][j]->cor)){
                    printf("(%d,%d) (%d,%d)\n",i,j+1,i,j);
                    return;
                }
            }
            if(caixa[i+1][j] != caixa[i][j]){
                if(!strcmp(caixa[i+1][j]->cor,caixa[i][j]->cor)){
                    printf("Existem bombas adjascentes! (%d,%d) (%d,%d)\n",i-1,j,i,j);
                }
            }
            if(caixa[i][j-1] != caixa[i][j] && j-1>=0){
                if(!strcmp(caixa[i][j-1]->cor,caixa[i][j]->cor)){
                    printf("Existem bombas adjascentes! (%d,%d) (%d,%d)\n",i-1,j,i,j);
                }
            }
        }
    }
    printf("Nenhuma bomba adjacente com cor igual encontrada.\n");
    return;
}