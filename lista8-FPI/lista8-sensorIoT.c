#include <stdio.h>

// struct que "pega os bits"
struct camposBits {
    unsigned int erro : 1;
    unsigned int modoOperacao : 3;
    unsigned int leitura : 4;
};

union decodificador { // union pedida na questão
    unsigned char rawByte;
    struct camposBits campo;
};

int main(){
    int x;
    scanf("%d", &x); // leitura do numero

    union decodificador Decod;
    Decod.rawByte = (unsigned char)x; // atribuo o numero na union depois de fazer a conversao

    // prints
    printf("Byte bruto: %d | Erro: %d | Modo: %d | Leitura: %d", Decod.rawByte, Decod.campo.erro, Decod.campo.modoOperacao, Decod.campo.leitura);

    return 0;
}