/*Encontrei dificuldades para resolver esse problema pois ainda não estou familiarizada
com ponteiros e acabei ficando confusa sobre as restrições do conteúdo para essa lista.
Por fim, após muita pesquisa sobre alocação dinâmica e utilizando IAs como Claude e
Gemini para me auxiliar no desenvolvimento do código, aqui está a solução:*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// protótipos das funções
int temLetraRepetida(char *s);
void fusao(char *s);

int main(){

    int n;
    scanf("%d", &n);

    // lista de ponteiros que apontam para palavras
    char *listaPalavras[n];
    // lista para guardar os tamanhos
    int tamPalavras[n];
    int totalLetras = 0; // tamanho da futura mergedString

    for (int i = 0; i < n; i++){
        char entrada[1000]; // entrada temporaria com tamanho signoficativo
        scanf("%s", entrada);
        // alocando a quantidade certa de memoria para a palavra
        char *palavra = (char *)malloc((strlen(entrada)+1) * sizeof(char)); 

        if (palavra == NULL) exit(1); // verificando para evitar erros

        strcpy(palavra, entrada); // copiando a palavra recebida para a memoria alocada
        listaPalavras[i] = palavra; // guardando o endereço (ponteiro) da palavra na lista
        tamPalavras[i] = strlen(entrada); // guardando o tamanho da palavra
        totalLetras += tamPalavras[i]; // somando o total de letras
    }

    // descobrindo qual o maior tamanho de palavra para usar no laço de mesclagem
    int maiorTamanho = 0;
    for (int i = 0; i < n; i++){
        if (tamPalavras[i] > maiorTamanho){
            maiorTamanho = tamPalavras[i];
        }
    }

    // MERGED_STRING
    char *mergedString = (char *)malloc((totalLetras + 1) * sizeof(char)); // alocando memoria para a merged string

    if (mergedString == NULL) exit(1); // teste
    
    int k = 0; // indice pra mergedString
    /* pensando como se fosse uma matriz n x maiorTamanho:
    a b c d -> string de maioer tamanho
    e f
    g h i
    */
    for (int coluna = 0; coluna < maiorTamanho; coluna++){
        for (int linha = 0; linha < n; linha++){

            if (coluna < tamPalavras[linha]){ // checagem pois temos strings de tamanhos diferentes
                mergedString[k] = listaPalavras[linha][coluna]; // pegando a letra da palavra da "linha"
                k++; // incrementando o indice da mergedString
            }
        }
    }
    mergedString[totalLetras] = '\0'; // adicionando o caractere de fim de string
    printf("%s\n", mergedString);
    
    while(temLetraRepetida(mergedString)){ // while garante as fusoes depois de outra fusao
        fusao(mergedString);
    }

    // printando a string depois da fusao
    printf("%s\n", mergedString);
    
    // liberando a memoria alocada
     for (int i = 0; i < n; i++) {
         free(listaPalavras[i]);
     }
     free(mergedString);

    return 0;
}

int temLetraRepetida(char *s){
    for (int i = 0; s[i] != '\0' && s[i+1] != '\0'; i++){
        if (s[i] == s[i+1]){
            return 1; // tem letra repetida
        }
    }
    return 0; // todas as letras são diferentes
}

void fusao(char *merged){

    for (int i = 0; merged[i] != '\0' && merged[i+1] != '\0'; i++){
        if (merged[i] == merged[i+1]){
            if (merged[i] == 'z'){
                merged[i] = 'a';
            } else {
                merged[i] = merged[i] + 1; // fusao: letra repetida vira a proxima letra do alfabeto
            }

            // removendo a letra repetida (deslocando os caracteres para a esquerda)
            for (int j = i + 1; merged[j] != '\0'; j++){
                merged[j] = merged[j+1];
            }
        }
    }

}