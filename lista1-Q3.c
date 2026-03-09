// Código escrito e comparado com o que foi gerado pelo Claude para correção de alguns erros 
// e entendimento da questão, além de pesquisa de sintaxe como os simbolos && e ||

#include <stdio.h>

int main(){

    int money, x, y, z;     // ENTRADA
    int A, B, C; 
    int R = 3;           // QUANTO CADA HOMEM e rebeka GANHOU 
    int sucesso = 0;
    int t, investimento;   //usadas para o incremento do dinheiro
    scanf("%d %d %d %d", &money, &x, &y, &z);
    
    if ((money*x)%100 == 0 && (money*y)%100 == 0 && (money*z)%100 == 0){ //se for inteiro 
        A = x * money / 100;
        B = y * money / 100;
        C = z * money / 100;
        sucesso = 1;
        
        if (A+B+C < money){
            R += money - A - B - C;
        }
    } 
    
    if (sucesso == 0){
    // valores não inteiros, rebeka investe dinheiro
    // checar se com ela investindo dinheiro vai conseguir dividir
        t = money + 1; //investiu 1 real
        if ((t*x)%100 == 0 && (t*y)%100 == 0 && (t*z)%100 == 0){
            A = x * t / 100;
            B = y * t / 100;
            C = z * t / 100;
            investimento = 1;
            int sobra = t - A - B - C;

            if (sobra > investimento){
                sucesso = 1;
                R += sobra - investimento;
            }
        }
    }

    if (sucesso == 0){
        t = money + 2; //investiu 2 reais
        if ((t*x)%100 == 0 && (t*y)%100 == 0 && (t*z)%100 == 0){
            A = x * t / 100;
            B = y * t / 100;
            C = z * t / 100;
            investimento = 2;
            int sobra = t - A - B - C;

            if (sobra > investimento){
                sucesso = 1;
                R += sobra - investimento;
            }
        }
    }

    if (sucesso == 0){
        t = money + 3; //investiu 3 reais
        if ((t*x)%100 == 0 && (t*y)%100 == 0 && (t*z)%100 == 0){
            A = x * t / 100;
            B = y * t / 100;
            C = z * t / 100;
            investimento = 3;
            int sobra = t - A - B - C;

            if (sobra > investimento){
                sucesso = 1;
                R += sobra - investimento;
            }
        }
    }

    if (sucesso == 1){
        printf("Cada homem ficou com %d, %d e %d reais, respectivamente\n", A, B, C);

        //rebeka prova que sabe fazer contas
        if (investimento == 2){
            char l, m, n;
            int v1, v2, v3;
            scanf(" %c %c %c", &l, &m, &n);
            v1 = l;
            v2 = m;
            v3 = n;

            if (v1 > 90){
                // minuscula
                v1 = l - 'a' + 1; // 'a' tem valor 97
            } else { 
                // maiuscula
                v1 = l - 'A' + 1; // 'A' tem valor 65
            }

            if (v2 > 90){
                // minuscula
                v2 = m - 'a' + 1;
            } else { 
                // maiuscula
                v2 = m - 'A' + 1;
            }
            
            if (v3 > 90){
                // minuscula
                v3 = n - 'a' + 1;
            } else { 
                // maiuscula
                v3 = n - 'A' + 1;
            }
        
            printf("%d\n", v1 + v2 + v3);

        } else if (investimento == 3){
            int i1, i2, i3;
            scanf("%d %d %d", &i1, &i2, &i3);
            
            if (i1 % 3 ==0 || i2 % 3 == 0 || i3 % 3 == 0){
                //Rebeka deverá retornar a soma final de parcelas do número 3 presente nas idades deles
                int parcelas = 0;
                if (i1 % 3 == 0) parcelas += i1 / 3;
                if (i2 % 3 == 0) parcelas += i2 / 3;
                if (i3 % 3 == 0) parcelas += i3 / 3;
                printf("%d\n", parcelas);
            }
        }
    }else{
        printf("Nao foi dessa vez que Rebeka pode ajudar...\n");
    }
  
    if (R >= 7){
        printf("Ela conseguiu! Rebeka voltou para casa e apanhou da mae por sumir noite passada!\n");
    }else{
        printf("E parece que Rebeka vai ter que voltar andando...\n");
    }
    
    return 0;
}
