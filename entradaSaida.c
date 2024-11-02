#include <stdio.h>
#include <stdlib.h>
#include "kitBoom.h"
#include <string.h>

Kit* leituraConfiguracao(char* fileConfiguracao){
    FILE *arquivo = fopen(fileConfiguracao, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de configuracao\n");
        return NULL;
    }

    Kit *kit = criarKit();
    Bomba bomba;

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

int leituraComposicao(char *fileComposicao, Kit *kit){
    FILE *arquivo = fopen(fileComposicao, "r");
    if(!arquivo){
        printf("Erro ao abrir o arquivo de composicao\n");
        return 0;
    }

    int completeza = 0;
    while(!feof(arquivo)){
        int quantidade, comprimento;
        char cor[3];

        fscanf(arquivo, "%d %d%s", &quantidade, &comprimento, cor);
        completeza += (quantidade * comprimento);

        int validezComposicao = validarComposicao(kit, quantidade,comprimento,cor);

        if(!validezComposicao){
            fclose(arquivo);
            return 0;
        }
    }

    fclose(arquivo);

    if(completeza < 36){
        printf("Composicao incompleta!\n");
        return 0;
    }
    
    return 1;
}

void imprimirCaixa(Par **matriz, int linhas, int colunas) {
    printf("\n=============== CAIXA DE BOMBAS ===============\n");
    printf("|                (Numero,Cor)                  |\n");
    for (int i = 0; i < linhas; i++) {
        printf("| ");
        for(int j = 0; j < colunas; j++) {
            printf("(%d,%s) ", matriz[i][j].nome, matriz[i][j].cor); 
        }
        printf("|\n");
    }
    printf("================================================\n");
}

void imprimirCabecalho(){
    printf("\n============= EXPLOSIVOS JEPSLON =============\n");
    printf("                   Kit BOOM!     \n\n");
    return;
}

void imprimirSaida(int validezComposicao, int validezSobreposicao,int validezCoordenadas,int validezAdjacencia){
    printf("\n=============== VALIDEZ DO KIT ===============\n\n");
    int kitValido = 1;
    if(!validezComposicao){
        printf("COMPOSICAO: invalida\n");
        kitValido = 0;
    } else {
        printf("COMPOSICAO: valida\n");
    }

    if(!validezSobreposicao){
        printf("SOBREPOSICAO: existe\n");
        kitValido = 0;
    } else {
        printf("SOBREPOSICAO: nao existe\n");
    }

    if(!validezCoordenadas){
        printf("COORDENADAS: incorretas\n");
        kitValido = 0;
    } else {
        printf("COORDENADAS: corretas\n");
    }

    if(!validezAdjacencia){
        printf("BOMBAS ADJACENTES: sim\n");
        kitValido = 0;
    } else {
        printf("BOMBAS ADJACENTES: nao\n");
    }

    if(kitValido){
        printf("\nRESULTADO: KIT VALIDO!\n");
    }else{
        printf("\nRESULTADO: KIT INVALIDO!\n");
    }

}
