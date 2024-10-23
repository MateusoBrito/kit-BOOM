#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "kitBoom.h"

int main(int argc, char *argv[]) {
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
        printf("Erro na leitura da composição!\n");
        return 0;
    }

    if(!comparaComposicaoConfiguracao(kit, composicao, numBombas)){
        printf("Composicao inválida!\n");
    }else{
        printf("Composicao valida!\n");
    }

    printf("teste\n");

    free(composicao);

    Bomba ***caixa = montarCaixa2(kit, linhas, colunas);

    printf("Caixa de Bombas:\n");
    imprimirMatriz(caixa, linhas, colunas);

    //validacaoAdjascente(caixa,linhas,colunas);

    //liberarMatriz(caixa, linhas);
    liberaKit(kit);


    return 0;
}