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

void inicializarFila();
Peca gerarPeca();
void exibirFila();
void exibirPilha();
void jogarPeca();
void reservarPeca();
void usarPecaReservada();
void trocarPeca();
void desfazerJogada();
void inverterEstruturas();
void limparBufferEntrada();
void pause();

int main() {
    srand(time(NULL));
    inicializarFila();

    int opcao;
    do {
        exibirFila();
        exibirPilha();
        printf("\n--- MENU - TETRIS STACK ---\n");
        printf("1 - Jogar peca\n");
        printf("2 - Reservar peca\n");
        printf("3 - Usar peca reservada\n");
        printf("4 - Trocar peca do topo da pilha com a da frente da fila\n");
        printf("5 - Desfazer ultima jogada\n");
        printf("6 - Inverter fila com pilha\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                jogarPeca();
                break;
            case 2:
                reservarPeca();
                break;
            case 3:
                usarPecaReservada();
                break;
            case 4:
                trocarPeca();
                break;
            case 5:
                desfazerJogada();
                break;
            case 6:
                inverterEstruturas();
                break;
            case 0:
                printf("Encerrando o jogo. Ate mais!\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
        pause();
    } while (opcao != 0);

    return 0;
}

void inicializarFila() {
    for (int i = 0; i < FILA_CAPACIDADE; i++) {
        Peca novaPeca = gerarPeca();
        if (countFila < FILA_CAPACIDADE) {
            tras = (tras + 1) % FILA_CAPACIDADE;
            fila[tras] = novaPeca;
            countFila++;
        }
    }
}

Peca gerarPeca() {
    Peca novaPeca;
    char tipos[7][5] = {"I", "O", "T", "L", "J", "S", "Z"};
    strcpy(novaPeca.nome, tipos[rand() % 7]);
    novaPeca.id = rand() % 1000 + 1;
    return novaPeca;
}


