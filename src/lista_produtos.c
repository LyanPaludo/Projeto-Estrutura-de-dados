#include "lista_produtos.h"
#include "utils.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct Produto{
    uint64_t codigo;
    char *nome;
    int qtd;                //Quantidade deste produto no estoque
    int volume;             //Volume ocupado por um único produto
    struct Produto *prox;   //Próximo produto na lista
}Produto;

typedef struct ListaProdutos{
    int prod_total;     //Quantidade de produtos diferentes
    Produto *primeiro;
    Produto *ultimo;
}ListaProdutos;

//GERAR PRÓXIMO CÓDIGO
static uint64_t gerar_prox_cod(void) {
    static uint64_t contador_cod = 1;
    return contador_cod++;
}
//INSERT
static void inserir_produto(ListaProdutos *control, Produto *produto){
    if (control->primeiro == NULL){
        control->primeiro       = produto;
        control->ultimo         = produto;
    }else{
        control->ultimo->prox   = produto;
        control->ultimo         = produto;
    }
    produto->prox       = NULL;
    control->prod_total += 1;
}

Produto *cad_prod_sys(char *nome, int qtd, int volume, ListaProdutos *control){
    Produto *produto = (Produto *) malloc(sizeof(Produto));
    if (produto == NULL){
        return NULL;
    }
    char *name = (char *) malloc((strlen(nome)+1)*sizeof(char));
    if (name == NULL){
        free(produto);
        return NULL;
    }
    strcpy(name, nome);
    produto->nome   = name;
    produto->qtd    = qtd;
    produto->volume = volume;
    produto->codigo = gerar_prox_cod();
    inserir_produto(control, produto);
    return produto;
}

//CREATE
ListaProdutos *criar_lista_produto(void){
    ListaProdutos *control  = (ListaProdutos *) malloc(sizeof(ListaProdutos));
    if (control == NULL){
        return NULL;
    }
    control->prod_total = 0;
    control->primeiro   = NULL;
    control->ultimo     = NULL;
    return control;
    
}

//READ
Produto *pesquisar_por_nome(char *nome, ListaProdutos *control){
    Produto *atual = control->primeiro;
    while (atual != NULL){
        if (comparar_sem_case(nome, atual->nome)==0){
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}
Produto *pesquisar_por_codigo(uint64_t codigo, ListaProdutos *control){
    Produto *atual = control->primeiro;
    while (atual != NULL){
        if (atual->codigo == codigo){
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}
const uint64_t getCode(Produto *produto){
    return produto->codigo;
}
const char *getName(Produto *produto){
    return produto->nome;
}
const int getQtd(Produto *produto){
    return produto->qtd;
}
const int getVolume(Produto *produto){
    return produto->volume;
}
Produto *getFirst(ListaProdutos *control){
    return control->primeiro;
}
Produto *getLast(ListaProdutos *control){
    return control->ultimo;
}
Produto *getNext(Produto *produto){
    return produto->prox;
}

//UPDATE
void aumentar_estoque(Produto *produto, int qtd){
    produto->qtd += qtd;
}
bool descontar_estoque(Produto *produto, int qtd){
    if (produto->qtd - qtd < 0){
        return false;
    }
    produto->qtd -= qtd;
    return true;
}

//DELETE
static void liberar_produto(Produto *produto){
    free(produto->nome);
    free(produto);
}
void liberar_lista(ListaProdutos *control){
    Produto *atual = control->primeiro;
    while (atual!=NULL){
        Produto *prox = atual->prox;
        liberar_produto(atual);
        atual = prox;
    }
    free(control);
}




