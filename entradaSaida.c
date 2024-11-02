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

int leituraComposicao(char *fileComposicao, Kit *kit){
    FILE *arquivo = fopen(fileComposicao, "r");
    if(!arquivo){
        printf("Erro ao abrir o arquivo de composicao\n");
        return 0;
    }

    int completeza = 0;
    NO *bombaAtual = *kit;

    while(!feof(arquivo) && bombaAtual != NULL){
        int quantidade, comprimento;
        char cor[3];

        fscanf(arquivo, "%d %d%s", &quantidade, &comprimento, cor);
        completeza += (quantidade * comprimento);

        int bombasEncontradas = 0;

        while(bombaAtual != NULL) {
            Bomba b = bombaAtual->bomba;
            if(strcmp(b.cor, cor) == 0 && b.comprimento == comprimento){
                bombasEncontradas++;
            }
            bombaAtual = bombaAtual->prox;
        }

        if(bombasEncontradas > quantidade){
            printf("Existe(m) bomba(s) %d%s a mais em sua configuracao!\n", comprimento, cor);
            fclose(arquivo);
            return 0;
        }else if(bombasEncontradas < quantidade){
            printf("Composicao incompleta: falta(m) bomba(s) %d%s em sua configuracao!\n", comprimento, cor);
            fclose(arquivo);
            return 0;
        }

        bombaAtual = *kit;
    }

    fclose(arquivo);

    if(completeza < 36){
        printf("Composicao incompleta!\n");
        return 0;
    }
    
    return 1;
}

void imprimirCaixa(Par **matriz, int linhas, int colunas) {
    printf("Caixa de Bombas:\n");
    printf("(nome,cor)\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("(%d,%s) ", matriz[i][j].nome, matriz[i][j].cor); 
        }
        printf("\n");
    }
}

void imprimirCabecalho(){
    printf("\n===== EXPLOSIVOS JEPSLON =====\n");
    printf("          Kit BOOM!     \n\n");
    return;
}

void imprimirSaida(int validezComposicao, int validezSobreposicao,int validezCoordenadas,int validezAdjacencia){
    printf("\n===== VALIDEZ DO KIT =====\n");
    if(!validezComposicao){
        printf("A composicao esta invalida!\n");
    } else {
        printf("A composicao esta valida!\n");
    }

    if(!validezSobreposicao){
        printf("Existe sobreposicao!\n");
    } else {
        printf("Nao existe sobreposicao!\n");
    }

    if(!validezCoordenadas){
        printf("Existe bomba que ultrapassa os limites!\n");
    } else {
        printf("As bombas cabem na caixa!\n");
    }

    if(!validezAdjacencia){
        printf("Existe bombas de mesma cor estao adjacentes!\n");
    } else {
        printf("As bombas estao espalhadas corretamente!\n");
    }

}
