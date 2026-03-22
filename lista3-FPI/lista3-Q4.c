/*código feito com auxilio do Gemini para usar melhor as funções da biblioteca e 
melhorar o fluxo, evitando e corrigindo erros */ 

#include <stdio.h>
#include <string.h>

int main() {
    int rCasos;
    int flashsTestados; // entradas
    char string[60]; //array para os estados da string atual
    char stringFinal[70000] = ""; // array para a luz gigante

    int tamanho; // tamanho da string atual
    int tamanhoTotal; // tamanho da luz gigante
    char ultimoEstado; // ultimo estado da luz gigante
    char ornamento; // simbolos que serão adicionados

    if (scanf("%d", &rCasos) != 1) return 0;

    for (int j = 0; j < rCasos; j++){
        scanf("%s %d", string, &flashsTestados);
        tamanho = strlen(string);

        // transformações da string a cada clock
        for (int k = 0; k < flashsTestados; k++){
            for (int i = 0; i < tamanho; i++){
                if (string[i] == 'X'){ // desligado -> ligado
                    string[i] = 'O';
                    break; // como ligou, o proximo não sera alterado
                } else {
                    string[i] = 'X';
                    // agora, como desligou, o proximo sera trocado!
                }
            }
        }
        // print da configuração final dos leds dessa string
        printf("%s\n", string); 

        // LUZ GIGANTE
        if (j == 0){  // looping na 1ª iteração
            // limpo a stringFinal e anexo as luzes após as tranformações
            strcpy(stringFinal, string); 

        } else { // demais iteracoes
            tamanhoTotal = strlen(stringFinal);
            ultimoEstado = stringFinal[tamanhoTotal - 1];
            if (tamanhoTotal % 2 == 0){ // par
                if (ultimoEstado == string[0]) ornamento = '@';
                else ornamento = '$';
            } else { // impar
                if (ultimoEstado == string[0]) ornamento = '#';
                else ornamento = '%';
            }
            // anexando o ornamento e a ultima string a stringTotal (luz gigante)
            int fim = strlen(stringFinal);
            stringFinal[fim] = ornamento;
            stringFinal[fim+1] = '\0';
            strcat(stringFinal, string);
        }
    }
    //print do final
    printf("%s", stringFinal);

	return 0;
}
