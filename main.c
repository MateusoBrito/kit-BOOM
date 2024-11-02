#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "kitBoom.h"

int main(int argc, char *argv[]) {
    imprimirCabecalho();

    int opt;
    char *fileComposicao = NULL;
    char *fileConfiguracao = NULL;
    int linhas = 6, colunas = 6;

    while ((opt = getopt(argc, argv, "k:c:")) != -1) {
        switch (opt) {
            case 'k':
                fileComposicao = optarg;
                break;
            case 'c':
                fileConfiguracao = optarg;
                break;
            default:
                //VER ISSO DEPOIS
                fprintf(stderr, "Uso: %s -k <arquivo composição> -c <arquivo configuração>\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if(fileConfiguracao == NULL){
        printf("O arquivo de configuração não foi especificado.\n");
        return 0;
    }

    if(fileComposicao == NULL){
        printf("O arquivo de composição não foi especificado.\n");
        return 0;
    }


    Kit *kit = leituraConfiguracao(fileConfiguracao);

    int numBombas;
    Composicao *composicao = leituraComposicao(fileComposicao, &numBombas);
    Par **caixa = montarCaixa(kit, linhas, colunas);

    int validezComposicao = validarComposicao(kit, composicao, numBombas);
    free(composicao); 

    imprimirCaixa(caixa,linhas,colunas);

    int validezSobreposicao = validarSobreposicao(kit);
    int validezCoordenadas = validarCoordenadas(kit, linhas, colunas);
    int validezAdjacencia = validarAdjacencia(caixa,linhas,colunas);

    imprimirSaida(validezComposicao, validezSobreposicao, validezCoordenadas, validezAdjacencia);

    liberarKit(kit);
    liberarCaixa(caixa,linhas);

    return 0;
}