#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
    int xInicial, yInicial, xFinal, yFinal;
    int comprimento;
    char cor[3];
} Bomba;

typedef struct {
    Bomba *bombas;
    int quantidadeBombas;
} Kit;

void imprimirConfiguracao(Kit *kit) {
    printf("Configuração do Kit:\n");
    for (int i = 0; i < kit->quantidadeBombas; i++) {
        Bomba bomba = kit->bombas[i];
        printf("Bomba %d: P1(%d, %d) P2(%d, %d) Comprimento: %d Cor: %s\n", 
               i + 1, bomba.xInicial, bomba.yInicial, bomba.xFinal, bomba.yFinal, bomba.comprimento, bomba.cor);
    }
}


Kit* leituraConfiguracao(char* fileConfiguracao){
    FILE *arquivo = fopen(fileConfiguracao, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de configuração");
        return NULL;
    }

    Kit *kit = malloc(sizeof(Kit));
    kit->bombas = malloc(sizeof(Bomba) * 36);  // assumimos no máximo 18 barras para simplificar
    kit->quantidadeBombas = 0;

    while (!feof(arquivo)) {
        Bomba bomba;
        fscanf(arquivo, "%d %d %d %d %d%s", &bomba.xInicial, &bomba.yInicial,
               &bomba.xFinal, &bomba.yFinal,&bomba.comprimento,bomba.cor);
        kit->bombas[kit->quantidadeBombas++] = bomba;
    }

    imprimirConfiguracao(kit);

}

int main(int argc, char *argv[]) {
    int opt;
    char *fileComposicao;
    char *fileConfiguracao;

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


    leituraConfiguracao(fileConfiguracao);


    return 0;
}