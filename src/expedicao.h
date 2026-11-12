#ifndef EXPEDICAO_H
#define EXPEDICAO_H
#include "caminhao.h"
#include "fila_prioridade.h"
#include <stdbool.h>
typedef struct Expedicao Expedicao;

//create
Expedicao *expedicao_criar(void);

//read
Caminhao *expedicao_get_doca(Expedicao *exp, int i);
int expedicao_historico_tamanho(Expedicao *exp);
void expedicao_percorrer_historico(Expedicao *exp, void (*visitar)(void *));

//update
bool expedicao_expedir(Expedicao *exp, FilaPrioridade *pacotes);

//delete
void expedicao_liberar(Expedicao *exp);

#endif