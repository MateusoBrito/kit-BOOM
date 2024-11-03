#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
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

    struct timeval start, end;
    gettimeofday(&start, NULL);

    struct timeval entrada_start, entrada_end;
    gettimeofday(&entrada_start, NULL);

    Kit *kit = leituraConfiguracao(fileConfiguracao);
    int validezComposicao = leituraComposicao(fileComposicao, kit);

    gettimeofday(&entrada_end, NULL);
    double entrada_time = (entrada_end.tv_sec - entrada_start.tv_sec) + (entrada_end.tv_usec - entrada_start.tv_usec) / 1000000.0;

    Par **caixa = montarCaixa(kit, linhas, colunas); 

    int validezSobreposicao = validarSobreposicao(kit);
    int validezCoordenadas = validarCoordenadas(kit, linhas, colunas);
    int validezAdjacencia = validarAdjacencia(caixa,linhas,colunas);

    struct timeval saida_start, saida_end;
    gettimeofday(&saida_start, NULL);

    imprimirSaida(validezComposicao, validezSobreposicao, validezCoordenadas, validezAdjacencia);
    imprimirCaixa(caixa,linhas,colunas);

    gettimeofday(&saida_end, NULL);
    double saida_time = (saida_end.tv_sec - saida_start.tv_sec) + (saida_end.tv_usec - saida_start.tv_usec) / 1000000.0;

    liberarKit(kit);
    liberarCaixa(caixa,linhas);

    gettimeofday(&end, NULL);

    double elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;


    printf("\nTempo de Entrada e Saida: %.6f segundos\n", entrada_time+saida_time);
    printf("Tempo total (real): %.6f segundos\n", elapsed_time);

    return 0;
}