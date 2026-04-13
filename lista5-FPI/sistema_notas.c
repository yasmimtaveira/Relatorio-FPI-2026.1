// questao feita sem uso de IA para gerar código, apenas com estudos sobre alocação dinamica
/* por enquanto minha solução para a moda não é genérica como deveria, pois não considera
notas "quabradas" na contagem das frequencias (para identificar quando a moda é única), mas caso 
consiga uma solução mais eficaz dentro do prazo da lista, atualizarei o código */

#include <stdio.h>
#include <stdlib.h>

// protótipos das funções
float media(float *notas, int n);
void maiorNota(float *notas, int n);
void menorNota(float *notas, int n); 
void acimaMedia(float *notas, int n);
void mediana(float *notas, int n);
void moda(float *notas, int n);

int main(){
    int n, k;
    scanf("%d", &n);
    
    // alocando memoria para n notas
    float *notas = (float *)malloc(n * sizeof(float));
    if (notas == NULL) {
        return 1; // saindo com erro
    }

    // recebe n numeros reais
    for (int i = 0; i < n; i++) {
        scanf("%f", &notas[i]);
    }

    // relatório inicial
    printf("%s\n", "Relatorio inicial");
    float mediaInicial = media(notas, n);
    printf("Media: %.2f\n", mediaInicial);

    maiorNota(notas, n);
    menorNota(notas, n);    
    acimaMedia(notas, n);
    mediana(notas, n);
    moda(notas, n);

    scanf("%d", &k); // quant de novas notas
    // realoca a memoria para n+k notas
    float *notasAtual = (float*) realloc(notas, (n+k) * sizeof(float));
    if (notasAtual == NULL) { // teste
        return 1; // saindo com erro
    }
    // recebe k novas notas
    for (int i = n; i < n+k; i++) {
        scanf("%f", &notasAtual[i]);
    }

    // relatorio atualizado
    printf("\n%s\n", "Relatorio atualizado");
    float mediaAtual = media(notasAtual, n+k);
    printf("Media: %.2f\n", mediaAtual);

    maiorNota(notasAtual, n+k);
    menorNota(notasAtual, n+k);    
    acimaMedia(notasAtual, n+k);
    mediana(notasAtual, n+k);
    moda(notasAtual, n+k);

    // liberando a memoria alocada
    free(notasAtual);

    return 0;
}

float media(float *notas, int n){
    float soma = 0;
    for (int i = 0; i < n; i++){
        soma += notas[i];
    }
    return soma/n;
}

void maiorNota(float *notas, int n){
    float maior = notas[0];
    int aluno = 1;
    for (int i = 1; i < n; i++){
        if (notas[i] > maior){
            maior = notas[i];
            aluno = 1 + i;
        }
    }
    printf("Maior nota: %.2f (aluno %d)\n", maior, aluno);
}

void menorNota(float *notas, int n){
    float menor = notas[0];
    int aluno = 1;
    for (int i = 1; i < n; i++){
        if (notas[i] < menor){
            menor = notas[i];
            aluno = 1 + i;
        }
    }
    printf("Menor nota: %.2f (aluno %d)\n", menor, aluno);
}

void acimaMedia(float *notas, int n){
    float mediaLocal = media(notas, n); // uso a prórpia função media para calcular a media local
    int total = 0;

    for (int i = 0; i < n; i++){
        if (notas[i] > mediaLocal){
            total++;
        }
    }
    printf("Acima da media: %d\n", total);
}

void mediana(float *notasRecebidas, int n){
    float notas[n]; // criando um array local para nao modificar o array original
    for (int i = 0; i < n; i++){
        notas[i] = notasRecebidas[i];
    }
    // ordenando as notas
    for (int i = 0; i < n-1; i++){
        for (int j = 0; j < n-i-1; j++){
            if (notas[j] > notas[j+1]){
                float temp = notas[j]; // variavel temporaria para auxiliar na troca
                notas[j] = notas[j+1];
                notas[j+1] = temp;
            }
        }
    }

    float mediana;
    if (n % 2 == 0){ // numero de notas par
        mediana = (notas[n/2 - 1] + notas[n/2]) / 2;
    } else { // numero de notas impar
        mediana = notas[n/2];
    }
    printf("Mediana: %.2f\n", mediana);
}

void moda(float *notas, int n){
    int modaUnica = 1; // flag para verificar se a moda é única

    int frequencia[11] = {0}; // array para contar a frequencia das notas de 0 a 10

    for (int i = 0; i < n; i++){ // contando as frequencias
        int notaAluno = (int)notas[i];
        frequencia[notaAluno]++;
    }

    float moda = 0; // inicializando as variaveis
    int max = frequencia[0];
    for (int i = 1; i < 10; i++){
        if (frequencia[i] > max){
            max = frequencia[i];
            moda = (float)i; // encontrei uma moda
        }
    }

    for (int i = 0; i < 10; i++){ // comparar as frequencias
        for (int j = 0; j < i; j++){
            if (frequencia[i] == frequencia[j] && frequencia[i] == max){
                modaUnica = 0; // encontrou outra nota com a mesma frequencia máxima
            }
        }
    }

    if (modaUnica){
        printf("Moda: %.2f\n", moda);
    } else {
        printf("%s\n", "Moda: Nao ha moda unica");
    }
}