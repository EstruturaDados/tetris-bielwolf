#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5

typedef struct Peca {
    char nome;
    int id;
} P;

typedef struct Fila {
    P itens[MAX];
    int inicio;
    int fim;
    int total;
} F;

void inicializarFila(F *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

int filaCheia(F *f) {
    return f->total == MAX;
}

int filaVazia(F *f) {
    return f->total == 0;
}

void inserir(F *f, P p) {
    if (filaCheia(f)) {
        printf("Fila cheia. Não é possível inserir.\n");
        return;
    }
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;
    f->total++;
}

void remover(F *f, P *p) {
    if (filaVazia(f)) {
        printf("Fila vazia. Não é possível remover.\n");
        return;
    }
    *p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
}

void mostrarFila(F *f) {
    printf("Fila: ");
    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX) {
        printf("[%c, %d] ", f->itens[idx].nome, f->itens[idx].id);
    }
    printf("\n");
}

P gerarPeca() {
    P peca;
    static int contador = 0;
    char tipos[] = {'I', 'O', 'T', 'L'};
    peca.nome = tipos[rand() % 4];
    peca.id = contador++;
    return peca;
}

int main() {
    F f;
    int opcao;
    P p;

    srand(time(NULL));
    inicializarFila(&f);

    // Inicializa fila com MAX peças
    for (int i = 0; i < MAX; i++) {
        inserir(&f, gerarPeca());
    }

    while (1) {
        printf("\n--------- MENU ---------\n");
        mostrarFila(&f);
        printf("\nOpções de ação:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                remover(&f, &p);
                if (f.total >= 0)
                    printf("Peça removida: [%c %d]\n", p.nome, p.id);
                break;

            case 2:
                inserir(&f, gerarPeca());
                break;

            case 0:
                printf("Saindo...\n");
                return 0;

            default:
                printf("Opção inválida!\n");
        }
    }

    return 0;
}

