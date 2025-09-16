#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5
#define MAX_PILHA 3

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

typedef struct Pilha
{
    P itens [MAX_PILHA];
    int topo;
} Pi;

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

void inserir(F *f, P peca) {
    if (filaCheia(f)) {
        printf("Fila cheia. Não é possível inserir.\n");
        return;
    }
    f->itens[f->fim] = peca;
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

void inicializarPilha(Pi *p) {
    p->topo = -1;
}

int pilhaVazia(Pi *p) {
    return p->topo == -1;
}

int pilhaCheia(Pi *p) {
    return p->topo == MAX_PILHA - 1;
}


void mostrarPilha(Pi *p) {
    printf("Pilha (topo -> base):\n");
    for (int i = p->topo; i >= 0; i--) {
        printf("[%c, %d]\n", p->itens[i].nome, p->itens[i].id);
    }
    printf("\n");
}

void movepeca(F *f, Pi *p) {
    if(pilhaCheia(p)) {
        printf("Não possível mover a peça. Pilha esta cheia.");
        return;
    }

    if (filaVazia(f)) {
        printf("Não é possível mover a peça. Fila está vazia.\n");
        return;
    }

    P peca = f->itens[f->inicio];

    p->topo++;
    p->itens[p->topo] = peca;

    f->inicio = (f->inicio + 1) % MAX;
    f->total--;

}

void trocaPecas(Pi *p, F *f) {
    if (f->inicio < f->fim && p->topo >= 0) {
        P aux = f->itens[f->inicio];
        f->itens[f->inicio] = p->itens[p->topo];
        p->itens[p->topo] = aux;
    } else {
        printf("Não é possível trocar: fila ou pilha vazia.\n");
    }
}

void trocaMultipla(F *f, Pi *p) {
    if (f->total < 3 || p->topo < 2) {
        printf("Não é possível realizar a troca múltipla: fila ou pilha com menos de 3 peças.\n");
        return;
    }

    for (int i = 0; i < 3; i++) {
        int idxFila = (f->inicio + i) % MAX;      
        int idxPilha = p->topo - i;                

        P aux = f->itens[idxFila];
        f->itens[idxFila] = p->itens[idxPilha];
        p->itens[idxPilha] = aux;
    }

    printf("Troca múltipla realizada com sucesso!\n");
}



P gerarPeca() {
    P peca;
    static int contador = 0;
    char tipos[] = {'I', 'O', 'T', 'L'};
    peca.nome = tipos[rand() % 4];
    peca.id = contador++;
    return peca;
}

void usarPeca(Pi *p) {
    if (pilhaVazia(p)) {
        printf("Não é possível usar peça. Pilha vazia.\n");
        return;
    }
    P removida = p->itens[p->topo];
    p->topo--;
    printf("Peça usada: [%c %d]\n", removida.nome, removida.id);
}

int main() {
    F f;
    Pi pil;
    int opcao;
    P p;

    inicializarFila(&f);
    for (int i = 0; i < MAX; i++) {
        inserir(&f, gerarPeca());
    }

    inicializarPilha(&pil);

    while (1) {
        printf("\n--------- MENU ---------\n");
        mostrarFila(&f);
        printf("\n");
        mostrarPilha(&pil);

        printf("\nOpções de ação:\n");
        printf("1 - Jogar uma peça\n");
        printf("2 - Reservar uma peça\n");
        printf("3 - Usar uma peça reservada\n");
        printf("4 - Trocar peças\n");
        printf("5 - Troca Múltipla\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                remover(&f, &p);
                printf("Peça jogada: [%c %d]\n", p.nome, p.id);
                inserir(&f, gerarPeca());
                break;

            case 2:
                movepeca(&f, &pil);
                inserir(&f, gerarPeca());
                break;

            case 3:
                usarPeca(&pil);
                break;

            case 4:
                trocaPecas(&pil, &f);
                break;

            case 5:
                trocaMultipla(&pil, &f);
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

