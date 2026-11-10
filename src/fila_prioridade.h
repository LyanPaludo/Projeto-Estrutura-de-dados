#ifndef FILA_PRIORIDADE_H
#define FILA_PRIORIDADE_H
#include <stdbool.h>
#include "constantes.h"

typedef struct FilaPrioridade FilaPrioridade;

//create
FilaPrioridade *fila_prioridade_criar(void);

//read
void *fila_prioridade_espiar_frente(FilaPrioridade *fp);
void fila_prioridade_percorrer(FilaPrioridade *fp, void(*visitar)(void *dado));
int fila_prioridade_tamanho(FilaPrioridade *fp);


//update
bool fila_prioridade_enfileirar(FilaPrioridade *fp, void *dado, int prioridade);
void *fila_prioridade_desenfileirar(FilaPrioridade *fp);

//delete
void fila_prioridade_liberar(FilaPrioridade *fp, void(*liberador)(void *dado));
#endif