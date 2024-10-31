#include <stdio.h>
#include <stdlib.h>
#include "kitBoom.h"
#include <string.h>
#include <sys/resource.h>

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
        printf("Composicao incompleta!\n");
        return NULL;
    }else{
        return composicao;
    }

    /*
    printf("Composicao lida:\n");
    for (int i = 0; i < *numBombas; i++) {
        printf("Bomba %d: Comprimento = %d, Quantidade = %d, Cor = %s\n",
               i + 1, composicao[i].comprimento, 
               composicao[i].quantidade, composicao[i].cor);
    }
    */
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

void saidaInvalido(){
    printf("A configuracao esta invalida!\n");
}

void exibirTempos() {
    struct rusage uso;

    getrusage(RUSAGE_SELF, &uso);

    // Tempo de usuário em segundos e microssegundos
    printf("Tempo de Usuário: %ld.%06ld segundos\n", 
           uso.ru_utime.tv_sec, uso.ru_utime.tv_usec);

    // Tempo de sistema em segundos e microssegundos
    printf("Tempo de Sistema: %ld.%06ld segundos\n", 
           uso.ru_stime.tv_sec, uso.ru_stime.tv_usec);
}