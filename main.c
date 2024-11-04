#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/time.h>
#include <sys/resource.h>
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

    struct timeval inicio, fim;
    gettimeofday(&inicio, NULL);

    struct rusage usage_start, usage_end;
    getrusage(RUSAGE_SELF, &usage_start); 

    struct timeval inicioEntrada, fimEntrada;
    gettimeofday(&inicioEntrada, NULL);

    Kit *kit = leituraConfiguracao(fileConfiguracao);
    int validezComposicao = leituraComposicao(fileComposicao, kit);

    gettimeofday(&fimEntrada, NULL);
    double tempoEntrada  = (fimEntrada.tv_sec - inicioEntrada.tv_sec) + (fimEntrada.tv_usec - inicioEntrada.tv_usec) / 1000000.0;

    Par **caixa = montarCaixa(kit, linhas, colunas); 

    int validezSobreposicao = validarSobreposicao(kit);
    int validezCoordenadas = validarCoordenadas(kit, linhas, colunas);
    int validezAdjacencia = validarAdjacencia(caixa,linhas,colunas);

    struct timeval inicioSaida, fimSaida;
    gettimeofday(&inicioSaida, NULL);

    imprimirSaida(validezComposicao, validezSobreposicao, validezCoordenadas, validezAdjacencia);
    imprimirCaixa(caixa,linhas,colunas);

    gettimeofday(&fimSaida, NULL);
    double tempoSaida = (fimSaida.tv_sec - inicioSaida.tv_sec) + (fimSaida.tv_usec - inicioSaida.tv_usec) / 1000000.0;

    liberarKit(kit);
    liberarCaixa(caixa,linhas);

    gettimeofday(&fim, NULL);
    getrusage(RUSAGE_SELF, &usage_end);

    double tempoTotal = (fim.tv_sec - inicio.tv_sec) + (fim.tv_usec - inicio.tv_usec) / 1000000.0;

    double tempoUsuario = (usage_end.ru_utime.tv_sec - usage_start.ru_utime.tv_sec) + (usage_end.ru_utime.tv_usec - usage_start.ru_utime.tv_usec) / 1000000.0;

    double tempoSistema = (usage_end.ru_stime.tv_sec - usage_start.ru_stime.tv_sec) + (usage_end.ru_stime.tv_usec - usage_start.ru_stime.tv_usec) / 1000000.0;
    
    printf("\nTempo de Entrada e Saida: %.6f segundos\n", tempoEntrada + tempoSaida);
    printf("Tempo total (real): %.6f segundos\n", tempoTotal);
    printf("Tempo de CPU (user): %.6f segundos\n", tempoUsuario);
    printf("Tempo de CPU (system): %.6f segundos\n", tempoSistema);

    return 0;
}