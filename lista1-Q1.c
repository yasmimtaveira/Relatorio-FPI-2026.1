// uso de IA apenas para perguntas sobre sintaxe 

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
    }

    // SORTE
    if (a1 >= a2){
        resultado = ((d1+d2+m1+m2)*9 + (a1 - a2)) % 101;
    }else{
        resultado = ((d1+d2+m1+m2)*9 + (a2 - a1)) % 101;
    }
    
    printf("Sorte: %d%% ", resultado);
    if (resultado < 30){
        printf("%s","Nem jogue moedas pra cima hoje.");
    } else if (resultado <= 50){
        printf("%s","Melhor nao arriscar.");
    } else if (resultado < 80){
        printf("%s","Por sua conta em risco.");
    } else if (resultado <= 90){
        printf("%s","Hoje vale a pena arriscar.");
    } else{
        printf("%s","Nao tenha medo de virar cartas hoje.");
    }
    puts(" Sem tigrinho nem jogos de azar, por favor!");

    // TRABALHO
    resultado = ((a1+a2) - (d1+d2+m1+m2)*8) % 101;
    printf("Trabalho: %d%% ", resultado);
    if (resultado < 40){
        puts("Hoje nao sera um dia tao proveitoso, keep calm e faca o basico.");
    } else if (resultado <= 50){
        puts("Segura a emocao, nao xinga ninguem, nao esquece de beber agua.");
    } else if (resultado < 70){
        puts("Um dia proveitoso com certeza, leve sua simpatia consigo.");
    } else if (resultado <= 84){
        puts("Boas vibracoes hoje, chances podem estar ao seu redor.");
    } else{
        puts("Use do maximo de networking possível hoje, dia bom para negocios.");
    }

    // COR
    resultado = (a1*a1 + a2*a2 + m1*m1 + m2*m2 + d1*d1 + d2*d2) % 11;
  
    switch (resultado){
    case 0:
        puts("Cor: Cinza.");
        break;
    case 1:
        puts("Cor: Vermelho.");
        break;
    case 2:
        puts("Cor: Laranja.");
        break;
    case 3:
        puts("Cor: Amarelo.");
        break;
    case 4:
        puts("Cor: Verde.");
        break;
    case 5:
        puts("Cor: Azul.");
        break;
    case 6:
        puts("Cor: Roxo.");
        break;
    case 7:
        puts("Cor: Marrom.");
        break;
    case 8:
        puts("Cor: Rosa.");
        break;
    case 9:
        puts("Cor: Preto.");
        break;
    case 10:
        puts("Cor: Branco.");
        break;
    }

    return 0;

}
