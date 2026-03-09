// Uso do Claude e Gemini para auxiliar a montar o cálculo das somas

#include <stdio.h>

int main() {
    long long N, A, B;
    scanf("%lld", &N);
    scanf("%lld %lld", &A, &B);

    long long somaTotal = N * (N + 1) / 2; 
    long long somaA     = (A + A*(N/A)) * (N/A) / 2;
    long long somaB     = (B + B*(N/B)) * (N/B) / 2;
    long long somaAB    = (A * B + A * B*(N/(A * B))) * (N/(A * B)) / 2;

    // Inclusão-Exclusão
    long long resultado = somaTotal - somaA - somaB + somaAB;

    printf("%lld\n", resultado);
    if (resultado % 2 == 0) { //PAR
        puts("Lá ele!!!");
    } else {
        puts("Opa xupenio AULAS...");
    }
    return 0;
}