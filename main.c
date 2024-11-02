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
                printf("\nUse: ./<arquivoexecutavel> -k <arquivo composicao> -c <arquivo configuracao>\n\n");
                return 0;
        }
    }

    if(fileConfiguracao == NULL){
        printf("O arquivo de configuracao nao foi especificado.\n");
        return 0;
    }

    if(fileComposicao == NULL){
        printf("O arquivo de composicao nao foi especificado.\n");
        return 0;
    }

    Kit *kit = leituraConfiguracao(fileConfiguracao);
    Par **caixa = montarCaixa(kit, linhas, colunas); 

    int validezComposicao = leituraComposicao(fileComposicao, kit);
    int validezSobreposicao = validarSobreposicao(kit);
    int validezCoordenadas = validarCoordenadas(kit, linhas, colunas);
    int validezAdjacencia = validarAdjacencia(caixa,linhas,colunas);

    imprimirSaida(validezComposicao, validezSobreposicao, validezCoordenadas, validezAdjacencia);
    imprimirCaixa(caixa,linhas,colunas);

    liberarKit(kit);
    liberarCaixa(caixa,linhas);

    return 0;
}