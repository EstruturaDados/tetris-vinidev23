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

void exibirFila() {
    printf("\n--- Fila de Pecas ---\n");
    if (countFila == 0) {
        printf("[Fila vazia]\n");
        return;
    }
    printf("Frente: ");
    for (int i = 0; i < countFila; i++) {
        int index = (frente + i) % FILA_CAPACIDADE;
        printf("[%s-%d]", fila[index].nome, fila[index].id);
        if (i < countFila - 1) {
            printf(" -> ");
        }
    }
    printf(" :Tras\n");
}

void exibirPilha() {
    printf("\n--- Pilha de Reserva ---\n");
    if (topoPilha == -1) {
        printf("[Pilha vazia]\n");
        return;
    }
    printf("Topo: ");
    for (int i = topoPilha; i >= 0; i--) {
        printf("[%s-%d]", pilha[i].nome, pilha[i].id);
        if (i > 0) {
            printf(" -> ");
        }
    }
    printf(" :Base\n");
}

void jogarPeca() {
    if (countFila > 0) {
        ultimaPecaJogada = fila[frente];
        ultimaJogadaValida = 1;
        printf("\nVoce jogou a peca: [%s-%d]\n", ultimaPecaJogada.nome, ultimaPecaJogada.id);

        frente = (frente + 1) % FILA_CAPACIDADE;
        
        Peca novaPeca = gerarPeca();
        tras = (tras + 1) % FILA_CAPACIDADE;
        fila[tras] = novaPeca;
        printf("Nova peca [%s-%d] inserida na fila.\n", novaPeca.nome, novaPeca.id);
    } else {
        printf("\nNao ha pecas para jogar na fila!\n");
    }
}

void reservarPeca() {
    if (topoPilha >= PILHA_CAPACIDADE - 1) {
        printf("\nA pilha de reserva esta cheia! Nao e possivel reservar mais pecas.\n");
        return;
    }
    if (countFila > 0) {
        Peca pecaParaReservar = fila[frente];
        topoPilha++;
        pilha[topoPilha] = pecaParaReservar;
        
        printf("\nPeca [%s-%d] movida da fila para a pilha de reserva.\n", pecaParaReservar.nome, pecaParaReservar.id);
        
        frente = (frente + 1) % FILA_CAPACIDADE;
        
        Peca novaPeca = gerarPeca();
        tras = (tras + 1) % FILA_CAPACIDADE;
        fila[tras] = novaPeca;
        printf("Nova peca [%s-%d] inserida na fila.\n", novaPeca.nome, novaPeca.id);
    } else {
        printf("\nA fila esta vazia! Nao ha pecas para reservar.\n");
    }
    ultimaJogadaValida = 0;
}

void usarPecaReservada() {
    if (topoPilha == -1) {
        printf("\nA pilha de reserva esta vazia! Nao ha pecas para usar.\n");
        return;
    }

    Peca pecaParaUsar = pilha[topoPilha];
    
    frente = (frente - 1 + FILA_CAPACIDADE) % FILA_CAPACIDADE;
    fila[frente] = pecaParaUsar;
    
    topoPilha--;
    printf("\nPeca [%s-%d] movida da pilha para a frente da fila.\n", pecaParaUsar.nome, pecaParaUsar.id);
    ultimaJogadaValida = 0;
}

void trocarPeca() {
    if (topoPilha == -1) {
        printf("\nA pilha esta vazia. Nao e possivel realizar a troca.\n");
        return;
    }
    if (countFila == 0) {
        printf("\nA fila esta vazia. Nao e possivel realizar a troca.\n");
        return;
    }

    Peca temp = fila[frente];
    fila[frente] = pilha[topoPilha];
    pilha[topoPilha] = temp;

    printf("\nTroca realizada com sucesso!\n");
    printf("Peca [%s-%d] foi para a fila e [%s-%d] para a pilha.\n", fila[frente].nome, fila[frente].id, pilha[topoPilha].nome, pilha[topoPilha].id);
    ultimaJogadaValida = 0;
}

void desfazerJogada() {
    if (ultimaJogadaValida) {
        tras = (tras - 1 + FILA_CAPACIDADE) % FILA_CAPACIDADE;
        fila[tras] = fila[(tras - 1 + FILA_CAPACIDADE) % FILA_CAPACIDADE];
        fila[frente] = ultimaPecaJogada;
        
        printf("\nUltima jogada desfeita. Peca [%s-%d] retornou para a frente da fila.\n", ultimaPecaJogada.nome, ultimaPecaJogada.id);
        
        Peca pecaRemovida = fila[tras];
        tras = (tras - 1 + FILA_CAPACIDADE) % FILA_CAPACIDADE;

        strcpy(pecaRemovida.nome, "");
        pecaRemovida.id = 0;

        ultimaJogadaValida = 0;
    } else {
        printf("\nNao ha jogada valida para ser desfeita.\n");
    }
}

void inverterEstruturas() {
    if (countFila != FILA_CAPACIDADE || topoPilha == -1) {
        printf("\nPara inverter, a fila deve estar cheia e a pilha nao vazia.\n");
        return;
    }
    
    Peca tempFila[FILA_CAPACIDADE];
    int j = 0;
    for (int i = topoPilha; i >= 0; i--) {
        tempFila[j++] = pilha[i];
    }

    Peca tempPilha[FILHA_CAPACIDADE];
    int k = 0;
    for (int i = (frente + countFila -1) % FILA_CAPACIDADE; i >= frente; i = (i - 1 + FILA_CAPACIDADE) % FILA_CAPACIDADE) {
        tempPilha[k++] = fila[i];
    }
    
    frente = 0;
    tras = -1;
    for(int i = 0; i < k; i++) {
        tras = (tras + 1) % FILA_CAPACIDADE;
        fila[tras] = tempPilha[i];
    }
    
    topoPilha = -1;
    for (int i = 0; i < j; i++) {
        topoPilha++;
        pilha[topoPilha] = tempFila[i];
    }
    
    printf("\nFila e Pilha invertidas com sucesso!\n");
    ultimaJogadaValida = 0;
}

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void pause() {
    printf("\nPressione ENTER para continuar...\n");
    limparBufferEntrada();
}