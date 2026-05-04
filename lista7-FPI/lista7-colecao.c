// questão tranquila para exercitar o conceito de struct, consegui resolver sem uso de IA

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char titulo[50];
    char genero[20];
    char estudio[30];
    char console[20];
    int nota;
    int anoLancamento;
} Colecao;

void printAno(Colecao jogos[], int n, int ano);
void printLetra(Colecao jogos[], int n, char letra);
void printStudio(Colecao jogos[], int n, char estudioEscolhido[]);
void printConsole(Colecao jogos[], int n, char consoleEscolhido[]);
void printColecao(Colecao jogos[], int n);


int main(){
    int n;
    scanf("%d", &n);
    // crio uma lista de jogos (com o tipo que criei com o struct)
    Colecao jogos[n];
    for (int i = 0; i < n; i++){
        scanf("%s", jogos[i].titulo);
        scanf("%s", jogos[i].genero);
        scanf("%s", jogos[i].estudio);
        scanf("%s", jogos[i].console);
        scanf("%d", &jogos[i].nota);
        scanf("%d", &jogos[i].anoLancamento);

        // saida de acordo com a nota de cada jogo cadastrado
        if (jogos[i].nota > 7){
            printf("%s\n", "AWESOME! Mais um GOTY pra minha coleção!");
        } else if (jogos[i].nota < 4){
            printf("%s\n", "Era melhor jogar mais um jogo de Mahjong.");
        }
    }

    char funcao[20];
    while (scanf("%s", funcao) != EOF){
        // CHAMAR A FUNCAO ESCOLHIDA
        if (strcmp(funcao, "printAno") == 0){
            int anoEscolhido;
            scanf("%d", &anoEscolhido);
            printAno(jogos, n, anoEscolhido);

        } else if (strcmp(funcao, "printLetra") == 0){
            char letraEscolhida;
            scanf(" %c", &letraEscolhida);
            printLetra(jogos, n, letraEscolhida);

        } else if (strcmp(funcao, "printStudio") == 0){
            char estudioEscolhido[30];
            scanf("%s", estudioEscolhido);
            printStudio(jogos, n, estudioEscolhido);

        } else if (strcmp(funcao, "printConsole") == 0){
            char consoleEscolhido[20];
            scanf("%s", consoleEscolhido);
            printConsole(jogos, n, consoleEscolhido);

        } else if (strcmp(funcao, "printColecao") == 0){
            printColecao(jogos, n);
        }
    }

    // fim do programa
    printf("Enjoei de jogar, agora vou ver TV.");
    return 0;
}

void printAno(Colecao jogos[], int n, int ano){
    int contador = 0;
    for (int i = 0; i < n; i++){
        if (jogos[i].anoLancamento == ano){
            printf("%s\n", jogos[i].titulo);
            contador++;
        }
    }
    if (contador > 0){
        printf("Tenho %d jogos || %d.\n", contador, ano);
    } else {
        printf("%s\n", "Nenhum jogo tem esse parâmetro Sr Sr Wilson.");
    }
}

void printLetra(Colecao jogos[], int n, char letra){
    int contador = 0;
    for (int i = 0; i < n; i++){
        if (jogos[i].titulo[0] == letra){
            printf("%s\n", jogos[i].titulo);
            contador++;
        }
    }
    if (contador > 0){
        printf("Tenho %d jogos || %c.\n", contador, letra);
    } else {
        printf("%s\n", "Nenhum jogo tem esse parâmetro Sr Sr Wilson.");
    }
}

void printStudio(Colecao jogos[], int n, char estudioEscolhido[]){
    int contador = 0;
    for (int i = 0; i < n; i++){
        if (strcmp(jogos[i].estudio, estudioEscolhido) == 0){
            printf("%s\n", jogos[i].titulo);
            contador++;
        }
    }
    if (contador > 0){
        printf("Tenho %d jogos || %s.\n", contador, estudioEscolhido);
    } else {
        printf("%s\n", "Nenhum jogo tem esse parâmetro Sr Sr Wilson.");
    }
}

void printConsole(Colecao jogos[], int n, char consoleEscolhido[]){
    int contador = 0;
    for (int i = 0; i < n; i++){
        if (strcmp(jogos[i].console, consoleEscolhido) == 0){
            printf("%s\n", jogos[i].titulo);
            contador++;
        }
    }
    if (contador > 0){
        printf("Tenho %d jogos || %s.\n", contador, consoleEscolhido);
    } else {
        printf("%s\n", "Nenhum jogo tem esse parâmetro Sr Sr Wilson.");
    }
}

void printColecao(Colecao jogos[], int n){
    for (int i = 0; i < n; i++){
        printf("%s %d\n", jogos[i].titulo, jogos[i].nota);
    }
}