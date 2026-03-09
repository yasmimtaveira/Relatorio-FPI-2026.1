// código escrito sem o uso de inteligência artificial
// acredito que ficou repetitivo pelo o uso exclusivo da função main

#include <stdio.h>

int main(){

    int x, y, c;
    scanf("%d %d %d", &x, &y, &c);

    int Kx, Ky, conseguiu = 0;
    int comecouEmX; //variavel para saber se o primeiro passo foi em x ou y
    int atual; //quadrante atual
    
    //definindo o quadrante atual e o destino
    if (x>0){
        if (y>0){
            //1º quadrante, quer ir ao terceiro
            atual = 1; 
        } else{
            //4º quadrante, quer ir ao segundo
            atual = 4;
        }

    } else if (x<0){
        if (y>0){
            //2º quadrante, quer ir ao quarto
            atual = 2;
        } else{
            //3º quadrante, quer ir ao primeiro
            atual = 3;
        }
    }

    //calculo dos passos
    if (c == 1){
        if (atual == 2){
            comecouEmX = 0;
            Kx = -x + 1;
            Ky = y + 1;
            conseguiu = 1;

        } else if (atual == 4){
            comecouEmX = 1;
            Kx = x + 1;
            Ky = -y + 1;
            conseguiu = 1;

        } else { //caminhada invalida
            conseguiu = 0;
        }
    } else if (c == 2){
        if (atual == 1){
            comecouEmX = 0;
            Kx = x + 1;
            Ky = y + 1;
            conseguiu = 1;

        } else if (atual == 3){
            comecouEmX = 1;
            Kx = -x + 1;
            Ky = -y + 1;
            conseguiu = 1;

        } else {
            conseguiu = 0; //caminhada invalida
        }
    } else if (c == 3){
        if (atual == 2){
            comecouEmX = 1;
            Kx = -x + 1;
            Ky = y + 1;
            conseguiu = 1;

        } else if (atual == 4){
            comecouEmX = 0;
            Kx = x + 1;
            Ky = -y + 1;
            conseguiu = 1;

        } else {
            conseguiu = 0; //caminhada invalida
        }
    } else if (c == 4){
        if (atual == 1){
            comecouEmX = 1;
            Kx = x + 1;
            Ky = y + 1;
            conseguiu = 1;

        } else if (atual == 3){
            comecouEmX = 0;
            Kx = -x + 1;
            Ky = -y + 1;
            conseguiu = 1;

        } else {
            conseguiu = 0; //caminhada invalida
        }
    }
     
    if (conseguiu == 0){
        puts("caminhada invalida");
    } else{
        if (comecouEmX == 1){
            printf("%d passos em x e %d passos em y", Kx, Ky);
        } else {
            printf("%d passos em y e %d passos em x", Ky, Kx);
        }
    }
    return 0;
}