#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int codigo;
    char nome[30];
    int qtd_estoque;
    float preco;
} Produtos;

typedef struct {
    int codigo;
    char tipo; // E = entrada, S = saída
    int qtd_movimento;
} Movimentos;

typedef struct {
    int codigo;
    char tipo; // E = entrada, S = saída
    int qtd_movimento;
    char inconsistencia[30];
} Inconsist;

int ja_processado(int lista_processados[], int cod_produto, int tot_prod);

int main(){
    
    // ler produtos.txt e movimentos.txt
    FILE* arq_prod = fopen("produtos.txt", "r");

    if (arq_prod == NULL){
        printf("Erro ao abrir arquivo");
        exit(1);
    }

    FILE* arq_mov = fopen("movimentos.txt", "r");

    if (arq_mov == NULL){
        printf("Erro ao abrir arquivo");
        fclose(arq_prod);
        exit(1);
    }

    // vetor de structs Produtos para armazenar os dados de produtos.txt
    int capacidade_prod = 3;
    int total_produtos = 0;
    Produtos *vetor_prod = (Produtos *)malloc(capacidade_prod * sizeof(Produtos));
    if (vetor_prod == NULL){
        fclose(arq_prod);
        fclose(arq_mov);
        exit(1);
    }

    // preencher o vetor de Produtos
    int cod, quant; // variaveis auxuliares
    float preco;
    char nome[30];
    while(fscanf(arq_prod," %d %s %d %f", &cod, nome, &quant, &preco) == 4){
        // verifica se precisa realocar memoria
        if (total_produtos >= capacidade_prod){
            capacidade_prod *= 2;
            Produtos *temp = (Produtos *)realloc(vetor_prod, capacidade_prod * sizeof(Produtos));
            if (temp == NULL){ // ERRO DE ALOCAÇÃO
                fclose(arq_prod);
                fclose(arq_mov);
                free(vetor_prod);
                exit(1);
            }
            vetor_prod = temp;
        }

        // cadastrando os dados
        Produtos produto;
        produto.codigo = cod;
        produto.qtd_estoque = quant;
        produto.preco = preco;
        strcpy(produto.nome, nome);

        // adicionando no vetor
        vetor_prod[total_produtos] = produto;
        total_produtos++;
    }
    
    // vetor de structs Movimentos para armazenar os dados de movimentos.txt
    int capacidade_mov = 3;
    int total_mov = 0;
    Movimentos *vetor_mov = (Movimentos *)malloc(capacidade_mov * sizeof(Movimentos));
    if (vetor_mov == NULL){
        fclose(arq_prod);
        fclose(arq_mov);
        free(vetor_prod);
        exit(1);
    }

    // preencher o vetor de movimentos
    char tipo;
    while(fscanf(arq_mov," %d %c %d", &cod, &tipo, &quant) == 3){
        // verifica se precisa realocar memoria
        if (total_mov >= capacidade_mov){
            capacidade_mov *= 2;
            Movimentos *temp = (Movimentos *)realloc(vetor_mov, capacidade_mov * sizeof(Movimentos));
            if (temp == NULL){ // ERRO DE ALOCAÇÃO
                fclose(arq_prod);
                fclose(arq_mov);
                free(vetor_prod);
                free(vetor_mov);
                exit(1);
            }
            vetor_mov = temp;
        }

        // cadastrando os dados
        Movimentos movimento;
        movimento.codigo = cod;
        movimento.qtd_movimento = quant;
        movimento.tipo = tipo;

        // adicionando no vetor
        vetor_mov[total_mov] = movimento;
        total_mov++;
    }

    //  gerar estoque_atualizado.txt e relatorio.txt.
    FILE* arq_atualizado = fopen("estoque_atualizado.txt", "w");
    if (arq_atualizado == NULL){
        printf("Erro ao gerar arquivo");
        fclose(arq_prod);
        fclose(arq_mov);
        free(vetor_prod);
        free(vetor_mov);
        exit(1);
    }
    FILE* arq_relatorio = fopen("relatorio.txt", "w");
    if (arq_relatorio == NULL){
        printf("Erro ao gerar arquivo");
        fclose(arq_prod);
        fclose(arq_mov);
        fclose(arq_atualizado);
        free(vetor_prod);
        free(vetor_mov);
        exit(1);
    }

    // PROCESSANDO OS MOVIMENTOS PARA PREENCHER OS ARQUIVOS NOVOS
    // contadores
    int prod_processados = 0, mov_aplicados = 0, saidas_recusadas = 0, sem_cadastro = 0;
    int lista_processados[total_produtos];
    for (int c = 0; c < total_produtos; c++){ // lista dos cod dos prod processados preenchida com 0
        lista_processados[c] = 0;
    }
    // vetor para produtos com estoque baixo
    int baixo = 0; 
    int capac_est_baixo = 5; //contador do estoque baixo
    Produtos *est_baixo = malloc(capac_est_baixo * sizeof(Produtos));
    if (est_baixo == NULL){ // erro de alocaçao
        fclose(arq_prod);
        fclose(arq_mov);
        fclose(arq_atualizado);
        fclose(arq_relatorio);
        free(vetor_prod);
        free(vetor_mov);
        exit(1);
    }

    // vetor para movimentos inconsistentes
    int total_inc = 0;
    int capac_inconsist = 5;
    Inconsist *inconsist = malloc(capac_inconsist * sizeof(Inconsist));
    if (inconsist == NULL){ // erro de alocaçao
        fclose(arq_prod);
        fclose(arq_mov);
        fclose(arq_atualizado);
        fclose(arq_relatorio);
        free(vetor_prod);
        free(vetor_mov);
        free(est_baixo);
        exit(1);
    }
    
    Produtos est_atual[total_produtos]; // estoque atualizado
    for (int a = 0; a < total_produtos; a++){
        est_atual[a] = vetor_prod[a]; // copia do vetor_prod
    }

    /* looping para varrer os produtos e movimentos, apicando os movimentos
    consistentes e modificando os dados dos produtos do est_atual */
    
    for (int m = 0; m < total_mov; m++){
        int inexistente = 1; // flag pra saber se o prod do movimento é existente
        for (int p = 0; p < total_produtos;  p++){

            if (capac_inconsist <= total_inc){ // realloc se necessário
                capac_inconsist *= 2;
                Inconsist *temp = realloc(inconsist, capac_inconsist);
                if (temp == NULL){
                    fclose(arq_prod);
                    fclose(arq_mov);
                    fclose(arq_atualizado);
                    fclose(arq_relatorio);
                    free(vetor_prod);
                    free(vetor_mov);
                    free(est_baixo);
                    free(inconsist);
                    exit(1);
                }
                inconsist = temp;
            }

            if (vetor_mov[m].codigo == est_atual[p].codigo){
                inexistente = 0;
                // se esse produto ainda não estiver na lista de prod processados,
                // incrementamos o contador
                if (!ja_processado(lista_processados, est_atual[p].codigo, total_produtos)){ 
                    lista_processados[prod_processados] =  est_atual[p].codigo;
                    prod_processados++;
                }
                if (vetor_mov[m].tipo == 'S'){ // saida de estoque

                    // saida autorizada
                    if (vetor_mov[m].qtd_movimento <= est_atual[p].qtd_estoque){
                        est_atual[p].qtd_estoque -= vetor_mov[m].qtd_movimento;
                        mov_aplicados++;

                    } else { // saida recusada, movimento nao deve ser aplicado
                        saidas_recusadas++;
                        inconsist[total_inc].codigo = vetor_mov[m].codigo;
                        inconsist[total_inc].qtd_movimento = vetor_mov[m].qtd_movimento;
                        inconsist[total_inc].tipo = vetor_mov[m].tipo;
                        strcpy(inconsist[total_inc].inconsistencia, "ESTOQUE_INSUFICIENTE");
                        total_inc++;
                    }

                } else { // entrada de estoque
                    est_atual[p].qtd_estoque += vetor_mov[m].qtd_movimento;
                    mov_aplicados++;
                }
            }

            // teste se o produto do movimento é inexistente
            if (p == total_produtos-1 && inexistente == 1){
                inconsist[total_inc].codigo = vetor_mov[m].codigo;
                inconsist[total_inc].qtd_movimento = vetor_mov[m].qtd_movimento;
                inconsist[total_inc].tipo = vetor_mov[m].tipo;
                strcpy(inconsist[total_inc].inconsistencia, "PRODUTO_INEXISTENTE");
                sem_cadastro++;
                total_inc++;
            }
        }
    }

    // varrer o estoque atual para definir os produtos com estoque baixo
    for (int i = 0; i<total_produtos; i++){
        if (est_atual[i].qtd_estoque <= 5){

            if (capac_est_baixo <= baixo){ // realloc se necessário
                capac_est_baixo *= 2;
                Produtos *temp = realloc(est_baixo, capac_est_baixo);
                if (temp == NULL){
                    fclose(arq_prod);
                    fclose(arq_mov);
                    fclose(arq_atualizado);
                    fclose(arq_relatorio);
                    free(vetor_prod);
                    free(vetor_mov);
                    free(est_baixo);
                    free(inconsist);
                    exit(1);
                }
                est_baixo = temp;
            }

            est_baixo[baixo++] = est_atual[i];
        }
    }

    // OK, DADOS COLETADOS E PROCESSADOS!!!!!!
    // ESCREVENDO OS ARQUIVOS
    // estoque_atualizado.txt
    for (int i = 0; i < total_produtos; i++){
        // variaveis auxiliares para facilitar o sprintf
        int c = est_atual[i].codigo;
        char n[30];
        strcpy(n, est_atual[i].nome);
        int q = est_atual[i].qtd_estoque;
        float p = est_atual[i].preco;
        fprintf(arq_atualizado, "%d %s %d %.2f\n", c, n, q, p);
    }

    // relatorio.txt
    fprintf(arq_relatorio, "PRODUTOS PROCESSADOS: %d\n", prod_processados);
    fprintf(arq_relatorio, "MOVIMENTOS APLICADOS: %d\n", mov_aplicados);
    fprintf(arq_relatorio, "SAIDAS RECUSADAS: %d\n", saidas_recusadas);
    fprintf(arq_relatorio, "MOVIMENTOS SEM CADASTRO: %d\n", sem_cadastro);
    
    fprintf(arq_relatorio, "ESTOQUE BAIXO:\n");
    for (int e = 0; e < baixo; e++){
        fprintf(arq_relatorio, "%d %s %d\n", est_baixo[e].codigo, est_baixo[e].nome, est_baixo[e].qtd_estoque);
    }

    fprintf(arq_relatorio, "INCONSISTENCIAS:");
    for (int s = 0; s < total_inc; s++){
        fprintf(arq_relatorio, "\n%d %c %d %s", inconsist[s].codigo, inconsist[s].tipo, inconsist[s].qtd_movimento, inconsist[s].inconsistencia);
    }

    return 0;
}

// funcao que define se vai incrementar o contador de produtos processados
int ja_processado(int lista_processados[], int cod_produto, int tot_prod){
    int ja_processado = 0;
    for (int i = 0; i< tot_prod; i++){
        if (lista_processados[i] == cod_produto){
            ja_processado = 1;
        }
    }
    return ja_processado;
}