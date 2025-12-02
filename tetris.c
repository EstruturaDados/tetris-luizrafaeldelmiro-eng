#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ============================
//     STRUCT E CONSTANTES
// ============================
typedef struct {
    char tipo;
    int id;
} Peca;

#define TAM_FILA 5
#define TAM_PILHA 3

// ============================
//     VARIÁVEIS GLOBAIS
// ============================
Peca fila[TAM_FILA];
int inicio = 0, fim = 0, quantidade = 0;

Peca pilha[TAM_PILHA];
int topo = -1;

int idGlobal = 1;

// ============================
//     FUNÇÕES DE SUPORTE
// ============================

// Gera uma peça automática com tipo e ID únicos
Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.tipo = tipos[rand() % 4];
    nova.id = idGlobal++;
    return nova;
}

// ============================
//     FILA CIRCULAR
// ============================

void inicializarFila() {
    for (int i = 0; i < TAM_FILA; i++) {
        fila[i] = gerarPeca();
    }
    inicio = 0;
    fim = 0;
    quantidade = TAM_FILA;
}

int filaVazia() {
    return quantidade == 0;
}

int filaCheia() {
    return quantidade == TAM_FILA;
}

void enqueue(Peca p) {
    if (!filaCheia()) {
        fila[fim] = p;
        fim = (fim + 1) % TAM_FILA;
        quantidade++;
    }
}

Peca dequeue() {
    Peca removida = fila[inicio];
    inicio = (inicio + 1) % TAM_FILA;
    quantidade--;
    return removida;
}

void mostrarFila() {
    printf("\n=== Fila de Peças Futuras ===\n");
    if (filaVazia()) {
        printf("Fila vazia!\n");
        return;
    }

    int index = inicio;
    for (int i = 0; i < quantidade; i++) {
        printf("[%c - ID %d] ", fila[index].tipo, fila[index].id);
        index = (index + 1) % TAM_FILA;
    }
    printf("\n");
}

// ============================
//     PILHA DE RESERVA
// ============================

void inicializarPilha() {
    topo = -1;
}

int pilhaVazia() {
    return topo == -1;
}

int pilhaCheia() {
    return topo == TAM_PILHA - 1;
}

void push(Peca p) {
    if (!pilhaCheia()) {
        pilha[++topo] = p;
    }
}

Peca pop() {
    return pilha[topo--];
}

void mostrarPilha() {
    printf("\n=== Pilha de Reserva ===\n");

    if (pilhaVazia()) {
        printf("Pilha vazia!\n");
        return;
    }

    for (int i = topo; i >= 0; i--) {
        printf("[%c - ID %d]\n", pilha[i].tipo, pilha[i].id);
    }
}

// ============================
//     MENU E AÇÕES
// ============================

int main() {
    srand(time(NULL));

    inicializarFila();
    inicializarPilha();

    int opcao;

    do {
        printf("\n===========================\n");
        printf("      TETRIS STACK\n");
        printf("===========================\n");
        mostrarFila();
        mostrarPilha();
        printf("\nMenu:\n");
        printf("1 - Jogar peça\n");
        printf("2 - Reservar peça (enviar da fila para pilha)\n");
        printf("3 - Usar peça reservada (remover da pilha)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {

        case 1: {
            if (!filaVazia()) {
                Peca jogada = dequeue();
                printf("\nVocê jogou a peça [%c - ID %d]\n", jogada.tipo, jogada.id);

                Peca nova = gerarPeca();
                enqueue(nova);
                printf("Nova peça inserida automaticamente: [%c - ID %d]\n",
                       nova.tipo, nova.id);
            }
            break;
        }

        case 2: {
            if (pilhaCheia()) {
                printf("\nA pilha está cheia! Não é possível reservar.\n");
                break;
            }
            if (filaVazia()) {
                printf("\nA fila está vazia! Não há peça para reservar.\n");
                break;
            }

            Peca reservada = dequeue();
            push(reservada);

            printf("\nPeça [%c - ID %d] enviada para a reserva!\n",
                   reservada.tipo, reservada.id);

            // Repor a fila automaticamente
            enqueue(gerarPeca());
            break;
        }

        case 3: {
            if (pilhaVazia()) {
                printf("\nA pilha está vazia! Não há peça para usar.\n");
                break;
            }

            Peca usada = pop();
            printf("\nPeça usada: [%c - ID %d]\n", usada.tipo, usada.id);
            break;
        }

        case 0:
            printf("\nEncerrando...\n");
            break;

        default:
            printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
