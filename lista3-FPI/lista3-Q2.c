/*código feito sem uso de IA
lÓGICA: crio uma array para armazenar quantas latas cada cliente comprou,
faço um looping para somar os elementos da lista e quando chego a 50
guardo a posição do ganhador (e quantas latas comprou), com ela consigo calcular o horario*/

#include <stdio.h>

int main() {
    int n, x, y; // clientes, x, clientes que compraram + que 1
    scanf("%d %d %d", &n, &x, &y);
    int listaClientes[n];
    int latasVendidas = 0, posicao = 0; //latas, n° do cliente
    int posicaoGanhador = 0, mGanhador = 0; // n° do ganhador, quantas latas comprou
    
    for (int i = 0; i < n; i++){ // para varrer a array
        if (x > 0 && ((i+1) % x == 0)){
            listaClientes[i] = 1;
        } else {
            listaClientes[i] = 0;
        }
    }
    for (int i = 0; i < y; i++){ // entradas
        int wh, wm, z; // hora, minuto, n° de latas compradas
        scanf("%d:%d %d", &wh, &wm, &z);
        posicao = ((wh * 60 + wm) - 7*60)/3; // calculo do numero do cliente através da hora
        listaClientes[posicao-1] = z; // preenche a array
        //printf("%d %d\n", posicao, listaClientes[posicao]);
    }

    for (int i = 0; i < n; i++){ // varrer a array para a contagem
        latasVendidas += listaClientes[i];
        if (latasVendidas >= 50 && posicaoGanhador == 0){
            posicaoGanhador = i + 1;
            mGanhador = listaClientes[i];
        }
    }

    //output
    int hora = 7 + (3*posicaoGanhador)/60;
    int min = 3*posicaoGanhador % 60;
    if (latasVendidas < 50){
        if (latasVendidas == 49){ //singular
            printf("%s", "Ainda nao foram vendidas latas suficientes. Falta 1 lata.");
        } else { //plural
            printf("Ainda nao foram vendidas latas suficientes. Faltam %d latas.", 50 - latasVendidas);
        }
    }else {
        printf("Quem levou a cesta basica foi o %d* cliente atendido por coragem, as ", posicaoGanhador);
        if (hora < 10){
            printf("0%d:", hora);
        } else { 
            printf("%d:", hora);
        }
        if (min < 10){
            printf("0%d. ", min);
        } else {
            printf("%d. ", min);
        }
        if (mGanhador == 1){ //singular
            printf("%s", "Que comprou 1 lata.");
        } else { // plural
            printf("Que comprou %d latas.", mGanhador);
        }
    }

	return 0;
}