/* código feito com ajuda do Claude para entender o fluxo e resolver problemas 
na comparação dos canais
*/
#include <stdio.h>

int main(){
    int X, N;
    int distMin = -1, melhorCanal = -1, minutoMin = -1, melhorTermo = -1; // variaveis para as informações do melhor canal encontrado
    scanf("%d %d", &X, &N);

    for (int c = 1; c <= N; c++) {
        int f1, f2;
        scanf("%d %d", &f1, &f2);
        int min, termo, distCanal; // variaveis locais para as infomações do canal analisado

        int d = f1 - X;
        if (d < 0) d = -d;
        min = 1;
        termo = f1;
        distCanal = d; // inicializando a distancia minima do canal

        d = f2 - X;
        if (d < 0) d = -d;
        if (d < distCanal) { // testando para f2
            min = 2;
            termo = f2;
            distCanal = d;  
        } 

        long long n1 = f1, n2 = f2;
        int indice = 3;
        while (1){ // testando os termos dp canal
            long long prox = n1 + n2;
            d = prox - X;
            if (d < 0) d = -d;
            if (d < distCanal) { // para definir o melhor termo do canal
                min = indice;
                termo = prox;
                distCanal = d;  
            }
            if (prox > X && d >= distMin) break; // a distancia só cresce dps disso
            n1 = n2;
            n2 = prox;
            indice++; //atualiza as variaveis
        }

        //desempate entre canais
        if (melhorCanal == -1 || distCanal < distMin || (distCanal == distMin)){
            melhorCanal = c;
            minutoMin = min;
            melhorTermo = termo;
            distMin = distCanal;
        }
    
    
    
    }
    //soma dos algarismos do melhor termo
    long long t = melhorTermo;
    int soma = 0;
    if (t < 0) t = -t;
    if (t == 0){
        soma = 0;
    } else {
        while (t > 0) {
            soma += t % 10;
            t /= 10;
        }
    }

    // output
    if (soma > 10) {
        printf("Xupenio, para ir ao lulupalooza vc deve entrar no canal %d e sera chamado mais ou menos no minuto %d e com o VIP garantido!!!\n", melhorCanal, minutoMin);
    } else {
        printf("Xupenio, para ir ao lulupalooza vc deve entrar no canal %d e sera chamado mais ou menos no minuto %d, mas o ingresso VIP não vai rolar :(\n", melhorCanal, minutoMin);
    }

    return 0; 
}