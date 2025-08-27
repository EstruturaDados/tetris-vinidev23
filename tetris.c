#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define FILA_CAPACIDADE 5
#define PILHA_CAPACIDADE 3

typedef struct {
    char nome[5];
    int id;
} Peca;

Peca fila[FILA_CAPACIDADE];
int frente = 0;
int tras = -1;
int countFila = 0;

Peca pilha[PILHA_CAPACIDADE];
int topoPilha = -1;

Peca ultimaPecaJogada;
int ultimaJogadaValida = 0;
