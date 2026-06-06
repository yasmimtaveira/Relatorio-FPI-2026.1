// uso de IA para pesquisa e aprendizado da estrutura de dados fila
// alem de video aulas sobre o assunto, para encontrar jeitos e 
// explicações mais claras de como trabalhar com as filas

#include <string.h>
#include <stdlib.h>

typedef struct no{ // struct da tarefa pedida no enunciado
	int id;
	int pri;
	struct no* prox;
}Tarefa;

typedef struct { // struct da fila com os ponteiros de inicio e fim
	Tarefa *inicio;
	Tarefa *fim;
} Fila;

void inserir(Fila *fila, int id, int pri){
	Tarefa *nova = malloc(sizeof(Tarefa)); // aloco memoria para a nova tarefa

	if (nova){
		nova->id = id; // preenchi novo no
		nova->pri = pri;
        nova->prox = NULL; // novo no sempre aponta para NULL

		// inserir de fato
		if (fila->fim == NULL){ // fila vazia
			fila->inicio = nova;
			
		} else { // fila tem coisa já
			fila->fim->prox = nova; // adiciono no final da fila
		}
		fila->fim = nova; // atualizo o fim da fila

	} else {
		printf("erro de alocacao");
	}
}

void remover(Fila *fila){

	if (fila->inicio == NULL){ // FILA vazia
		printf("Fila vazia\n");

	} else {
		Tarefa *removido = fila->inicio; // guardo o inicio que sera removido
		fila->inicio = removido->prox; // atualizo pois o prox agora sera o inicio da fila
		printf("Removida: id=%d prioridade=%d\n", removido->id, removido->pri);
		free(removido); // libero a memoria
	}
}

void listar(Fila *fila){
	Tarefa *temp = fila->inicio; // ponteiro para varrer a fila
	if (temp == NULL){ // vazia
		printf("Fila vazia\n");

	} else { // imprimir tarefas
		while(temp != NULL){
			printf("id=%d prioridade=%d\n", temp->id, temp->pri);
			temp = temp->prox; // atualizo o ponteiro auxiliar
		}
	}
}

int main(){

	char comando = 'a';
	Fila f = {NULL, NULL};

	while(scanf("%c", &comando) && comando != 'F'){
		if (comando == 'I'){
			int id, pri;
			scanf("%d %d", &id, &pri);
			inserir(&f, id, pri);
		} else if (comando == 'R'){
			remover(&f);
		} else if (comando == 'L'){
			listar(&f);
		}
	}
    return 0;
}