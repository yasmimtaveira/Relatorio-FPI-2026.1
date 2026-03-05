#include <stdio.h>

int main(){

    int money, x, y, z;     // ENTRADA
    int A, B, C, R;            // QUANTO CADA HOMEM e rebeka GANHOU 
    scanf("%d %d %d %d", &money, &x, &y, &z);
    
    if (x/100 % money == 0 && y/100 %money == 0 && z/100 %money == 0){  
       A = x/100 * money;
       B = y/100 * money;
       C = z/100 * money;
        
        if (A+B+C < money){
            R = money - A - B - C;
        }
    }
    
    return 0;
}
