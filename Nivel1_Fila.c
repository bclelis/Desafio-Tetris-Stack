/*
 * DESAFIO NÍVEL 1: TETRIS STACK (FILA)
 * LINGUAGEM: C
 *
 * DESCRIÇÃO: Simula a fila de "próximas peças" do Tetris.
 * Foco: Implementação de uma Fila Circular (FIFO) com
 * capacidade fixa.
 *
 * Operações:
 * 1. Jogar (Dequeue)
 * 2. Inserir (Enqueue) - Se houver espaço.
 * 3. Sair
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5 // Capacidade máxima da fila

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
int proximoId = 0; // Contador para IDs únicos

// --- Protótipos das Funções ---
void limparBuffer();
Peca gerarPeca();

// Funções da Fila
int isFilaCheia();
int isFilaVazia();
void enqueue(Peca p);
Peca dequeue();
void exibirFila();

// --- Função Principal ---
int main() {
    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    // Nível 1: Inicializar a fila com 5 peças
    printf("Inicializando a fila de pecas...\n");
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(gerarPeca());
    }

    int opcao = -1;

    do {
        // Nível 1: Exibir estado atual
        printf("\n--- TETRIS STACK (Nivel 1) ---\n");
        exibirFila();

        // Nível 1: Menu de Opções
        printf("\nOpcoes de acao:\n");
        printf("1. Jogar peca (dequeue)\n");
        printf("2. Inserir nova peca (enqueue)\n");
        printf("0. Sair\n");
        printf("Opcao: ");

        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1: // Jogar peça (dequeue)
                if (isFilaVazia()) {
                    printf("FILA VAZIA! Nao ha pecas para jogar.\n");
                } else {
                    Peca p = dequeue();
                    printf("ACAO: Peca [%c %d] foi jogada!\n", p.nome, p.id);
                }
                break;

            case 2: // Inserir nova peça (enqueue)
                if (isFilaCheia()) {
                    printf("FILA CHEIA! Nao e possivel inserir.\n");
                } else {
                    Peca p = gerarPeca();
                    enqueue(p);
                    printf("ACAO: Nova peca [%c %d] inserida no final.\n", p.nome, p.id);
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

// --- Implementação das Funções ---

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * Nível 1: Gera uma nova peça com tipo aleatório e ID único.
 */
Peca gerarPeca() {
    char tipos[] = "IOTLSI"; // Tipos de peça
    Peca p;
    p.nome = tipos[rand() % 6]; // Sorteia um tipo
    p.id = proximoId++;         // Atribui o ID e incrementa
    return p;
}

// Verifica se a fila está cheia
int isFilaCheia() {
    return total_fila == TAM_FILA;
}

// Verifica se a fila está vazia
int isFilaVazia() {
    return total_fila == 0;
}

/**
 * Nível 1: Inserir (enqueue)
 * Adiciona uma peça ao final da fila circular.
 */
void enqueue(Peca p) {
    if (isFilaCheia()) {
        return; // Segurança
    }
    fila[fim_fila] = p;
    fim_fila = (fim_fila + 1) % TAM_FILA; // Lógica circular
    total_fila++;
}

/**
 * Nível 1: Jogar (dequeue)
 * Remove e retorna a peça do início da fila circular.
 */
Peca dequeue() {
    Peca p_vazia = {' ', -1};
    if (isFilaVazia()) {
        return p_vazia; // Segurança
    }
    Peca p = fila[inicio_fila];
    inicio_fila = (inicio_fila + 1) % TAM_FILA; // Lógica circular
    total_fila--;
    return p;
}

/**
 * Nível 1: Exibe o estado atual da fila.
 */
void exibirFila() {
    printf("Fila de pecas: ");
    if (isFilaVazia()) {
        printf("[VAZIA]\n");
        return;
    }

    int i = inicio_fila;
    for (int count = 0; count < total_fila; count++) {
        printf("[%c %d] ", fila[i].nome, fila[i].id);
        i = (i + 1) % TAM_FILA; // Avança na fila circular
    }
    printf("\n");
}
