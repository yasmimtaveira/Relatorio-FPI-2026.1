// Questao feita sem uso de IA
#include <stdio.h>

int main(){
    char C;
    scanf("%c", &C);
    int linhas = C - 'A' + 1; // saber quantas linhas tem a piramide

    for (int i = 1; i <= linhas; i++){
        // pontos da esquerda
        for (int p = 0; p < linhas - i; ++p){
            printf("%s", ".");
        }

        // printf das letras
        for (int j = 0; j < i; j++){
            printf("%c", j + 65);
        } 
        for (int j = 2; j <= i; j++){
            if (i>1){
                printf("%c", 65 + i - j);
            }
        } 

        // pontos da direita
        for (int p = 0; p < linhas - i; ++p){
            printf("%s", ".");
        }
        puts(""); // pular para prox linha
    }

    return 0;
}