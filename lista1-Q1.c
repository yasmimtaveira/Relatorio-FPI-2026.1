#include <stdio.h>

int main(){
    int d1, m1, a1, d2, m2, a2;
    scanf("%d/%d/%d %d/%d/%d", &d1, &m1, &a1, &d2, &m2, &a2);

    // AMOR
    int resultado = (d1 + m1 + a1 + d2 + m2 + a2) * 7 % 101;
    printf("Amor: %d%% ", resultado);
    if (resultado < 20){
        puts("Pessimo dia para se apaixonar.");
    } else if (resultado <= 40){
        puts("Melhor manter o coracao <3 longe de perigo.");
    } else if (resultado < 70){
        puts("Se o papo e as ideias baterem, esta liberado pensar em algo.");
    } else if (resultado <= 80){
        puts("Saia com o coracao aberto, mas lembre, nem toda troca de olhar em onibus e sinal de romance.");
    } else{
        puts("Um dia deslumbrantemente lindo para amar. Ps: Cuidado com a intensidade.");
