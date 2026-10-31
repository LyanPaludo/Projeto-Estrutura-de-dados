#ifndef FILA_H
#define FILA_H
#include <stdbool.h>

typedef struct Fila Fila;

//CREATE
Fila *fila_criar(void);

//READ
void *fila_espiar_frente(Fila *fila);
void fila_percorrer(Fila *fila, void (*visitar)(void *dado));
int fila_tamanho(Fila *fila);

//UPDATE
bool fila_enfileirar(Fila *fila, void *dado);
void *fila_desenfileirar(Fila *fila);

//DELETE
void fila_liberar(Fila *fila, void (*liberador)(void *dado));


#endif