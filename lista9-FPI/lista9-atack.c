#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    char letra;
    struct node* anterior;
} Node;

typedef struct {
    Node* topo;
} Pilha;

void push(Pilha* p, char letra){ // adiciona um novo nó topo
    Node *novo = (Node*)malloc(sizeof(Node)); // cria no

    if (novo){
        novo->letra = letra; // preenche as informações
        novo->anterior = p->topo;
        p->topo = novo; // atualiza topo

    } else {
        printf("erro na alocação\n");
    }
}

Node* pop(Pilha *p){ // remove um nó do topo e retorna o nó removido
    if (p->topo){
        Node *remover = p->topo;
        p->topo = remover->anterior;
        return remover;
    } else {
        printf("pilha vazia\n");
    }
    return NULL;
}

void imprimir_pilha(Node* topo) { // funcao para imprimir
    Node* temp = topo; // auxiliar para varrer a pilha
    if (temp == NULL){
        printf("Pilha vazia!\n");
    }
    while (temp != NULL) {
        printf("%c\n", temp->letra);
        temp = temp->anterior;
    }
}

int main() {
    
    Pilha p = {NULL, 0}; // inicializo a pilha vazia
    char letra;

    // Lendo até o Fim do Arquivo (EOF)
    while (scanf(" %c", &letra) != EOF) {
        
        int processado = 0;

        while (!processado) {
            // pilha vazia, apenas insere
            if (p.topo == NULL){
                push(&p, letra);
                processado = 1;

            } else { // pilha nao vazia
                // checar se funde com o bloco do topo
                char fusao = 0; // inicializa fusao como 0
                if ((letra == 'g' && p.topo->letra == 'b') || (letra == 'b' && p.topo->letra == 'g')) fusao = 'c';
                if ((letra == 'r' && p.topo->letra == 'b') || (letra == 'b' && p.topo->letra == 'r')) fusao = 'm';
                if ((letra == 'r' && p.topo->letra == 'g' ) || (letra == 'g' && p.topo->letra == 'r')) fusao = 'y';
                
                if (fusao != 0) {
                    // topo antigo some (pop)
                    Node* removido = pop(&p);
                    free(removido);
                    letra = fusao; 
                } 
                // verificar se aparece 3 blocos iiguais
                else if (p.topo->letra == letra && p.topo->anterior && p.topo->anterior->letra == letra) {
                    Node* removido1 = pop(&p);
                    Node* removido2 = pop(&p);
                    free(removido1);
                    free(removido2);
                    processado = 1; // ignorar a letra atual
                    
                } else { // apenas empilha a atual
                    push(&p, letra);
                    processado = 1;
                }
            }
        }

        imprimir_pilha(p.topo);
        printf("\n");
    }

    printf("Thank You So Much For Playing My Game!\n");

    return 0;
}