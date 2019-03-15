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

//Faz função de união entre conjuntos
void juntar(int a, int b) {
    
    //Se o prox de a e b forem iguais a 0, significa que eles estão contidos 
    //em um subconjunto com apenas um elemento (eles mesmos)
    //O grupo de b recebe o grupo de a para que simbolize que estão no 
    //mesmo grupo
    //O início de a e b aponta para a 
    //O próximo de a e b recebe 1 para simbolizar que nao estão mais em um 
    //conjunto com um elemento.
    if (C[a]->prox == 0 && C[b]->prox == 0) {
        C[b]->grupo = C[a]->grupo;
        C[a]->inicio = C[a];
        C[b]->inicio = C[a];
        C[a]->prox = 1;
        C[b]->prox = 1;
    //Se o próximo de a for 1 e o de b for 0 significa que o a está em um 
    //conjunto com mais elementos e b em um conjunto com um elemento
    //O grupo de b recebe o grupo de a
    //O próximo de b recebe 1 para simbolizar que ele pertence a um conjunto 
    //com mais de um elemento.
    } else if (C[a]->prox == 1 && C[b]->prox == 0) {
        C[b]->grupo = C[a]->grupo;
        C[b]->inicio = C[a]->inicio;
        C[b]->prox = 1;
    //Faz exatamente o mesmo que a condicional anterior só que agora o b que 
    //está contido em um conjunto com mais elementos e a em um conjunto com 
    //apenas ele mesmo.
    } else if (C[a]->prox == 0 && C[b]->prox == 1) {
        C[a]->grupo = C[b]->grupo;
        C[a]->inicio = C[b]->inicio;
        C[a]->prox = 1;
    //Se o prox de a e b for 1 significa que eles estão contidos em um conjunto 
    //com mais de um elemento
    //Atribui no conjunto do início de a na posição do grupo de b o valor 1
    //Faz o mesmo no conjunto do início de b na posição do grupo de a
    } else if (C[a]->prox == 1 && C[b]->prox == 1) {
        C[a]->inicio->conjunto[C[b]->grupo] = 1;
        C[b]->inicio->conjunto[C[a]->grupo] = 1;
        //Se o anterior de a e de b forem diferentes de NULL, significa que 
        //eles já foram unidos com outro conjunto anteriormente
        //Atribui no conjunto do anterior do inicio de a na posição do grupo de 
        //b o valor 1
        //Faz o mesmo no conjunto do inicio do anterior de b na posição a
        if(C[a]->inicio->anterior != NULL && C[b]->inicio->anterior != NULL) {
            C[a]->inicio->anterior->conjunto[C[b]->grupo] = 1;
            C[b]->inicio->anterior->conjunto[C[a]->grupo] = 1;
        }
        //Se o anterior de a for igual a NULL e o de b for diferente de NULL
        //significa que apenas b foi unido com outro conjunto anteriormente
        //Faz as modificações feitas anteriormente só que apenas em b
        else if(C[a]->inicio->anterior == NULL && C[b]->inicio->anterior != NULL) {
            C[b]->inicio->anterior->conjunto[C[a]->grupo] = 1;
        }
        //Nesse caso o anterior de a é diferente de NULL e o de b é igual a NULL
        //siginifica que apenas a foi unido com outro conjunto anteriormente
        //Faz as modificações feitas anteriormente só que apenas em a
        else if(C[a]->inicio->anterior != NULL && C[b]->inicio->anterior == NULL) {
            C[b]->inicio->anterior->conjunto[C[a]->grupo] = 1;
        }
        //Aponta o anterior do início de a para o inicio de b
        //e o anterior do início de b para o inicio de a
        C[a]->inicio->anterior = C[b]->inicio;
        C[b]->inicio->anterior = C[a]->inicio;
    }
}

//Testa se dois números estão contidos no mesmo grupo
void teste(int a, int b) {
    //Se o grupo de a for igual ao grupo de b printa True
    if (C[a]->grupo == C[b]->grupo) {
        printf("\nTrue");
        return;
    //Se no conjunto do inicio de a na posição do grupo de b for igual a 1
    //ou no conjunto do inicio de b na posição do grupo de a for igual a 1
    //printa True
    } else if (C[a]->inicio->conjunto[C[b]->grupo] == 1 || C[b]->inicio->conjunto[C[a]->grupo] == 1) {
        printf("\nTrue");
        return;
    //Se o anterior de a e de b for diferente de NULL
    //Ele verifica no conjunto do anterior do início de a no grupo de b
    //e no anterior do inicio de b no grupo de a se é igual a 1
    //se for verdade printa True
    } else if(C[a]->anterior != NULL && C[b]->anterior != NULL) {
        if(C[a]->inicio->anterior->conjunto[C[b]->grupo] == 1 || C[a]->inicio->anterior->conjunto[C[b]->grupo] == 1) {
            printf("\nTrue");
            return;
        }
    //Faz o mesmo que o anterior mas só checa no anterior do início de a
    } else if(C[a]->anterior != NULL && C[b]->anterior == NULL) {
        if(C[a]->inicio->anterior->conjunto[C[b]->grupo] == 1) {
            printf("\nTrue");
            return;
        }
    //Faz o mesmo que o anterior mas só checa no anterior do início de b
    } else if(C[a]->anterior == NULL && C[a]->anterior != NULL) {
        if(C[b]->inicio->anterior->conjunto[C[a]->grupo] == 1) {
            printf("\nTrue");
            return;
        }
    }
    //Printa false se nenhum anterior for verdade
    printf("\nFalse");
}

//Preenche o vetor C inicial
//Cada posição de C é um no, logo são setados valores iniciais para os campos
//de cada no de C
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

//Libera a memória que foi alocada
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
