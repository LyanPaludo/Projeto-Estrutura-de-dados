#ifndef CAMINHAO_H
#define CAMINHAO_H
#include "pacote.h"
#include <stdbool.h>

typedef struct Caminhao Caminhao;

//create
Caminhao *caminhao_criar(int numero, int capacidade);

//read
bool caminhao_cabe(Caminhao *cmn, Pacote *pacote);
bool caminhao_cheio(Caminhao *cmn);
void caminhao_percorrer(Caminhao *cmn, void (*visitar)(void *dado));
int caminhao_get_numero(Caminhao *cmn);
int caminhao_get_capacidade(Caminhao *cmn);
int caminhao_get_usado(Caminhao *cmn);
int caminhao_get_qtd(Caminhao *cmn);
//update
bool caminhao_carregar(Caminhao *cmn, Pacote *pacote);

//delete
void caminhao_liberar(Caminhao *cmn);

#endif