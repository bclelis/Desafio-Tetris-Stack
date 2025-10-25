/*
 * DESAFIO NÍVEL 3: TETRIS STACK (TROCAS ESTRATÉGICAS)
 * LINGUAGEM: C
 *
 * DESCRIÇÃO: Sistema completo com Fila, Pilha e trocas
 * estratégicas entre as duas estruturas.
 *
 * Operações:
 * 1. Jogar (Dequeue fila)
 * 2. Reservar (Dequeue fila -> Push pilha)
 * 3. Usar Reservada (Pop pilha)
 * 4. Troca Simples (Fila[inicio] <-> Pilha[topo])
 * 5. Troca Múltipla (3 da fila <-> 3 da pilha)
 *
 * REGRA: Fila reabastece após 'Jogar' ou 'Reservar'.
 * Trocas NÃO reabastecem, pois são... trocas.
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

// Funções de Jogo
void reabastecerFila();
void trocarPecaAtual(); // Nível 3
void trocarMultiplo();  // Nível 3

// --- Função Principal ---
int main() {
    srand(time(NULL));

    // Nível 3: Inicializar a fila
    printf("Inicializando a fila de pecas...\n");
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(gerarPeca());
    }

    int opcao = -1;

    do {
        // Nível 3: Exibir estado atual
        printf("\n--- TETRIS STACK (Nivel Mestre) ---\n");
        exibirEstado();

        // Nível 3: Menu de Opções
        printf("\nOpcoes disponiveis:\n");
        printf("1. Jogar peca da frente da fila\n");
        printf("2. Enviar peca da fila para a pilha de reserva\n");
        printf("3. Usar peca da pilha de reserva\n");
        printf("4. Trocar peca da frente da fila com o topo da pilha\n");
        printf("5. Trocar os 3 primeiros da fila com as 3 pecas da pilha\n");
        printf("0. Sair\n");
        printf("Opcao escolhida: ");

        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1: // Jogar peça
                if (isFilaVazia()) {
                    printf("FILA VAZIA! Nao ha pecas para jogar.\n");
                } else {
                    Peca p = dequeue();
                    printf("ACAO: Peca [%c %d] foi jogada!\n", p.nome, p.id);
                    reabastecerFila();
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
                    reabastecerFila();
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

            case 4: // Nível 3: Troca Simples
                trocarPecaAtual();
                break;

            case 5: // Nível 3: Troca Múltipla
                trocarMultiplo();
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

// --- Funções de Jogo (Nível 2 e 3) ---

void reabastecerFila() {
    while (!isFilaCheia()) {
        enqueue(gerarPeca());
    }
}

/**
 * Nível 3: Troca a peça da frente da fila com o topo da pilha.
 * Acesso direto aos arrays, sem enqueue/dequeue.
 */
void trocarPecaAtual() {
    printf("ACAO: Trocando peca da frente da fila com topo da pilha...\n");
    if (isFilaVazia() || isPilhaVazia()) {
        printf("ERRO: Fila e Pilha devem conter pelo menos 1 peca para trocar.\n");
        return;
    }

    // Acessa os elementos diretamente
    Peca temp = fila[inicio_fila];       // Guarda a peça da frente da fila
    fila[inicio_fila] = pilha[topo_pilha]; // Topo da pilha vai para a frente da fila
    pilha[topo_pilha] = temp;              // Peça da fila vai para o topo da pilha

    printf("Troca simples realizada com sucesso!\n");
}

/**
 * Nível 3: Troca as 3 primeiras peças da fila com as 3 da pilha.
 * Requer que AMBAS tenham 3 peças.
 */
void trocarMultiplo() {
    printf("ACAO: Trocando as 3 primeiras pecas da fila com as 3 da pilha...\n");

    // Validação: total_fila >= 3 e (topo_pilha + 1) >= 3
    if (total_fila < 3 || topo_pilha < 2) {
        printf("ERRO: Fila e Pilha devem conter pelo menos 3 pecas para a troca multipla.\n");
        return;
    }

    int idx_fila = inicio_fila;
    int idx_pilha = topo_pilha; // Topo (2)

    // Troca 3 peças
    for (int i = 0; i < 3; i++) {
        // Troca
        Peca temp = fila[idx_fila];
        fila[idx_fila] = pilha[idx_pilha];
        pilha[idx_pilha] = temp;

        // Avança os ponteiros
        idx_fila = (idx_fila + 1) % TAM_FILA; // Avança na fila circular
        idx_pilha--;                          // Recua na pilha
    }

    printf("Troca multipla realizada com sucesso!\n");
}
