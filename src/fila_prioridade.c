#include "fila_prioridade.h"
#include "fila.h"
#include <stdlib.h>

struct FilaPrioridade{
    Fila *filas[PRIORIDADE_QTD];
};

//create
FilaPrioridade *fila_prioridade_criar(void){
    FilaPrioridade *fp = (FilaPrioridade *) malloc(sizeof(FilaPrioridade));
    if (fp == NULL){
        return NULL;
    }
    for (int i=0; i<PRIORIDADE_QTD; i++){
        fp->filas[i] = fila_criar();
        if (fp->filas[i] == NULL){
            for (int j=0; j<i; j++){
                fila_liberar(fp->filas[j], NULL);
            }
            free(fp);
            return NULL;
        }
    }
    return fp;
}

//read
void *fila_prioridade_espiar_frente(FilaPrioridade *fp){
    for (int i=0; i<PRIORIDADE_QTD; i++){
        if (fila_tamanho(fp->filas[i]) > 0){
            return fila_espiar_frente(fp->filas[i]);
        }
    }
    return NULL;
}

void fila_prioridade_percorrer(FilaPrioridade *fp, void(*visitar)(void *dado)){
    for (int i=0; i<PRIORIDADE_QTD; i++){
        fila_percorrer(fp->filas[i], visitar);
    }
}

int fila_prioridade_tamanho(FilaPrioridade *fp){
    int tamanho = 0;
    for (int i=0; i<PRIORIDADE_QTD; i++){
        tamanho += fila_tamanho(fp->filas[i]);
    }
    return tamanho;
}


//update
bool fila_prioridade_enfileirar(FilaPrioridade *fp, void *dado, int prioridade){
    if (prioridade < 0 || prioridade > PRIORIDADE_QTD-1){
        return false;
    }
    if (!fila_enfileirar(fp->filas[prioridade], dado)){
        return false;
    }
    return true;
}
void *fila_prioridade_desenfileirar(FilaPrioridade *fp){
    for (int i=0; i<PRIORIDADE_QTD; i++){
        if (fila_tamanho(fp->filas[i]) > 0){
            return fila_desenfileirar(fp->filas[i]);
        }
    }
    return NULL;
}

//delete
void fila_prioridade_liberar(FilaPrioridade *fp, void(*liberador)(void *dado)){
    for (int i=0; i<PRIORIDADE_QTD; i++){
        fila_liberar(fp->filas[i], liberador);
    }
    free(fp);
}
