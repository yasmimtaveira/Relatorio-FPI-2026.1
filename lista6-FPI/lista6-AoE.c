// codigo feito com auxilio de IA apenas para estudo das estruturas e explicação dos test cases
// consegui concertar um erro nessa questão após fazer o teste que se assemelhava a essa!

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void arcana(int **matriz, int l, int c, int x, int y);
void nuvemVenenosa(int **matriz, int l, int c, int x, int y);
void executaAtaque(int **matriz, int l, int c, int x, int y, void (*funcao)(int **matriz, int l, int c, int x, int y));
int contarVizinhos(int **matriz, int l, int m, int x, int y);
void imprimirMatriz(int **matriz, int l, int c);
int **copiaMatriz(int **matriz, int l, int c);

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    // alocando a matriz dinamicamente
    int **matriz = (int **)malloc(m * sizeof(int *));

    if (matriz == NULL) exit(1);

    for (int i = 0; i < m; i++) {
        matriz[i] = (int *)malloc(n * sizeof(int));
        if (matriz[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(matriz[j]); // liberando o espaço alocado ate o momento
            }
            free(matriz);
            exit(1);
        }
    }

    // leitura da entrada do usuario
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matriz[i][j]);
        }
    }

    int x, y;
    scanf("%d %d", &x, &y);
    char ataque[17];
    scanf("%s", ataque);

    // print da matriz inicial
    printf("%s", "Estado inicial do mapa:\n");
    imprimirMatriz(matriz, m, n);

    int **matrizResultante = copiaMatriz(matriz, m, n);
    // verificacao da alocacao
    if (matrizResultante == NULL) exit(1);

    // execucao do ataque e print da matriz resultante
    if (strcmp(ataque, "EXPLOSAO_ARCANA") == 0){
        printf("%s", "\nEstado do mapa após usar a Explosão Arcana:\n");
        executaAtaque(matrizResultante, m, n, x, y, arcana);
        imprimirMatriz(matrizResultante, m, n);

    } else {
        printf("%s", "\nEstado do mapa, por turno, após usar a Nuvem Venenosa:\n");
        executaAtaque(matrizResultante, m, n, x, y, nuvemVenenosa);
    }

    // liberacao da memoria
    liberarMemoria(matriz, m);
    liberarMemoria(matrizResultante, m);

    return 0;
}

void imprimirMatriz(int **matriz, int m, int n){
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

int **copiaMatriz(int **matriz, int l, int c){
    int **matrizNova = (int **)malloc(l * sizeof(int *));
    // verificacao de alocacao
    if (matrizNova == NULL) return NULL;

    for (int i = 0; i < l; i++) {
        matrizNova[i] = (int *)malloc(c * sizeof(int));
        if (matrizNova[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(matrizNova[j]);
            }
            free(matrizNova);
            return NULL;
        }
    }

    for (int k = 0; k < l; k++){ // copia da matriz original
        for (int h = 0; h < c; h++){
            matrizNova[k][h] = matriz[k][h];
        }
    }
    return matrizNova;
}

void arcana(int **matriz, int l, int c, int x, int y){

    for (int variaX = x-2; variaX <= x+2; variaX++){
        for (int variaY = y-2; variaY <= y+2; variaY++){
            if ((variaX)>=0 && (variaX)<l && (variaY)>=0 && (variaY)<c){
                // verificacao da zona de dano
                if ((abs(variaX-x) + abs(variaY-y)) <= 1){ // camada 1
                    matriz[variaX][variaY] = fmax(0, matriz[variaX][variaY] - 50);
                } else if ((abs(variaX-x) + abs(variaY-y)) < 4){ // camada 2
                    matriz[variaX][variaY] = fmax(0, matriz[variaX][variaY] - 25);
                }

            }
        }
    }
}

void nuvemVenenosa(int **matriz, int l, int c, int x, int y){
    int playersNaZona = 0;

    for (int t = 0; t < 3; t++){
        int **matrizAnterior = copiaMatriz(matriz, l, c);
        if (matrizAnterior == NULL) exit(1);

        for (int variaX = x-2; variaX <= x+2; variaX++){
            for (int variaY = y-2; variaY <= y+2; variaY++){
                if ((variaX)>=0 && (variaX)<l && (variaY)>=0 && (variaY)<c){
                    if ((abs(variaX-x) + abs(variaY-y)) < 4 && matriz[variaX][variaY] > 0){ // verificacao se esta dentro da zona de dano
                        int vizinhos = contarVizinhos(matrizAnterior, l, c, variaX, variaY);
                        int dano = 5 + (8 * vizinhos);
                        matriz[variaX][variaY] = fmax(0, matriz[variaX][variaY] - dano);
                    }
                }
            }
        }
        imprimirMatriz(matriz, l, c);
        printf("\n");

        // pontos de vida reduzidos a 0 antes do terceiro turno
        for (int variaX = x-2; variaX <= x+2; variaX++){
            for (int variaY = y-2; variaY <= y+2; variaY++){
                if ((variaX)>=0 && (variaX)<l && (variaY)>=0 && (variaY)<c){
                    if ((abs(variaX-x) + abs(variaY-y)) < 4){ // verificacao se esta dentro da zona de dano
                        if (matriz[variaX][variaY] > 0) playersNaZona++;
                    }
                }
            }
        }
        liberarMemoria(matrizAnterior, l); // liberacao da matriz anterior
        if (playersNaZona == 0) break; // se nao houver mais vizinhos vivos, o ataque termina
        playersNaZona = 0; // reset do contador de players na zona para o proximo turno
    }
}

void executaAtaque(int **matriz, int l, int c, int x, int y, void (*funcao)(int **matriz, int l, int c, int x, int y)){
    funcao(matriz, l, c, x, y);
}

int contarVizinhos(int **matriz, int l, int c, int x, int y){
    int contador = 0;
    for (int variaX = x-1; variaX <= x+1; variaX++){
        for (int variaY = y-1; variaY <= y+1; variaY++){
            if (variaX >= 0 && variaX < l && variaY >= 0 && variaY < c){ // celulas dentro da matriz
                if (matriz[variaX][variaY] > 0){ // celulas positivas
                    if (variaX != x || variaY != y) contador++; // nao conta a propria celula (x,y)
                }
            }
        }
    }
    return contador;
}

void liberarMemoria(int **matriz, int l) {
    for (int i = 0; i < l; i++) {
        free(matriz[i]);
    }
    free(matriz);
}
