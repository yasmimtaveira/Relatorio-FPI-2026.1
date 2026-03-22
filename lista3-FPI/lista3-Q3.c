/* código feito com auxílio do Gemini para entender a lógica 
e a contagem das letras de um jeito eficiente
*/ 
#include <stdio.h>
#include <string.h>

int main() {
    char frase[101];
    int total_pares = 0;
    int encontrou = 0;

    // Lendo a frase (ignorando espaços)
    scanf("%[^\n]", frase);

    int tam_total = strlen(frase);

    for (int i = 0; i < tam_total; i++) { // varrendo os caracteres da frase
        // ---- 1ª palavra -----
        // verificando se é uma letra
        if ((frase[i] >= 'a' && frase[i] <= 'z') || (frase[i] >= 'A' && frase[i] <= 'Z')) {
            int fim1 = i; // variavel para saber em qual indice a palavra termina
            while (fim1 < tam_total && ((frase[fim1] >= 'a' && frase[fim1] <= 'z') || (frase[fim1] >= 'A' && frase[fim1] <= 'Z'))) {
                fim1++;
                // incrementa o fim da palavra enquanto o prox caractere for letra
            }

            // ---- 2ª palavra -----
            for (int k = fim1; k < tam_total; k++) {
                if ((frase[k] >= 'a' && frase[k] <= 'z') || (frase[k] >= 'A' && frase[k] <= 'Z')) {
                    int fim2 = k;
                    while (fim2 < tam_total && ((frase[fim2] >= 'a' && frase[fim2] <= 'z') || (frase[fim2] >= 'A' && frase[fim2] <= 'Z'))) {
                        fim2++; // fim da 2ª palavra
                    }

                    // Comparação de tamanho
                    if ((fim1 - i) == (fim2 - k)) {
                        // arrrays para contar quantas vezes cada uma das 26 letras do alfabeto aparece em cada palavra
                        int freq1[26] = {0}; // palavra 1
                        int freq2[26] = {0}; // palavra 2

                        // Conta letras da palavra 1
                        for (int x = i; x < fim1; x++) {
                            char c = frase[x];
                            if (c >= 'A' && c <= 'Z') c += 32; // se for maiuscula, converto para minuscula
                            freq1[c - 'a']++; // atualizo quantas vezes a letra apareceu na palavra
                        }
                        // Conta letras da palavra 2
                        for (int x = k; x < fim2; x++) {
                            char c = frase[x];
                            if (c >= 'A' && c <= 'Z') c += 32; // se for maiuscula, converto para minuscula
                            freq2[c - 'a']++;
                        }

                        int eh_anagrama = 1;
                        for (int x = 0; x < 26; x++) {
                            if (eh_anagrama != 0){
                                if (freq1[x] != freq2[x]) { // analisa se tem a mesma quantidade de cada letra nas palavras
                                eh_anagrama = 0;
                                }
                            }
                        }

                        if (eh_anagrama) {
                            if (encontrou == 0) {
                                printf("Pares de anagramas encontrados:\n");
                                encontrou = 1; // para printar só dps de encontrar o 1º anagrama
                            }
                            // print dos pares
                            for (int x = i; x < fim1; x++) printf("%c", frase[x]);
                            printf(" e ");
                            for (int x = k; x < fim2; x++) printf("%c", frase[x]);
                            printf("\n");
                            total_pares++;
                        }
                    }
                    k = fim2; // pula o contador para não repetir pares
                }
            }
            i = fim1; // pula o contador para não repetir pares
        }
    }

    if (encontrou) {
        printf("\nTotal de pares: %d\n", total_pares);
    } else {
        printf("Nao existem anagramas na frase.\n");
    }

    return 0;
}
