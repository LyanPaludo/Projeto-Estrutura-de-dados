#include "fila.h"
#include <stdio.h>

static void imprimir_int(void *dado){
    printf("%d\n", *(int *) dado);
}


int main(void){
    Fila *fila = fila_criar();
    int a=1, b=2, c=3;
    fila_enfileirar(fila, &a);
    fila_enfileirar(fila, &b);
    fila_enfileirar(fila, &c);
    imprimir_int(fila_espiar_frente(fila));
    printf("\nTamanho: %d\n", fila_tamanho(fila));
    fila_percorrer(fila, imprimir_int); 
    fila_desenfileirar(fila);
    printf("\nDesenfileirou: ");
    printf("\nTamanho: %d\n", fila_tamanho(fila));
    fila_percorrer(fila, imprimir_int); 
    fila_desenfileirar(fila);
    printf("\nDesenfileirou: ");
    printf("\nTamanho: %d\n", fila_tamanho(fila));
    fila_percorrer(fila, imprimir_int); 
    fila_desenfileirar(fila);
    printf("\nDesenfileirou: ");
    printf("\nTamanho: %d\n", fila_tamanho(fila));
    fila_percorrer(fila, imprimir_int); 

    fila_liberar(fila, NULL);
    return 0;
}