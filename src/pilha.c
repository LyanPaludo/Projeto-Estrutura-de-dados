#include "pilha.h"
#include <stdlib.h>

typedef struct No{
    Produto *produto;
    struct No *abaixo;
}No;

struct Pilha{
    No *topo;
    int tamanho;
    int volume;
};

//CREATE
Pilha *pilha_criar(void){
    Pilha *pilha = (Pilha *) malloc(sizeof(Pilha));
    if (pilha == NULL){
        return NULL;
    }
    pilha->topo    = NULL;
    pilha->tamanho = 0;
    pilha->volume  = 0;
    return pilha;
}
//READ
Produto *pilha_espiar_topo(Pilha *pilha){
    if (pilha->topo == NULL){
        return NULL;
    }
    return pilha->topo->produto;
}

void pilha_percorrer(Pilha *pilha, void (*visitar)(Produto *)){
    No *atual = pilha->topo;
    while (atual != NULL){
        visitar(atual->produto);
        atual = atual->abaixo;
    }
}

int pilha_tamanho(Pilha *pilha){
    return pilha->tamanho;
}

int pilha_volume(Pilha *pilha){
    return pilha->volume;
}



//UPDATE
bool pilha_empilhar(Pilha *pilha, Produto *produto){
    if (produto == NULL){
        return false;
    }
    No *no = (No *) malloc(sizeof(No));
    if (no == NULL){
        return false;
    }
    no->produto = produto;
    no->abaixo  = pilha->topo;
    pilha->topo = no;
    pilha->tamanho++;
    pilha->volume += produto_get_volume(produto);
    return true;
}

Produto *pilha_desempilhar(Pilha *pilha){
    if (pilha->topo == NULL){
        return NULL;
    }
    No *topo = pilha->topo;
    Produto *produto = topo->produto;
    pilha->topo = topo->abaixo;
    pilha->tamanho--;
    pilha->volume -= produto_get_volume(produto);
    free(topo);
    return produto;
}

//DELETE
void pilha_liberar(Pilha *pilha){
    No *atual = pilha->topo;
    while (atual != NULL){
        No *abaixo = atual->abaixo;
        free(atual);
        atual = abaixo;
    }
    free(pilha);
}