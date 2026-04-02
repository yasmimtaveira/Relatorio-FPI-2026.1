/*código feito com uso de IA (Claude e Gemini) para entender o algoritmo de busca em largura (BFS),
encontrei dificuldades nessa questao para entender o funcionamento, principalmente das filas
mas acredito que foi um ótimo aprendizado conhecer esse algoritmo tao eficiente! */ 

#include <stdio.h>
#include <string.h>
#define MAX 105

void BFS(int linhas, int colunas, char mapa[MAX][MAX], int dist[MAX][MAX]) {
	// "Fila" com arrays para algoritmo de busca em largura (BFS)!!
	// para guardar as coordenadas das posicoes
    int filaLinha[MAX * MAX], filaColuna[MAX * MAX];
    int inicio = 0, fim = 0;
    
    // varre a matriz pra achar a origem e coloca na fila
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (mapa[i][j] == 'o') {
                filaLinha[fim] = i;
                filaColuna[fim] = j;
                fim++;
                dist[i][j] = 0;
            }
        }
    }
    
    // Direções: cima, baixo, esquerda, direita
	// usaremos para caminhar pela matriz
    int direcaoLinha[4] = {-1, 1, 0, 0};
    int direcaoColuna[4] = {0, 0, -1, 1};
    
    // BFS
	// enquanto tiver elementos na fila, ou seja,
	// enquanto tiver posicoes para explorar
    while (inicio < fim) { 
        int linhaAtual = filaLinha[inicio];
        int colunaAtual = filaColuna[inicio];
        inicio++;
        
        for (int d = 0; d < 4; d++) { // moovimentos dentro da matriz
			// ex: quando d=0, a coordenada da linha é -1 (cima) e a coluna é 0 (mesma coluna)
            int novaLinha = linhaAtual + direcaoLinha[d];
            int novaColuna = colunaAtual + direcaoColuna[d];
            
            // Checa limites (se saiu da matriz)
            if (novaLinha < 0 || novaLinha >= linhas) continue;
            if (novaColuna < 0 || novaColuna >= colunas) continue;
            
            // Checa se já foi visitado ou é parede
            if (dist[novaLinha][novaColuna] != -1) continue;
            if (mapa[novaLinha][novaColuna] == '#') continue;
            
            // Atualiza distância e coloca na fila
            dist[novaLinha][novaColuna] = dist[linhaAtual][colunaAtual] + 1;
            filaLinha[fim] = novaLinha;
            filaColuna[fim] = novaColuna;
            fim++;
        }
    }
}

int main() {
    int linhasMatriz, colunasMatriz;
    char mapaMatriz[MAX][MAX];
    int dist[MAX][MAX];
    
    // entrada: tamanho da matriz
    scanf("%dx%d", &linhasMatriz, &colunasMatriz);
    
    // leitura da Matriz
    for (int i = 0; i < linhasMatriz; i++) {
        scanf("%s", mapaMatriz[i]);
    }
    
    // Inicializa distâncias com -1 (para indicar que não foi visitado)
    for (int i = 0; i < linhasMatriz; i++)
        for (int j = 0; j < colunasMatriz; j++)
            dist[i][j] = -1;

	// chamo a funcao para fazer a busca preenchendo a matriz de distancias		
	BFS(linhasMatriz, colunasMatriz, mapaMatriz, dist);
    
    // Acha a saída no mapaMatriz e verifica distância na matriz de distâncias
    int encontrou = 0;
    for (int i = 0; i < linhasMatriz; i++) {
        for (int j = 0; j < colunasMatriz; j++) {
            if (mapaMatriz[i][j] == 'd' && dist[i][j] != -1) {
                printf("Apos correr %d metros e quase desistir por causa da distância, Rebeka conseguiu escapar!\n", dist[i][j]);
                encontrou = 1;
            }
        }
    }
    
    if (!encontrou) { // nao encontrou a saida
        printf("Poxa... Parece que nao foi dessa vez que Rebeka conseguiu fugir\n");
    }
    
    return 0;
}
