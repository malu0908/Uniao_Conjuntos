@@ -0,0 +1,114 @@
#include <stdio.h> 
#include <stdlib.h>
#define TAMANHO 11

typedef struct no_ no;

struct no_ {
    int valor;
    int prox;
    no* inicio;
    no* anterior;
    int grupo;
    int conjunto[TAMANHO];
};

no* C[TAMANHO];

void juntar(int a, int b) {
    if (C[a]->prox == 0 && C[b]->prox == 0) {
        C[b]->grupo = C[a]->grupo;
        C[a]->inicio = C[a];
        C[b]->inicio = C[a];
        C[a]->prox = 1;
        C[b]->prox = 1;
    } else if (C[a]->prox == 1 && C[b]->prox == 0) {
        C[b]->grupo = C[a]->grupo;
        C[b]->inicio = C[a]->inicio;
        C[b]->prox = 1;
    } else if (C[a]->prox == 0 && C[b]->prox == 1) {
        C[a]->grupo = C[b]->grupo;
        C[a]->inicio = C[b]->inicio;
        C[a]->prox = 1;
    } else if (C[a]->prox == 1 && C[b]->prox == 1) {
        C[a]->inicio->conjunto[C[b]->grupo] = 1;
        C[b]->inicio->conjunto[C[a]->grupo] = 1;
        C[a]->inicio->anterior = C[b]->inicio;
        C[b]->inicio->anterior = C[a]->inicio;
        if(C[a]->inicio->anterior != NULL && C[b]->inicio->anterior != NULL) {
            C[a]->inicio->anterior->conjunto[C[b]->grupo] = 1;
            C[b]->inicio->anterior->conjunto[C[a]->grupo] = 1;
        }
        else if(C[a]->inicio->anterior == NULL && C[b]->inicio->anterior != NULL) {
            C[b]->inicio->anterior->conjunto[C[a]->grupo] = 1;
        }
        else if(C[a]->inicio->anterior != NULL && C[b]->inicio->anterior == NULL) {
            C[b]->inicio->anterior->conjunto[C[a]->grupo] = 1;
        }
    }
}

void teste(int a, int b) {
    if (C[a]->grupo == C[b]->grupo) {
        printf("\nTrue");
        return;
    } else if (C[a]->inicio->conjunto[C[b]->grupo] == 1 || C[b]->inicio->conjunto[C[a]->grupo] == 1) {
        printf("\nTrue");
        return;
    } else if(C[a]->anterior != NULL && C[b]->anterior != NULL) {
        if(C[a]->inicio->anterior->conjunto[C[b]->grupo] == 1 || C[a]->inicio->anterior->conjunto[C[b]->grupo] == 1) {
            printf("\nTrue");
            return;
        }
    } else if(C[a]->anterior != NULL && C[b]->anterior == NULL) {
        if(C[a]->inicio->anterior->conjunto[C[b]->grupo] == 1) {
            printf("\nTrue");
            return;
        }
    } else if(C[a]->anterior == NULL && C[a]->anterior != NULL) {
        if(C[b]->inicio->anterior->conjunto[C[a]->grupo] == 1) {
            printf("\nTrue");
            return;
        }
    }
    printf("\nFalse");
}

void preenche() {
    for (int i = 0; i <= TAMANHO; i++) {
        C[i] = malloc(sizeof (no));
        C[i]->valor = i;
        C[i]->inicio = NULL;
        C[i]->grupo = i;
        C[i]->prox = 0;
        C[i]->anterior = NULL;
    }
}

void desaloca() {
    for (int i = 0; i < TAMANHO; i++) {
        free(C[i]);
    }
}

void main() {
    //Setando os valores iniciais em cada noh
    preenche();

    juntar(0, 1);
    juntar(2, 3);
    juntar(4, 5);
    juntar(2, 5);
    juntar(0, 5);
    juntar(8, 9);
    juntar(10, 11);
    juntar(8, 11);
    juntar(10, 3);
    
    teste(0, 4);
    teste(4, 1);
    teste(9, 10);
    teste(2, 8);
    
    desaloca();
}
