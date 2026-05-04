// uso de IA para aprender sobre as funções das bibliotecas usadas

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
    char nome[50];
    int populacao;
    int periculosidade;
    char funcao[20];
} Informacoes;

void formatarSaida(Informacoes *cidadela);

int main(){
    char mensagem[201];
    Informacoes cidadelas[30];
    int i = 0; // indice do numero de cidadelas cadastradas
    int chave = -1; // para indicar que ainda nao encontrei nenhuma chave

    while(scanf(" %[^\n]", mensagem) != EOF){
        int idxNome = 0; // indice dos caracteres do nome da cidadela
        int idxFuncao = 0; // indice dos caracteres da funcao da cidadela
        cidadelas[i].nome[0] = '\0'; 
        cidadelas[i].funcao[0] = '\0'; 
        cidadelas[i].populacao = 0; // inicializo a populacao da cidadela como 0
        cidadelas[i].periculosidade = 0; // inicializo a periculosidade da cidadela como 0

        // checar se é uma mensagem especial
        char *ptrExclamacao = strchr(mensagem, '!');

        if (ptrExclamacao != NULL){ // encontrei um '!' na mensagem, entao é uma mensagem especial
            // extrair a chave da mensagem especial
            chave = 0; // inicializo a chave como 0
            for (int caractere = 0; caractere < strlen(mensagem); caractere++){
                if (isdigit(mensagem[caractere])){
                    // caracter é um numero, entao é parte da chave
                    int digito = mensagem[caractere] - '0'; // converto o caracter para o valor inteiro correspondente
                    chave = (chave * 10) + digito;
                }
            }
            i--; // decremento pois essa mensagem nao informa sobre nenhuma cidadela

        } else { // mensagem normal
            // preencher as informacoes da cidadela[i]

            for (int letra = 0; letra < strlen(mensagem); letra++){

                // preenchendo o nome
                if (isupper(mensagem[letra])){
                    //letra maiuscula, entao é parte do nome da cidadela
                    cidadelas[i].nome[idxNome] = mensagem[letra];
                    idxNome++;
                }

                // preenchendo a populacao
                if (isdigit(mensagem[letra])){
                    // caracter é um numero, entao é parte da populacao
                    int digito = mensagem[letra] - '0'; // converto o caracter para o valor inteiro correspondente
                    cidadelas[i].populacao = (cidadelas[i].populacao * 10) + digito;
                }

                // preenchendo a periculosidade
                if (mensagem[letra] == '*'){
                    cidadelas[i].periculosidade++;
                }

                // preenchendo a funcao
                if (letra - 1 >= 0 && mensagem[letra - 1] == ' ' && letra - 2 >= 0 && mensagem[letra - 2] == ' '){
                    // encontrei um caractere que os dois anteriores sao espaços
                    cidadelas[i].funcao[idxFuncao] = mensagem[letra];
                    idxFuncao++;
                }
            }
            // finalizo as strings com '\0'
            cidadelas[i].nome[idxNome] = '\0';
            cidadelas[i].funcao[idxFuncao] = '\0';
        }
        // incremento o indice para a proxima cidadela
        i++;
    }

    // ordenar as cidadelas em ordem decrescente (habitantes, periculosidade, lexigráfica)
    // bubble sort
    for (int a = 0; a < i; a++){
        for (int b = 0; b < i - a - 1; b++){
            if (cidadelas[b].populacao < cidadelas[b+1].populacao){
                // trocar cidadela b com a cidadela b+1
                Informacoes temp = cidadelas[b];
                cidadelas[b] = cidadelas[b+1];
                cidadelas[b+1] = temp;
            
            } else if (cidadelas[b].populacao == cidadelas[b+1].populacao){
                // desempate pela periculosidade
                if (cidadelas[b].periculosidade < cidadelas[b+1].periculosidade){
                    // trocar cidadela b com a cidadela b+1
                    Informacoes temp = cidadelas[b];
                    cidadelas[b] = cidadelas[b+1];
                    cidadelas[b+1] = temp;

                } else if (cidadelas[b].periculosidade == cidadelas[b+1].periculosidade){
                    // desempate lexicográfico
                    if (strcmp(cidadelas[b].nome, cidadelas[b+1].nome) > 0){
                        // trocar cidadela b com a cidadela b+1
                        Informacoes temp = cidadelas[b];
                        cidadelas[b] = cidadelas[b+1];
                        cidadelas[b+1] = temp;
                    }
                }
            }
        }
    }

    if (chave != -1){ // chave recebida, Gingrey encontrada
        chave--; // chave vem em formato 1-based, entao decremento para usar como indice 0-based

        formatarSaida(&cidadelas[chave]);

        printf("Gingrey foi encontrada em %s, uma cidadela com %d mil habitantes cuja função é %s e periculosidade ", cidadelas[chave].nome, cidadelas[chave].populacao, cidadelas[chave].funcao);
        for (int k = 0; k < cidadelas[chave].periculosidade; k++){
            printf("*");
        }
        printf(".");

        if (cidadelas[chave].populacao >= 1000 && cidadelas[chave].periculosidade > 3){
            printf("%s", " Talvez seja melhor desistir...");

        } else {
            if (cidadelas[chave].populacao >= 1000){
                printf("%s", " Um lugar denso, vai ser difícil achar ela.");
            }
            if (cidadelas[chave].periculosidade > 3){
                printf("%s", " Vai ser complicado entrar lá.");
            }
        }
        
    } else {
        printf("%s\n", "Gingrey ainda não foi achada, vamos esperar mais um pouco.");
    }

    return 0;
}

void formatarSaida(Informacoes *cidadela){
    // colocar o nome e a funcao da cidadela no formato pedido
    for (int letra = 1; letra < strlen(cidadela->nome); letra++){
        // como o nome esta todo maiusculo, basta colocar em minusculo a partir da segunda letra
        cidadela->nome[letra] = tolower(cidadela->nome[letra]);
    }
    cidadela->funcao[0] = toupper(cidadela->funcao[0]); // primeira letra da funcao em maiusculo
    for (int letra = 1; letra < strlen(cidadela->funcao); letra++){
        cidadela->funcao[letra] = tolower(cidadela->funcao[letra]);
    }
}