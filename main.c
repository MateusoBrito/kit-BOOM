#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "kitBoom.h"

int main(int argc, char *argv[]) {

    printf("\n===== EXPLOSIVOS JEPSLON =====\n");
    printf("          Kit BOOM!     \n\n");

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

    if(composicao == NULL) {
        printf("Erro na leitura da composicao!\n");
        return 0;
    }

    if(!verificarComposicao(kit, composicao, numBombas)){
        return 0;
    }

    free(composicao); 

    Par **caixa = montarCaixa(kit, linhas, colunas);
    imprimirCaixa(caixa,linhas,colunas);

    if(!verificarSobreposicao(kit) || !validarCoordenadas(kit, linhas, colunas) || !validarAdjacencia(caixa,linhas,colunas)){
        saidaInvalido();
        return 0;
    }

    liberaKit(kit);
    liberarCaixa(caixa,linhas);

    exibirTempos();

    return 0;
}