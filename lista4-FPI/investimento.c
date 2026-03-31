// questão feita sem uso de ia, confundi um pouco as variaveis das coordenadas,
// mas foi tranquilo de resolver
/*LOGICA: recebo a entrada, elimino os espacos, mudo a matriz de acordo
com os movimentos, incrementando (++) nas casas que ele caminha,
após a matriz ser preenchida, procuro pela casa mais visitada */

#include <stdio.h>

void desenharCaminho(char vetor[20], int matrizMapa[4][4]){
    int x = 0, y = 0; // horizontal e vertical
    for (int i = 0; i < 20; i++){
        if (vetor[i] == 'c' && x > 0){
            x--;
            matrizMapa[x][y]++;
        }
        if (vetor[i] == 'b' && x < 3){
            x++;
            matrizMapa[x][y]++;
        }
        if (vetor[i] == 'e' && y > 0){
            y--;
            matrizMapa[x][y]++;
        }
        if (vetor[i] == 'd' && y < 3){
            y++;
            matrizMapa[x][y]++;
        }
    }
}

int main() {
	char caminhoEspaco[40] = "", caminho[20] = "";
	fgets(caminhoEspaco, sizeof(caminhoEspaco), stdin); // recebe a entrada com os espacos
	int j = 0;
    for (int i = 0; caminhoEspaco[i] != '\0'; i++) {
        // retirar os espacos
        if (caminhoEspaco[i] != ' ' && caminhoEspaco[i] != '\n' && caminhoEspaco[i] != '\t') {
            caminho[j] = caminhoEspaco[i];
            j++;
        }
    }
    caminho[j] = '\0'; // finaliza a nova string

    int matrizCidade[4][4] = {0};

    desenharCaminho(caminho, matrizCidade); // chama a função para desenhar o caminho

    int xLocal = 0, yLocal = 0; // coordenadas que vao ser impressas
    int numVisitas = 0; // variavel para guardar o valor da casa mais visitada
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (matrizCidade[i][j] > numVisitas){
                numVisitas = matrizCidade[i][j];
                xLocal = j;
                yLocal = i;
            }
        }
    }

    printf("Coordenada X:%d, Y:%d", xLocal, yLocal);

	return 0;
}
