// codigo feito sem IA. O programa recebe a entrada e chama a funcao para modificar a matriz
// faco as verificacoes necessarias para adicionar os enfeites 

#include <stdio.h>

void enfeitaMatriz(size_t linhas, size_t colunas, char matriz[linhas][colunas]){
	for (int a = 0; a < linhas; a++){
		for (int b = 0; b < colunas; b++){
			if (matriz[a][b] == 'P'){ 
				
				if (a > 0){ 
					// adicionando os "+" nas linhas anteriores
					if (matriz[a-1][b] != 'P') matriz[a-1][b] = '+';
					if (b > 0){
						// adicionando "x" na diag esquerda superior
						if (matriz[a-1][b -1] == '-') matriz[a-1][b-1] = 'x';
					}
					if (b + 1 < colunas){
						// adicionando "x" na diag direita superior
						if (matriz[a-1][b+1] == '-') matriz[a-1][b+1] = 'x';
					}
				}
				if (b > 0){ 
					// adicionando os "+" nas colunas anteriores
					if (matriz[a][b-1] != 'P') matriz[a][b-1] = '+';
				}
				if (a + 1 < linhas){ 
					// adicionando os "+" nas linhas seguintes
					if (matriz[a+1][b] != 'P') matriz[a+1][b] = '+';
					if (b > 0){
						// adicionando "x" na diag esquerda inferior
						if (matriz[a+1][b-1] == '-') matriz[a+1][b-1] = 'x';
					}
					if (b + 1 < colunas){
						// adicionando "x" na diag direita inferior
						if (matriz[a+1][b+1] == '-') matriz[a+1][b+1] = 'x';
					}
				}
				if (b + 1 < colunas){ 
					// adicionando os "+" nas colunas anteriores
					if (matriz[a][b+1] != 'P') matriz[a][b+1] = '+';
				}
			}
		}
	}

	return;
}

int main() {

	size_t m, n;
	scanf("%d %d", &m, &n);

	char matrizPraca[m][n];
	matrizPraca[m][n] = "";

	for (int i = 0; i < m; i++){
		scanf("%s", matrizPraca[i]);
	}

	enfeitaMatriz(m, n, matrizPraca);

	 //Printar a matriz modificada
	for (int a = 0; a < m; a++){
		for (int b = 0; b < n; b++){
			printf("%c", matrizPraca[a][b]);
			if (b == n - 1) puts("");}}


	return 0;
}