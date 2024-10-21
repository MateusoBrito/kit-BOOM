#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "kitBoom.h"

Kit *criarKit(){
    Kit *k;
    k = (Kit*) malloc (sizeof(Kit));
    if(k != NULL){
        *k = NULL;
    }
    return k;
}

int kitVazio (Kit *k){
    if(k == NULL ) 
        return -1;
    if (*k == NULL )
        return 1;
    return 0; 
}

NO* alocarNO () {
return (NO *) malloc ( sizeof (NO));
}

void liberarNO (NO* q){
free (q);
}

int insereBomba(Kit *k, Bomba bomba){
    if(k==NULL) return 0;
    NO* novo = alocarNO();
    if(novo = NULL) return 0;
    novo->bomba = bomba;
    novo->prox = *k;
    *k = novo;
    return 1;
}

void liberaKit(Kit *k){
    if(k != NULL){
        NO *aux;
        while((*k)!=NULL){
            aux = *k;
            *k = (*k)->prox;
            liberarNO(aux);
        }
        free(k);
    }
}

Kit* leituraConfiguracao(char* fileConfiguracao){
    FILE *arquivo = fopen(fileConfiguracao, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de configuração");
        return NULL;
    }

    Kit *kit = criarKit();

    while (!feof(arquivo)) {
        Bomba bomba;
        fscanf(arquivo, "%d %d %d %d %d%s", &bomba.xInicial, &bomba.yInicial,
               &bomba.xFinal, &bomba.yFinal,&bomba.comprimento,bomba.cor);
        insereBomba(kit, bomba);
    }

    fclose(arquivo);
    return kit;
}

int **alocarMatriz(int linhas, int colunas) {
    int **matriz = (int **)malloc(linhas * sizeof(int *));
    
    if (matriz == NULL) {
        return 0;
    }
    for (int i = 0; i < linhas; i++) {
        matriz[i] = (int *)malloc(colunas * sizeof(int));
        if (matriz[i] == NULL) {
            return 0;
        }
    }

    return matriz;
}

void liberarMatriz(int **matriz, int linhas) {
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

void montarCaixa(Kit *kit,int linhas, int colunas) {
    int **caixa = alocarMatriz(linhas, colunas);
    
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            caixa[i][j] = 0;
        }
    }

    NO *bombaAtual = *kit;
    while(bombaAtual != NULL){
        Bomba b = bombaAtual->bomba;

        for(int i=b.xInicial-1; i<b.xFinal;i++){
            for(int j=b.yInicial-1; j<b.yFinal;j++){
                
            }
        }
    }

    liberarNO(bombaAtual);
    
}

void imprimirMatriz(int **matriz, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int linhas = 6;
    int colunas = 6;

    // Alocar matriz
    int **matriz = alocarMatriz(linhas, colunas);

    // Preencher e imprimir a matriz
    preencherMatriz(matriz, linhas, colunas);
    imprimirMatriz(matriz, linhas, colunas);

    // Liberar memória alocada
    liberarMatriz(matriz, linhas);

    return 0;
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