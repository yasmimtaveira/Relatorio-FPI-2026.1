#include <stdio.h>

int main(){

    int money, x, y, z;     // ENTRADA
    int A, B, C, R;            // QUANTO CADA HOMEM e rebeka GANHOU 
    int sucesso;
    scanf("%d %d %d %d", &money, &x, &y, &z);
    
    if (//inteiros){  
        A = x/100 * money;
        B = y/100 * money;
        C = z/100 * money;
        sucesso = 1;
        
        if (A+B+C < money){
            R = money - A - B - C;
        }else {
            R = 0;
        }
    } else {
        // valores não inteiros, rebeka investe dinheiro
        // checar se com ela investindo dinheiro vai conseguir dividir
        // se conseguir:
        sucesso = 1;
        //se nao conseguir:
        sucesso = 0;
        
        int investimento;
        if (investimento == 2){
            int l, m, n;
            scanf("%d %d %d", &l, &m, &n);
            
        } else if (investimento == 3){
            int i1, i2, i3;
            scanf("%d %d %d", &i1, &i2, &i3);
            
            if (i1 % 3 ==0 || i2 % 3 == 0 || i3 % 3 == 0){
                //Rebeka deverá retornar a soma final de parcelas do número 3 presente nas idades deles
            }
        }
    }
    
    if (sucesso == 1){
        prinf("Cada homem ficou com %d, %d e %d reais, respectivamente\n", A, B, C);
    }else{
        prinf_s(“Nao foi dessa vez que Rebeka pode ajudar...\n”);
    }
    
    if (R >= 7){
        prinf_s(“Ela conseguiu! Rebeka voltou para casa e apanhou da mae por sumir noite passada!\n”);
    }else{
        prinf_s(“E parece que Rebeka vai ter que voltar andando...\n”);
    }
    
    return 0;
}
