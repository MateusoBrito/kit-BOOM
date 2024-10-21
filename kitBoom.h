#ifndef KIT_H
#define KIT_H

typedef struct {
    int xInicial, yInicial, xFinal, yFinal;
    int comprimento;
    char cor[3];
} Bomba;

typedef struct NO{
    Bomba bomba;
    struct NO *prox;
} NO;

typedef struct NO* Kit;




#endif