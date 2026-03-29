// código feito se auxilio de IA
// lógica baseada nos 2 test cases fornecidos no enunciado da questão (juiz fora do ar)

#include <stdio.h>

void molharMatriz(int linha, int coluna, char matrix[linha][coluna]){
	for (int i = 0; i < linha; i++){
		for (int j = 0; j < coluna; j++){
			// adicionando as gotas ao redor das prateleiras
			if (matrix[i][j] == '#') {
				if (j > 0) {
					// adicionando a queda dagua para esquerda
					if (matrix[i][j-1] != '#') matrix[i][j-1] = 'o'; 
					// adicionando a queda dagua para diagonal esquerda
					if (i > 0 && matrix[i-1][j-1] != '#') matrix[i-1][j-1] = 'o'; 
				}
				// adicionando a queda dagua para cima
				if (i > 0 && matrix[i-1][j] != '#') matrix[i-1][j] = 'o'; 
	
				if (j + 1 < coluna) {
					// adicionando a queda dagua para diagonal direita
					if (i > 0 && matrix[i-1][j+1] != '#') matrix[i-1][j+1] = 'o'; 
					// adicionando a queda dagua para direita
					if (matrix[i][j+1] != '#') matrix[i][j+1] = 'o';
				}
			}
		}
	}
	for (int i = 0; i < linha; i++){
		for (int j = 0; j < coluna; j++){
			// adicionando a queda dagua para baixo quando encontra uma gota "livre"
			if (matrix[i][j] == 'o') {
				int l = i;
				while(l < linha && matrix[l][j] != '#'){
					matrix[l][j] = 'o'; 
					l++;
				}
			}
		}
	}
}

int main() {
	int m, n;
	scanf("%d %d", &m, &n); // dimensoes da matriz
	char matrix[m][n];
	matrix[m][n] = ""; // inicializando a matriz
	for (int i = 0; i < m; i++) {
		scanf("%s", matrix[i]); // recebendo as linhas
	}

	molharMatriz(m, n, matrix); // chamando a função

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			printf("%c", matrix[i][j]); // imprimindo a matriz
		}
		printf("\n");
	}
	return 0;
}
