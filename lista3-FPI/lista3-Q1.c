/* código feito com apoio do Gemini, mesmo ele errando as saídas, 
me ajudou com a lógica e com a manipulação dos arrays.
Outra ferramenta foi o site diffchecker, que me auxiliou a visualizar
os erros nas saídas (espaços a mais ou a menos) */

#include <stdio.h>

int main() {

    int t; // numero de entradas
    if(scanf("%d", &t) == 1){
        while (t--) { // looping para cada entrada
            int n; // tamanho da sequencia
            scanf("%d", &n);
            int seq[100]; // sequencia de numeros
            for (size_t i = 0; i < n; i++) {
                scanf("%d", &seq[i]);
            }  

            int tam_atual = 0, tam_max = 0; // tamanho da sequencia
            int inicio_atual = 0, inicio_melhor = 0; // indices para comparar
            
            for (size_t i = 0; i < n; i++) {
                //inicio da sequencia ou o numero é menor que o anterior
                if (i == 0 || seq[i] < seq[i-1]){
                    if (tam_atual == 0){
                        inicio_atual = i; // inicio da sequencia
                    }
                    tam_atual++; // incrementa o tamanho da sequencia
                } else {
                    if (tam_atual > tam_max && tam_atual > 1) { // verifica se a sequencia atual é maior que a melhor
                        //sendo assim, vamos iniciar nova sequencia
                        tam_max = tam_atual; // atualiza o tamanho maximo
                        inicio_melhor = inicio_atual; // atualiza o inicio da melhor sequencia
                    }
                    tam_atual = 1; // reinicia o tamanho da sequencia
                    inicio_atual = i; // reinicia o inicio da sequencia
                }
                    
            }

            // verificação final
            if (tam_atual > tam_max && tam_atual > 1) {
                tam_max = tam_atual;
                inicio_melhor = inicio_atual;
            }

            //output do programa
            if (tam_max > 1){ //se a seq for maior que 1
                printf("%d\n", tam_max);
                for (size_t i = 0; i < tam_max; i++) {
                    printf("%d", seq[inicio_melhor + i]);
                    if (i == tam_max - 1) {
                        printf(" \n"); // quebra de linha
                    }else {
                        printf(" "); // espaçs entre termos da sequencia
                    }
                }
            } else {
                printf("0\n");
            }
        }
    }

	return 0;
}