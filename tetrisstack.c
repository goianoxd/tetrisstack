#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILA 5   // Tamanho fixo da fila

/*
    Struct Peca:
    Representa uma peça futura do Tetris Stack.
    - nome: tipo da peça (I, O, T, L)
    - id: identificador único da peça
*/
typedef struct {
    char nome;
    int id;
} Peca;

// Vetor que representa a fila de peças futuras
Peca fila[MAX_FILA];

// Controle da fila circular
int inicio = 0;  
int fim = 0;    
int quantidade = 0;

// Contador global para gerar IDs únicos
int proximoID = 0;


/*
    Função: gerarPeca()
    - Gera automaticamente uma peça com tipo aleatório
      e id único incremental.
*/
Peca gerarPeca() {
    char tipos[4] = {'I', 'O', 'T', 'L'};
    Peca nova;

    nova.nome = tipos[rand() % 4];  // Tipo aleatório
    nova.id = proximoID++;          // ID único

    return nova;
}


/*
    Função: enqueue()
    - Insere nova peça ao final da fila circular,
      se houver espaço.
*/
void enqueue() {
    if (quantidade == MAX_FILA) {
        printf("\nFila cheia! Não é possível inserir nova peça.\n");
        return;
    }

    fila[fim] = gerarPeca();
    fim = (fim + 1) % MAX_FILA;
    quantidade++;

    printf("\nPeça adicionada com sucesso!\n");
}


/*
    Função: dequeue()
    - Remove a peça da frente da fila, se não estiver vazia.
*/
void dequeue() {
    if (quantidade == 0) {
        printf("\nFila vazia! Nenhuma peça para jogar.\n");
        return;
    }

    Peca removida = fila[inicio];
    inicio = (inicio + 1) % MAX_FILA;
    quantidade--;

    printf("\nPeça jogada: [%c %d]\n", removida.nome, removida.id);
}


/*
    Função: exibirFila()
    - Mostra o estado atual da fila na tela.
*/
void exibirFila() {
    printf("\n=== Fila de Peças Futuras ===\n");

    if (quantidade == 0) {
        printf("[Fila vazia]\n");
        return;
    }

    int i = inicio;
    for (int cont = 0; cont < quantidade; cont++) {
        printf("[%c %d] ", fila[i].nome, fila[i].id);
        i = (i + 1) % MAX_FILA;
    }
    printf("\n");
}


/*
    Função principal:
    - Inicializa a fila com 5 peças
    - Exibe menu de operações
    - Controla entrada do jogador
*/
int main() {
    srand(time(NULL));  // Para gerar peças aleatórias

    // Inicializando fila com 5 peças
    for (int i = 0; i < MAX_FILA; i++) {
        enqueue();
    }

    int opcao;

    do {
        exibirFila();

        printf("\n=== Menu ===\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dequeue();
                break;

            case 2:
                enqueue();
                break;

            case 0:
                printf("\nEncerrando o sistema...\n");
                break;

            default:
                printf("\nOpcao inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
