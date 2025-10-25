/*
 * DESAFIO NÍVEL 2: TETRIS STACK (FILA + PILHA)
 * LINGUAGEM: C
 *
 * DESCRIÇÃO: Simula a fila de peças e a pilha de reserva.
 * Foco: Interação entre Fila (FIFO) e Pilha (LIFO).
 *
 * Operações:
 * 1. Jogar (Dequeue da fila)
 * 2. Reservar (Dequeue da fila -> Push para pilha)
 * 3. Usar Reservada (Pop da pilha)
 *
 * REGRA: A fila é reabastecida automaticamente após 'Jogar' ou 'Reservar'.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5 // Capacidade da fila
#define TAM_PILHA 3 // Capacidade da pilha

// --- Estrutura da Peça ---
typedef struct {
    char nome; // 'I', 'O', 'T', 'L'
    int id;
} Peca;

// --- Variáveis Globais (Fila Circular) ---
Peca fila[TAM_FILA];
int inicio_fila = 0;
int fim_fila = 0;
int total_fila = 0;

// --- Variáveis Globais (Pilha Linear) ---
Peca pilha[TAM_PILHA];
int topo_pilha = -1; // Pilha vazia

int proximoId = 0; // Contador para IDs únicos

// --- Protótipos das Funções ---
void limparBuffer();
Peca gerarPeca();
void exibirEstado();
void exibirFila();
void exibirPilha();

// Funções da Fila
int isFilaCheia();
int isFilaVazia();
void enqueue(Peca p);
Peca dequeue();

// Funções da Pilha
int isPilhaCheia();
int isPilhaVazia();
void push(Peca p);
Peca pop();

// Nível 2: Função de reabastecimento
void reabastecerFila();

// --- Função Principal ---
int main() {
    srand(time(NULL));

    // Nível 2: Inicializar a fila
    printf("Inicializando a fila de pecas...\n");
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(gerarPeca());
    }
    // A pilha começa vazia

    int opcao = -1;

    do {
        // Nível 2: Exibir estado atual
        printf("\n--- TETRIS STACK (Nivel 2) ---\n");
        exibirEstado();

        // Nível 2: Menu de Opções
        printf("\nOpcoes de Acao:\n");
        printf("1. Jogar peca\n");
        printf("2. Reservar peca\n");
        printf("3. Usar peca reservada\n");
        printf("0. Sair\n");
        printf("Opcao: ");

        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1: // Jogar peça
                if (isFilaVazia()) {
                    printf("FILA VAZIA! Nao ha pecas para jogar.\n");
                } else {
                    Peca p = dequeue();
                    printf("ACAO: Peca [%c %d] foi jogada!\n", p.nome, p.id);
                    reabastecerFila(); // Nível 2: Regra de reabastecimento
                }
                break;

            case 2: // Reservar peça
                if (isPilhaCheia()) {
                    printf("PILHA CHEIA! Nao e possivel reservar.\n");
                } else if (isFilaVazia()) {
                    printf("FILA VAZIA! Nao ha peca para reservar.\n");
                } else {
                    Peca p = dequeue();
                    push(p);
                    printf("ACAO: Peca [%c %d] movida para a reserva.\n", p.nome, p.id);
                    reabastecerFila(); // Nível 2: Regra de reabastecimento
                }
                break;

            case 3: // Usar peça reservada
                if (isPilhaVazia()) {
                    printf("PILHA VAZIA! Nao ha pecas para usar.\n");
                } else {
                    Peca p = pop();
                    printf("ACAO: Peca reservada [%c %d] foi usada!\n", p.nome, p.id);
                }
                break;

            case 0:
                printf("Encerrando o jogo...\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }

    } while (opcao != 0);

    return 0;
}

// --- Implementação das Funções Auxiliares ---

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

Peca gerarPeca() {
    char tipos[] = "IOTLSI";
    Peca p;
    p.nome = tipos[rand() % 6];
    p.id = proximoId++;
    return p;
}

/**
 * Nível 2: Exibe o estado de ambas as estruturas.
 */
void exibirEstado() {
    exibirFila();
    exibirPilha();
}

void exibirFila() {
    printf("Fila de pecas: ");
    if (isFilaVazia()) {
        printf("[VAZIA]\n");
        return;
    }
    int i = inicio_fila;
    for (int count = 0; count < total_fila; count++) {
        printf("[%c %d] ", fila[i].nome, fila[i].id);
        i = (i + 1) % TAM_FILA;
    }
    printf("\n");
}

void exibirPilha() {
    printf("Pilha de reserva (Topo -> Base): ");
    if (isPilhaVazia()) {
        printf("[VAZIA]\n");
        return;
    }
    for (int i = topo_pilha; i >= 0; i--) { // Do topo para a base
        printf("[%c %d] ", pilha[i].nome, pilha[i].id);
    }
    printf("\n");
}

// --- Funções da Fila ---
int isFilaCheia() { return total_fila == TAM_FILA; }
int isFilaVazia() { return total_fila == 0; }

void enqueue(Peca p) {
    if (isFilaCheia()) return;
    fila[fim_fila] = p;
    fim_fila = (fim_fila + 1) % TAM_FILA;
    total_fila++;
}

Peca dequeue() {
    if (isFilaVazia()) return (Peca){' ', -1};
    Peca p = fila[inicio_fila];
    inicio_fila = (inicio_fila + 1) % TAM_FILA;
    total_fila--;
    return p;
}

// --- Funções da Pilha ---
int isPilhaCheia() { return topo_pilha == TAM_PILHA - 1; }
int isPilhaVazia() { return topo_pilha == -1; }

void push(Peca p) {
    if (isPilhaCheia()) return;
    topo_pilha++;
    pilha[topo_pilha] = p;
}

Peca pop() {
    if (isPilhaVazia()) return (Peca){' ', -1};
    Peca p = pilha[topo_pilha];
    topo_pilha--;
    return p;
}

/**
 * Nível 2: Garante que a fila seja preenchida até o
 * máximo após uma peça ser removida.
 */
void reabastecerFila() {
    while (!isFilaCheia()) {
        enqueue(gerarPeca());
    }
}
