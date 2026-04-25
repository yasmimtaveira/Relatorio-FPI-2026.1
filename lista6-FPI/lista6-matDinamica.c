// código tranquilo para entender o conceito inicial de ponteiros para funcoes
// consegui fazer sem IA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// funções para manipulação da matriz
int** alocarMatriz(int l, int c);
void lerMatriz(int **matriz, int l, int c);
void imprimirMatriz(int **matriz, int l, int c);
void liberarMemoria(int **matriz, int l);
void operacao(int **matriz, int l, int c, void (*funcao)(int **matriz, int l, int c));

// funções para as operações
void dobro(int **matriz, int l, int c);
void quadrado(int **matriz, int l, int c);
void absoluto(int **matriz, int l, int c);

int main() {

    int l, c, op;
    scanf("%d %d", &l, &c);

    // alocação
    int **matriz = alocarMatriz(l, c);

    // verificação de alocação
    if (matriz == NULL) {
        exit(1);
    }

    // leitura da matriz
    lerMatriz(matriz, l, c);

    // operação do usuário
    scanf("%d", &op);

    // realiza a operação escolhida
    if (op == 1) {
        operacao(matriz, l, c, dobro);
    } else if (op == 2) {
        operacao(matriz, l, c, quadrado);
    } else if (op == 3) {
        operacao(matriz, l, c, absoluto);
    }

    // impressão da matriz
    imprimirMatriz(matriz, l, c);

    // liberação da memória
    liberarMemoria(matriz, l);

    return 0;
}

int **alocarMatriz(int l, int c){
    int **matriz = (int **)malloc(l * sizeof(int *));
    for (int k = 0; k < l; k++){
        matriz[k] = (int *)malloc(c * sizeof(int));

        // verificação de alocação
        if (matriz[k] == NULL) {
            // libera a memória alocada até o momento
            for (int i = 0; i < k; i++) {
                free(matriz[i]);
            }
            free(matriz);
            return NULL; // retorna NULL para indicar falha
        }
    }
    return matriz;
}

void lerMatriz(int **matriz, int l, int c){
    for (int i = 0; i < l; i++){
        for (int j = 0; j < c; j++){
            scanf("%d", &matriz[i][j]);
        }
    }
}

void operacao(int **matriz, int l, int c, void (*funcao)(int **matriz, int l, int c)){
    funcao(matriz, l, c);
}

void imprimirMatriz(int **matriz, int l, int c){
    for (int linha = 0; linha < l; linha ++){
        for (int col = 0; col < c; col++){
            printf("%d ", matriz[linha][col]);
        }
        printf("\n");
    }
}

void liberarMemoria(int **matriz, int l) {
    for (int i = 0; i < l; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

void dobro(int **matriz, int l, int c){
    for (int i = 0; i < l; i++){
        for (int j = 0; j < c; j++){
            matriz[i][j] *= 2;
        }
    }
}

void quadrado(int **matriz, int l, int c){
    for (int i = 0; i < l; i++){
        for (int j = 0; j < c; j++){
            matriz[i][j] = matriz[i][j] * matriz[i][j];
        }
    }
}
void absoluto(int **matriz, int l, int c){
    for (int i = 0; i < l; i++){
        for (int j = 0; j < c; j++){
            matriz[i][j] = abs(matriz[i][j]);
        }
    }
}