// questão feita sem uso de IA (elas não conseguiram identificar os erros, mas consegui resolver sozinha)
#include <stdio.h>

int main(){
    int q, x;
    char c;
    int coluna = 0;
    int ultimoB = 0; // variavel para saber se o ultimo comando foi B
    scanf("%d", &q);

    for (int i = 1; i <= q; i++){
        scanf("%d %c", &x, &c);

        // print dos pontos
        if (c == 'D' || c == 'd'){ // direita
            if (ultimoB){ //uso isso pois o ultimo ponto de B fica na mesma linha dos pontos desse comando
                x++;
            }
            
            if (coluna > 0){ // espa�os das colunas
                for (int e = 1; e <= coluna; e++){
                    printf("%s", " ");
                }
            }
            for (int p = 1; p <= x; p++){
                printf("%s", ".");
            }
            puts(""); // pular para prox linha
            coluna += x - 1; // atualiza a coluna
            ultimoB = 0; // falso

        }else if (c == 'E' || c == 'e'){ // esquerda
            if (ultimoB){
                x++;
            }
        
            if(coluna - x <  0){
                puts("Informacao invalida");
                break;
            } else {
                coluna -= x - 1;
            }
            
            if (coluna > 0){ // espa�os da coluna
                for (int e = 1; e <= coluna; e++){
                    printf("%s", " ");
                }
            }
            
            for (int p = 1; p <= x; p++){
                printf("%s", ".");
            }
            puts("");
            ultimoB = 0;

        }else if (c == 'B' || c == 'b'){ // baixo
            for (int b = 1; b < x; b++){
                if (coluna > 0){ // espacos da coluna
                    for (int e = 1; e <= coluna; e++){
                        printf("%s", " ");
                    }
                }
                if (x > 1){ 
                    printf("%s\n", ".");
                    /* pois o ultimo ponto de B será na mesma linha do prox comando,
                    */
                }
            }
            if (i == q) { //mas se for o ultimo comando, todos os pontos de B devem ser impressos
                for (int e = 1; e <= coluna; e++){
                    printf("%s", " ");
                }
                printf("%s", ".");
            }
            ultimoB = 1;
        }
    }
    return 0; 
}