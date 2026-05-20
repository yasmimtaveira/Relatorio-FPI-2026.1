/*
 uso do gemini para entender a questão e para pesquisa 
 (como formatação de saída e leitura de numeros em hexadecimal)
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct campoBit {
    unsigned int ID : 10;
    unsigned int status : 3;
    unsigned int bateria : 1;
    int temperatura : 12; 
    unsigned int controle : 6;

    // como declarei um int com sinal na temperatura, ele faz o complemento a 2 automaticamente
    // o restante dos membros é sem sinal (unsigned int)
};

typedef union {
    uint32_t dado : 32;
    struct campoBit campo;
} Protocolo;

int main(){
    // alocação de um vetor da union Protocolo que criei
    int capacidade = 2;
    Protocolo *vetor = malloc(capacidade * sizeof(Protocolo));
    
    if (vetor == NULL) exit(1); // verificação da alocação de memória

    int cont = 0; // contador de pacotes

    int x;
    while (scanf("%x", &x) == 1 && x != 0){ // lê a entrada em quanto não for 0 ou 0x0
        if (cont >= capacidade){ // memória insuficiente, usamos o realloc para aumentar a capacidade
            capacidade *= 2;
            Protocolo *temp = realloc(vetor, capacidade * sizeof(Protocolo));
            
            if (temp == NULL) exit(1); // verificação da alocação
            vetor = temp; // recebe a memoria realocada
        }
        Protocolo pacote; // inicializo minha union
        pacote.dado = (unsigned int)x; // coloco o dado bruto e o restante vai ser preenchido "automaticamente"

        vetor[cont++] = pacote; // adiciono o pacote no vetor e incremento o contador
    }

    // saida
    for (int i = 0; i < cont; i++){
        // coloco o 0x manualmente para printar o x minusculo como no exemplo
        // mas a formatação é usada para o restante do dado bruto ser printado em maiúsculo
        printf("Pacote [%d] - Dado Bruto: 0x%08X\n", i+1, vetor[i].dado);
        printf("ID do Sensor : %d\n", vetor[i].campo.ID);
        printf("Status : %d\n", vetor[i].campo.status);
        if (vetor[i].campo.bateria == 0){
            printf("%s", "Bateria Baixa: Nao\n");
        } else {
            printf("%s", "Bateria Baixa: SIM (ALERTA)\n");
        }
       printf("Temperatura : %d graus\n", vetor[i].campo.temperatura);
       printf("%s", "-------------------------------------------------\n");
    }

    free(vetor); // liberando a memória alocada
    return 0;
}