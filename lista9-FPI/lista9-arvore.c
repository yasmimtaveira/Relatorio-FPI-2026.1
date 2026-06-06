// código feito com base no conteudo disponibilizado pelo professor e video aulas

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct treeNode {
    int num;
    struct treeNode *esquerda;
    struct treeNode *direita;
}TreeNode;

typedef TreeNode *TreeNodePtr; // sinonimo para TreeNode *

void insertNode(TreeNodePtr *treePtr, int value);
void inOrder(TreeNodePtr treePtr);
void preOrder(TreeNodePtr treePtr);
void postOrder(TreeNodePtr treePtr);
int contarNos(TreeNodePtr treePtr);
int altura(TreeNodePtr treePtr);
int folhas(TreeNodePtr treePtr);

int main(){
    
    TreeNodePtr raiz = NULL; // raiz da arvore vazia
    
    int num;
    scanf("%d", &num);
    int menor = num;
    int maior = num;

    while(num != -1){
        insertNode(&raiz, num); // inserir os nós
        if (num < menor) menor = num; // compara para atualizar as variaveis
        if (num > maior) maior = num;
        scanf("%d", &num); // lê novamente a entrada do usuario
    }

    if (raiz){ // raiz nao é nula -> arvore nao vazia
        printf("PREORDEM:");
        preOrder(raiz);
        printf("\nEMORDEM:");
        inOrder(raiz);
        printf("\nPOSORDEM:");
        postOrder(raiz);
        printf("\nNOS: %d", contarNos(raiz));
        printf("\nFOLHAS: %d", folhas(raiz));
        printf("\nALTURA: %d", altura(raiz));
        printf("\nMENOR: %d", menor);
        printf("\nMAIOR: %d", maior);

    } else { // raiz nula -> arvore vazia
        printf("ARVORE VAZIA");
    }
    return 0;
}

void insertNode(TreeNodePtr *treePtr, int num){
    if (*treePtr == NULL){ // arvore vazia, aqui vai ocorrer a inserção
        *treePtr = malloc(sizeof(TreeNode)); // alocacar memoria
        if (*treePtr){ // alocacao ok
            (*treePtr)->num = num;
            (*treePtr)->esquerda = NULL;
            (*treePtr)->direita = NULL;
        } else {
            printf("erro de alocacao");
        }
    } else { // arvore nao vazia: vefificacao e recursao
        if (num < (*treePtr)->num){ // inserir a esquerda
            insertNode(&((*treePtr)->esquerda), num);
    
        }else if (num > (*treePtr)->num){ // inserir a direita
            insertNode(&((*treePtr)->direita), num);
        } // ignora os iguais
    }
}

void inOrder(TreeNodePtr treePtr){ // esquerda -> processa -> direita
    if (treePtr){
        inOrder(treePtr->esquerda);
        printf(" %d", treePtr->num);
        inOrder(treePtr->direita);
    }
}

void preOrder(TreeNodePtr treePtr){ // processa -> esquerda -> direita
    if (treePtr){
        printf(" %d", treePtr->num);
        preOrder(treePtr->esquerda);
        preOrder(treePtr->direita);
    }
}

void postOrder(TreeNodePtr treePtr){ // esquerda -> direita -> processa
    if (treePtr){
        postOrder(treePtr->esquerda);
        postOrder(treePtr->direita);
        printf(" %d", treePtr->num);
    }
}

int contarNos(TreeNodePtr treePtr){
    if (treePtr != NULL){ // arvore nao vazia
        // no atual + contagem dos nos da esquerda + nos da direita
        return 1 + contarNos(treePtr->esquerda) + contarNos(treePtr->direita);
    }
    return 0;
}

int altura(TreeNodePtr treePtr){
    if (treePtr == NULL){
        return -1; // altura da arvore vazia: -1
    } else {
        int esquerda = altura(treePtr->esquerda);
        int direita = altura(treePtr->direita);
        if (esquerda > direita){ // altura é a maior distancia da raiz ate uma folha
            return esquerda + 1; // soma 1 por conta do no atual
        } else {
            return direita + 1;
        }
    }
}

int folhas(TreeNodePtr treePtr){
	if (treePtr != NULL){ // nao é nulo
		if (treePtr->esquerda == NULL && treePtr->direita == NULL){ // é uma folha
		 return 1;
		} else { // nao é folha, ent chamamos a recursao para esquerda e direita
			int esq = folhas(treePtr->esquerda);
			int dir = folhas(treePtr->direita);
			return esq + dir; // 
		}
	} else { // é nulo
		return 0;
	}
}