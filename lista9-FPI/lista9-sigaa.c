#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct a{ // dados do aluno
	char mat[15];
	int pri;
	float cr;
	int L, R;
	int score;
}Aluno;

typedef struct no { // struct para o nó
	Aluno aluno;
	struct no *prox;
} No;

typedef struct { // struct da fila
	No *inicio;
	No *fim;
} Fila;

void initFila (Fila *fila){ //inicializar fila vazia
	fila->inicio = NULL;
	fila->fim = NULL;
}

int isVazia (Fila *fila){
	return (fila->inicio == NULL)? 1 : 0;
}

// remover do inicio
void dequeue (Fila *fila){
	No *removido = fila->inicio;

	if (isVazia(fila)){
		return;

	} else {
		fila->inicio = removido->prox;
		free(removido);
	}
}

void imprimirFila(Fila *fila){
	No *temp = fila->inicio;
	int cont = 1;
	while(temp){
		printf("%d. Matricula: %s\n", cont, temp->aluno.mat);
		temp = temp->prox;
        cont++;
	}
	free(temp);
}

// liberar a memoria dos nos d fila
void freeFila (Fila *fila){
    while(!isVazia(fila)){
        dequeue(fila);
    }
}

// inserir no fim
void enqueue (Fila *fila, Aluno a){
	No *novo = (No *)malloc(sizeof(No));
	novo->aluno = a;
	novo->prox = NULL;
	
	if (novo){
		if (isVazia(fila)){
			fila->inicio = novo;
			fila->fim = novo;

		} else {
			fila->fim->prox = novo;
			fila->fim = novo;
		}

	} else {
		printf("erro de alocacao");
		freeFila(fila);
		exit(1);
	}
}

int main(){
	
	char input[10];
	char nome[51];
	int vagas = 0;
	int tempo = 0;

	Fila fila_requisicoes;
	Fila fila_oficial;

	initFila(&fila_requisicoes);
	initFila(&fila_oficial); // filas inicializadas

	while(scanf("%s", input) != EOF){ // leitura do comando
		
		if (strcmp(input, "START") == 0){
			scanf("%s %d", nome, &vagas); // dados sobre a disciplina
			tempo = 1;

		} else if (strcmp(input, "ADD") == 0){
            // cria um aluno e guarda seus dados
			Aluno a;
			scanf("%s %d %f %d %d", a.mat, &a.pri, &a.cr, &a.L, &a.R);
			a.score = (int)round(a.cr * 100) / a.pri;
			enqueue(&fila_requisicoes, a); // adiciona o aluno nas requisicoes
			
		} else if (strcmp(input, "PROC") == 0){
			int qtd;
			scanf("%d", &qtd); // lê a quant que sera processada
			int processados = 0;

			while(processados < qtd && !isVazia(&fila_requisicoes)){ // processar a fila de requisicoes
				
				Aluno atual = fila_requisicoes.inicio->aluno; // comeca pelo aluno do inicio da fila
				if (tempo < atual.L) tempo = atual.L; // tempo ocioso

				if (tempo > atual.R){ // timeout
					printf("[TIMEOUT] mat=%s | Desconectado da fila.\n", atual.mat);
					
				} else { // nao teve timeout
					if (vagas > 0){ // tem vaga
						printf("[ALOCADO] mat=%s | score=%d | Processado no seg: %d\n", atual.mat, atual.score, tempo);
						enqueue(&fila_oficial, atual); // coloco aluno na fila oficial
						vagas--;
					} else { // nao tem vaga
						printf("[LOTADO] mat=%s | score=%d | Processado no seg: %d\n", atual.mat, atual.score, tempo);
					}
					processados++;
					tempo++; // atualiza os contadorws
				}
				dequeue(&fila_requisicoes); // retiro o aluno do inicio da fila de requisicoes
			}
			
		} else if (strcmp(input, "FIM") == 0){
			printf("--- LISTA OFICIAL: %s ---\n", nome);
			imprimirFila(&fila_oficial);
			freeFila(&fila_requisicoes);
			freeFila(&fila_oficial);
		}
	}

	return 0;
}