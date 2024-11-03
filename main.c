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

    struct timeval io_start, io_end;
    gettimeofday(&io_start, NULL);

    Kit *kit = leituraConfiguracao(fileConfiguracao);
    Par **caixa = montarCaixa(kit, linhas, colunas); 

    gettimeofday(&io_end, NULL);
    double io_time = (io_end.tv_sec - io_start.tv_sec) + (io_end.tv_usec - io_start.tv_usec) / 1000000.0;


    int validezComposicao = leituraComposicao(fileComposicao, kit);
    int validezSobreposicao = validarSobreposicao(kit);
    int validezCoordenadas = validarCoordenadas(kit, linhas, colunas);
    int validezAdjacencia = validarAdjacencia(caixa,linhas,colunas);

    imprimirSaida(validezComposicao, validezSobreposicao, validezCoordenadas, validezAdjacencia);
    imprimirCaixa(caixa,linhas,colunas);

    liberarKit(kit);
    liberarCaixa(caixa,linhas);

    gettimeofday(&end, NULL);

    double elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;


    printf("\nTempo de E/S: %.6f segundos\n", io_time);
    printf("Tempo total (real): %.6f segundos\n", elapsed_time);

    return 0;
}