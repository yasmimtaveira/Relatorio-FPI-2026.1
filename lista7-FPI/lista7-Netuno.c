// uso de IA para entender o funcionamento da questão e os requisitos de implementação
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Mecha Mecha;

typedef struct {
    char nome[30];
    int atrib1;     // Atk: Dano Base   | Def: Blindagem Fixa | Utl: Recup. Base
    int atrib2;     // Atk: Custo Ener. | Def: Bônus de Slot   | Utl: Multiplicador
    void (*subrotina)(Mecha *m, int slot, int input, int *output);
} SubSistema;

struct Mecha {
    int id;                // Identificador único (0 até N-1)
    char modelo[50];
    int energia_atual;
    int num_sistemas; // Q
    int valor_wintermute;  // Contexto de dano enviado pelo Comando
    SubSistema sistemas[]; // O Flexible Array Member (FAM)
};

void rotinaDefesa(Mecha *m, int slot, int input, int *output);
void rotinaUtilidade(Mecha *m, int slot, int input, int *output);
void rotinaAtaque(Mecha *m, int slot, int input, int *output);

int main(){
    int n;
    scanf("%d", &n);

    // vetor de ponteiros para o esquadrao
    Mecha **esquadrao = malloc(n * sizeof(Mecha *));

    // verificar alocação
    if (esquadrao == NULL) exit(1);

    for (int i = 0; i < n; i++){
        int id, energia, num_sistemas;
        char modelo[50];

        scanf("%d %s %d %d", &id, modelo, &energia, &num_sistemas);

        // alocacao UNICA
        Mecha *novoMecha = malloc(sizeof(Mecha) + (num_sistemas * sizeof(SubSistema)));
        if (novoMecha == NULL) exit(1);

        // colocando os dados na mecha
        novoMecha->id = id;
        strcpy(novoMecha->modelo, modelo);
        novoMecha->energia_atual = energia;
        novoMecha->num_sistemas = num_sistemas;

        // preenchedno o array de subsistemas com os dados para combate
        for (int j = 0; j < num_sistemas; j++){
            char tipo;
            scanf(" %c %s %d %d", &tipo, novoMecha->sistemas[j].nome, &novoMecha->sistemas[j].atrib1, &novoMecha->sistemas[j].atrib2);
        
            // definir o ponteiro para funcao de acordo com o tipo de subsistema
            if (tipo == 'D') novoMecha->sistemas[j].subrotina = rotinaDefesa;
            if (tipo == 'U') novoMecha->sistemas[j].subrotina = rotinaUtilidade;
            if (tipo == 'A') novoMecha->sistemas[j].subrotina = rotinaAtaque;       
        }

        int valor_wintermute;
        scanf("%d", &valor_wintermute);
        novoMecha->valor_wintermute = valor_wintermute;
        esquadrao[i] = novoMecha; // adicionando a mecha já preenchida ao esquadrao
    }

    // ordenar de acordo com o ID (bubble sort)
    for (int i = 0; i < n -1; i++){
        for (int j = 0; j < n - i - 1; j++){
            if (esquadrao[j]->id > esquadrao[j+1]->id){
                Mecha *temp = esquadrao[j];
                esquadrao[j] = esquadrao[j+1];
                esquadrao[j+1] = temp;
            }
        }
    }

    // protocolo de saida
    printf("%s\n", "[RELATORIO DE MISSÃO: OPERAÇÃO LANÇA DE NETUNO]");

    for (int i = 0; i < n; i++){ // looping para cada mecha
        Mecha *m = esquadrao[i];
        // array de ponteiros para função (as rotinas)
        void (*ordemRotinas[])(Mecha *, int, int, int *) = {rotinaDefesa, rotinaUtilidade, rotinaAtaque}; 
        
        printf("ID: %d | MECHA: %s | ENERGIA: %d\n", esquadrao[i]->id, esquadrao[i]->modelo, esquadrao[i]->energia_atual);
        
        for (int j = 0; j < 3; j++){ // looping para a ordem das rotinas ser sempre defesa, utilidade e ataque
            for (int s = 0; s < m->num_sistemas; s++){ // looping para cada sistema que o mecha tenha

                // verificar se é a rotina da vez por comparação de ponteiros
                if (m->sistemas[s].subrotina == ordemRotinas[j]){ 
                    int resultado;
                    // chamando a subrotina (função) e armazenando o resultado
                    m->sistemas[s].subrotina(m, s, m->valor_wintermute, &resultado);

                    // prints correspondentes de cada rotina
                    if (ordemRotinas[j] == rotinaDefesa){
                        printf("-> [DEFESA] %s | Dano final sofrido: %d\n", m->sistemas[s].nome, resultado);
                    
                    } else if (ordemRotinas[j] == rotinaUtilidade){
                        printf("-> [UTILIDADE] %s | Energia atual: %d\n", m->sistemas[s].nome, resultado);
                    
                    } else if (ordemRotinas[j] == rotinaAtaque){
                        if (resultado == -1){ //  ataque falho
                            printf("-> [ATAQUE] %s | Energia insuficiente!\n", m->sistemas[s].nome);
                        } else {  // bem sucedido
                            printf("-> [ATAQUE] %s | Dano causado: %d | Energia restante: %d\n", m->sistemas[s].nome, resultado, m->energia_atual);
                        }
                    }
                }
            }
        }
        printf("ENERGIA FINAL: %d\n", m->energia_atual);
        printf("%s\n", "-----------------------------------------"); // apos cada mecha
        free(esquadrao[i]); // liberando a memória alocada para a mecha após o uso
    }   
    printf("%s\n", "Esquadrao pronto para o combate.");
    
    free(esquadrao); // liberando a memória alocada para o vetor de ponteiros
    return 0;
}

// funções de rotina
void rotinaDefesa(Mecha *m, int slot, int input, int *output){
    int DanoFinal = input - (m->sistemas[slot].atrib1) - slot * (m->sistemas[slot].atrib2);
    if (DanoFinal < 0) DanoFinal = 0;
    *output = DanoFinal;
}

void rotinaUtilidade(Mecha *m, int slot, int input, int *output){
    int recuperado = (m->sistemas[slot].atrib1) + slot * (m->sistemas[slot].atrib2);
    m->energia_atual += recuperado;
    *output = m->energia_atual;
}

void rotinaAtaque(Mecha *m, int slot, int input, int *output){
    int dano;
    if (m->energia_atual < m->sistemas[slot].atrib2){
        dano = -1; // ataque cancelado
    } else {
        dano = m->sistemas[slot].atrib1 + m->energia_atual + slot - input;
        m->energia_atual -= m->sistemas[slot].atrib2;
    }
    *output = dano;
}