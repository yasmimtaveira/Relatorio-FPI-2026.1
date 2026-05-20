#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct das informações presentes nos arquivos
typedef struct {
    float sepal_length;
    float sepal_width;
    float petal_length;
    float petal_width;
    char species[30];
} IrisDados;

char* DefinirEspecieModa(int setosa, int versicolor, int virginica);

int main(){
    int qtd_arq;
    scanf("%d", &qtd_arq);  

    // loop for para a leitura dos arquivos
    for (int i = 0; i < qtd_arq; i++){

        //sprintf para gerar dinamicamente os nomes dos arquivos
        char nome_arquivo[20];
        sprintf(nome_arquivo, "iris%d.csv", i+1);
        
        // abrir o arquivo
        FILE *arquivo = fopen(nome_arquivo, "r+");
        if (arquivo == NULL) { // verificar se foi bem-sucedido
            printf("Erro ao abrir o arquivo\n");
            exit(1);
        }

        int capacidade = 3; // alocando memoria para ler as linhas do arquivo
        IrisDados *dados = malloc(capacidade * sizeof(IrisDados));
        int total_linhas = 0;

        if (dados == NULL){ // verificação da alocação
            printf("Erro na alocação\n");
            fclose(arquivo);
            exit(1);
        }

        // leitura do cabeçalho antes de entrar no looping
        char cabecalho[100];
        fscanf(arquivo, "%s", cabecalho);

        // print no terminal
        printf("--- Conteudo do arquivo: %s ---\n", nome_arquivo);
        printf("\n%s\n", cabecalho);

        // contadores
        float total_sl = 0, total_sw = 0, total_pl = 0, total_pw = 0;
        int setosa = 0, versicolor = 0, virginica = 0;
        // variaveis auxiliares para a leitura das linhas do arquivo
        float sl, sw, pl, pw; 
        char especie[30];

        // ler as linhas do arquivo 
        while (fscanf(arquivo, " %f,%f,%f,%f,%[^ \n\r]", &sl, &sw, &pl, &pw, especie) == 5){

            // verificar se precisa de realloc                                                    
            if (total_linhas >= capacidade){
                capacidade *= 2;
                IrisDados *temp = realloc(dados, capacidade * sizeof(IrisDados));
                if (temp == NULL) {
                    free(dados);
                    fclose(arquivo);
                    exit(1);
                }
                dados = temp;
            }
            dados[total_linhas].sepal_length = sl;
            dados[total_linhas].sepal_width = sw;
            dados[total_linhas].petal_length = pl;
            dados[total_linhas].petal_width = pw;
            strcpy(dados[total_linhas].species, especie);

            //Extrair os dados de cada arquivo.
            total_sl += dados[total_linhas].sepal_length;
            total_sw += dados[total_linhas].sepal_width;
            total_pl += dados[total_linhas].petal_length;
            total_pw += dados[total_linhas].petal_width;

            if (!strcmp(dados[total_linhas].species, "Iris-setosa")) setosa++;
            if (!strcmp(dados[total_linhas].species, "Iris-versicolor")) versicolor++;
            if (!strcmp(dados[total_linhas].species, "Iris-virginica")) virginica++;

            // exibir todo conteudo do arquivo no terminal (com 2 casas decimais)
            printf("%.2f,%.2f,%.2f,%.2f,%s\n",  dados[total_linhas].sepal_length,
                                                dados[total_linhas].sepal_width,
                                                dados[total_linhas].petal_length,
                                                dados[total_linhas].petal_width,
                                                dados[total_linhas].species);
            total_linhas++; // incremento o contador
        }
        puts(" "); // quebra de linha pra deixar o print no terminal mais organizado

        // Calcular a média de cada dimensão das flores.
        float media_sl = total_sl / total_linhas; 
        float media_sw = total_sw / total_linhas; 
        float media_pl = total_pl / total_linhas;
        float media_pw = total_pw / total_linhas;

        // Determinar a espécie com maior frequência (moda).
        char *especie_moda = DefinirEspecieModa(setosa, versicolor, virginica);
        
        //Gravar os resultados ao final do próprio arquivo original
        fseek(arquivo, 0, SEEK_END); // coloca o cursor no fim do arquivo
        fprintf(arquivo, "\n\nMédias: %.2f, %.2f, %.2f, %.2f\n", media_sl, media_sw, media_pl, media_pw);
        fprintf(arquivo, "Moda: %s", especie_moda);

        // liberar memoria e fechar arquivo
        free(dados);
        fclose(arquivo);
    }
    return 0;
}

char* DefinirEspecieModa(int setosa, int versicolor, int virginica){
    
    int num_moda = 0;
    if (setosa > num_moda) num_moda = setosa;
    if (versicolor > num_moda) num_moda = versicolor;
    if (virginica > num_moda) num_moda = virginica;

    // ordem alfabetica: setosa, vericolor, virginica
    // o if else nessa ordem já garante os empates
    if (num_moda == setosa){ 
        return "Iris-setosa";
    
    } else if (num_moda == versicolor){
        return "Iris-versicolor";
    
    } else {
        return "Iris-virginica";
    }
}
