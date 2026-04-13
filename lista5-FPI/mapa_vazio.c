// codigo feito com estudos sobre alocação dinamica com a ferramenta gemini
/*crio uma array dinamica e se o tamanho nao for suficientes, 
uso realloc criando uma nova array e depois a array antiga recebe a nova*/

#include <stdio.h>
#include <stdlib.h>

int main(){
    int *array = NULL; // iniciando o ponteiro
    int capacidade = 2; // capacidade que vou iniciar
    int tam = 0;
    int n;
    array = (int *)malloc(capacidade * sizeof(int)); // alocando o array

    if (array == NULL) { // verificando para evitar erros
        return 1; // saindo com erro
    }
    // entrada
    //Várias linhas, cada uma com apenas um número inteiro positivo(N).
    while (scanf("%d", &n) == 1 && n > 0) {
        // ver se o array esta cheio
        if (tam == capacidade){
            // uso o realloc para dobrar a capacidade
            capacidade *= 2;
            int *novoArray = realloc(array, capacidade * sizeof(int));
            
            if (novoArray == NULL) { // verificando para evitar erros
                free(array); // liberando a memória alocada
                return 1; // saindo com erro
            }
            array = novoArray;
        }
        array[tam] = n; // adicionando o número ao array
        tam++; // incrementando o tamanho apos receber cada numeri
    }

    printf("%s\n", "Mais um bom dia de trabalho!");
    /*
    impressos cada número ímpar seguido por quebra de linha.
    Então, serão impressos cada número par, seguidos por quebra de linha.*/
    
    for (int i = 0; i < tam; i++) {
        if (array[i] % 2 != 0) { // se é impar
            printf("%d\n", array[i]);
        }
    }

    for (int i = 0; i < tam; i++) {
        if (array[i] % 2 == 0) { // se é par
            printf("%d\n", array[i]);
        }
    }

    printf("%s\n", "Vou visitar esses lugares de novo... algum dia.");
    return 0;
}