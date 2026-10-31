#include "fila.h"
#include <stdlib.h>

typedef struct No{
    void *dado; //pode ser pacote ou pedido
    struct No *prox;
}No;

struct Fila{
    int tam;
    No *primeiro;
    No *ultimo;
};

//CREATE
Fila *fila_criar(void){
    Fila *fila = (Fila *) malloc(sizeof(Fila));
    if (fila == NULL){
        return NULL;
    }
    fila->primeiro = NULL;
    fila->ultimo   = NULL;
    fila->tam      = 0;
    return fila;
}

//READ
void *fila_espiar_frente(Fila *fila){
    if (fila->primeiro == NULL){
        return NULL;
    }
    return fila->primeiro->dado;
}

void fila_percorrer(Fila *fila, void (*visitar)(void *dado)){
    No *atual = fila->primeiro;
    while (atual != NULL){
        visitar(atual->dado);
        atual = atual->prox;
    }
}

int fila_tamanho(Fila *fila){
    return fila->tam;
}


//UPDATE
bool fila_enfileirar(Fila *fila, void *dado){
    if (dado == NULL){
        return false;
    }
    No *no = (No *) malloc(sizeof(No));
    if (no == NULL){
        return false;
    }
    no->dado = dado;
    no->prox = NULL;
    if (fila->primeiro == NULL){
        fila->primeiro = no;
        fila->ultimo   = no;
    }else{
        fila->ultimo->prox = no;
        fila->ultimo       = no;
    }
    fila->tam++;
    return true;
}
void *fila_desenfileirar(Fila *fila){
    No *no = fila->primeiro;
    if (no == NULL){
        return NULL;
    }
    void *dado = no->dado;
    fila->primeiro = no->prox;
    if (fila->primeiro == NULL){
        fila->ultimo = NULL;
    }
    fila->tam--;
    free(no);
    return dado;
}  

//DELETE
void fila_liberar(Fila *fila, void (*liberador)(void *dado)){
    No *atual = fila->primeiro;
    while (atual != NULL){
        No *prox = atual->prox;
        if (liberador != NULL){
            liberador(atual->dado);
        }
        free(atual);
        atual = prox;
    }
    free(fila);
}