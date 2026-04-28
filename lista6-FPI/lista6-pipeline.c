// codigo feito com ajuda do Gemini para entender melhor os parâmetros de cada função
// e o uso de vetor de ponteiro de função
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calibracao(int valor) {
    return valor + 5;
}

int saturacao(int valor) {
    if (valor > 80) return 80;
    return valor;
}

int amplificador(int valor) {
    return valor * 2;
}

void modificar(int **matriz, int l, int c, int (**pipeline)(int), int n_filtros){
    for (int i = 0; i < l; i++) { // chama a funcao para cada elemento da matriz
        for (int j = 0; j < c; j++) {
            for (int f = 0; f < n_filtros; f++) { // chama todos os filtros da lista
                matriz[i][j] = pipeline[f](matriz[i][j]); // ponteiro que aponta p função certa
            }
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    // Alocação dinâmica da matriz
    int **matriz = (int **)malloc(n * sizeof(int *));

    if (matriz == NULL) exit(1);

    for (int i = 0; i < n; i++) {
        matriz[i] = (int *)malloc(m * sizeof(int));
        if (matriz[i] == NULL){
            for (int k = 0; k < i; k++){
                free(matriz[k]); // libera a memoria alocada até o momento
                exit(1);
            }
        }
        for (int j = 0; j < m; j++) {
            scanf("%d", &matriz[i][j]);
        }
    }

    // vetor (lista) de ponteiros para as funcoes (filtros)
    int (*idFiltros[4])(int) = {NULL, calibracao, saturacao, amplificador};

    int comando;
    while (scanf("%d", &comando) && comando != 0){
        int (**pipeline_atual)(int) = NULL; // criando o ponteiro para ponteiro de função
        int k = 0; // contador de filtros

        if (comando >= 1 && comando <= 3) {
            k = 1;
            // alocando memoria para apenas um ponteiro de ponteiro de funcao
            pipeline_atual = (int (**)(int))malloc(sizeof(int (*)(int))); 
            // preenchendo o vetor (lista) de ponteiros com o ponteiro da funcao selecionada
            pipeline_atual[0] = idFiltros[comando]; 
        } else if (comando == 4) {
            scanf("%d", &k); // usuario escolhe quantos filtros aplicar
            
            // alocando memoria suficiente para os filtrsp
            pipeline_atual = (int (**)(int))malloc(k * sizeof(int (*)(int)));
            for (int i = 0; i < k; i++) { // recebe os comandos
                int filtroEscolido;
                scanf("%d", &filtroEscolido);
                pipeline_atual[i] = idFiltros[filtroEscolido]; // preenchendo o vetor de ponteiros com as funcoes na ordem correta
            }
        }

        if (pipeline_atual != NULL) {
            modificar(matriz, n, m, pipeline_atual, k); // chama a funcao de modificacao passando o pipeline atual
            free(pipeline_atual); // liberando a memoria alocada para o pipeline
        }
    }

    // saida dos dados

    int maior = matriz[0][0];
    int linhaMaior = 0, colunaMaior = 0;

    printf("Matriz processada:\n");
    for (int i = 0; i < n; i++){
        for (int j = 0; j <m; j++){
            printf("%d ", matriz[i][j]);

            if (matriz[i][j] > maior) { // escolhendo o maior
                maior = matriz[i][j];
                linhaMaior = i;
                colunaMaior = j;
            }
        }
        printf("\n");
    }

    // saida do sensor critico
    printf("\nSensor critico: %d\n", maior);
    printf("Posicao: (%d,%d)\n", linhaMaior, colunaMaior);

    // liberar memoria
    for (int i = 0; i < n; i++) {
        free(matriz[i]);
    }
    free(matriz);


    return 0;
}
