/*Código feito com auxílio do Claude, precisei fazer alterações para ajustar uma saída e
fazer o código aapenas usando a função main. A lógica é testar cada número do intervalo
de N a K, somando seus fatores primos distintos, além de verificar se eles não se repetem.
*/
#include <stdio.h>

int main() {

    int Q = -1;
    int primeiro = -1; // Variavel para armazenar o primeiro numero encontrado
    int N, K, P;
    scanf("%d %d %d", &N, &K, &P);


    for (int j = N; j < K; j++){ // Testa cada numero do intervalo

        int dividido = j;
        int invalido = 0;
        int cont = 0;
        while (dividido % 2 == 0){
            dividido /= 2;
        }

        for (int i = 3; i * i <= dividido; i += 2){ // contar os fatores primos distintos, verificando se eles se repetem
            if (dividido % i == 0){
                dividido /= i;
                cont++;
                if (dividido % i == 0){ // nao pode repetir fator impar
                    invalido = 1;
                }
            }
        }
        if (dividido > 1) { // se ainda houver um fator primo
            cont++;
        }

        if (cont == P && invalido == 0){ // contagem dos numeros validos
            Q++;
            if (primeiro == -1){
                primeiro = j;
            }
        }
    }

    // output
    if (primeiro == -1) {
        printf("Poxa dudinha, me desculpa, nao achei os numeros mas vou te mandar uma foto de um gatinho fofo.");
    } else {
        printf("%d %d", primeiro, Q);
    }

    return 0;
}