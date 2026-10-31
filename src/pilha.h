#ifndef PILHA_H
#define PILHA_H
#include "lista_produtos.h"
#include <stdbool.h>

typedef struct Pilha Pilha;

//CREATE
Pilha *pilha_criar(void); //Criar pilha
//READ
Produto *pilha_espiar_topo(Pilha *pilha); //Ver qual produto está no topo da pilha
void pilha_percorrer(Pilha *pilha, void (*visitar)(Produto *)); //Percorrer cada nó da pilha
int pilha_tamanho(Pilha *pilha); //Retorna o tamanho da pilha
int pilha_volume(Pilha *pilha);  //Retorna o volume total da pilha

//UPDATE
bool pilha_empilhar(Pilha *pilha, Produto *produto); //Empilha um produto na pilha
Produto *pilha_desempilhar(Pilha *pilha);            //Desempilha o topo da pilha

//DELETE
void pilha_liberar(Pilha *pilha); //Libera a pilha
#endif