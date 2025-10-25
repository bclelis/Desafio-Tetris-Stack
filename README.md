# Tetris Stack - Desafios de Fila e Pilha em C

Este repositório contém a implementação de um sistema de gerenciamento de peças para um jogo fictício, o "Tetris Stack". O projeto foi desenvolvido em C e é dividido em três níveis de complexidade, demonstrando o uso e a interação de estruturas de dados fundamentais: Filas Circulares (FIFO) e Pilhas (LIFO).

## 🚀 Sobre os Desafios

O projeto simula a lógica de um jogador que gerencia as próximas peças (Fila) e uma área de reserva (Pilha). Cada nível adiciona novas mecânicas e complexidade.

### Nível 1: Fila de Peças (Básico)

**Local:** `src/Nivel1_FilaSimples/`

Implementação da fila de "próximas peças" do jogo.

* **Estrutura:** Fila Circular (FIFO) com capacidade fixa de 5 peças.
* **Conceitos:** `struct`, Array, Lógica de Fila Circular (`%`).
* **Operações:**
    * `Jogar Peça`: Remove a peça da frente da fila (Dequeue).
    * `Inserir Peça`: Adiciona uma nova peça ao final da fila (Enqueue), somente se houver espaço.
    * `Exibir`: Mostra o estado atual da fila.

### Nível 2: Fila e Pilha (Aventureiro)

**Local:** `src/Nivel2_FilaPilha/`

Adiciona a mecânica de "reserva", implementada como uma Pilha.

* **Estruturas:** Fila Circular (5) e Pilha (LIFO) com capacidade fixa de 3 peças.
* **Conceitos:** Interação entre Fila e Pilha.
* **Operações Adicionais:**
    * `Reservar Peça`: Move a peça da frente da fila para o topo da pilha (Dequeue da Fila -> Push para Pilha).
    * `Usar Peça Reservada`: Remove a peça do topo da pilha (Pop da Pilha).
* **Nova Regra:** A fila é **automaticamente reabastecida** (Enqueues) até ficar cheia sempre que uma peça é `Jogada` ou `Reservada`.

### Nível 3: Trocas Estratégicas (Mestre)

**Local:** `src/Nivel3_TrocasEstrategicas/`

O desafio final, que implementa todas as mecânicas anteriores e adiciona trocas complexas entre as estruturas.

* **Estruturas:** Fila Circular (5) e Pilha (3).
* **Conceitos:** Acesso direto aos índices de arrays para manipulação de estruturas (swapping).
* **Operações Avançadas:**
    * `Troca Simples`: Troca a peça da frente da fila (`fila[inicio]`) com a peça no topo da pilha (`pilha[topo]`).
    * `Troca Múltipla`: Troca as 3 primeiras peças da fila com as 3 peças da pilha, exigindo que ambas as estruturas tenham pelo menos 3 itens.

## 🧠 Conceitos Praticados
Estruturas de Dados: struct.

Fila Circular: Implementação de lógica FIFO (First-In, First-Out) com reaproveitamento de espaço em um vetor, usando controle de índices (inicio, fim) e o operador módulo (%).

Pilha Linear: Implementação de lógica LIFO (Last-In, First-Out) em um vetor, usando um controle de topo.

Modularização: Separação de responsabilidades em funções (enqueue, dequeue, push, pop, exibir, etc.).

Geração Aleatória: Uso de srand(time(NULL)) e rand() para simular a geração de peças.

Interação de Estruturas: Lógica de transferência de dados entre uma fila e uma pilha.
