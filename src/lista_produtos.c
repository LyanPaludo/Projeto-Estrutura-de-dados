#include "lista_produtos.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

//GERAR PRÓXIMO CÓDIGO
static uint64_t gerar_prox_cod(void) {
    static uint64_t contador_cod = 1;
    return contador_cod++;
}
//INSERT
void inserir_produto(Controle *control, Produto *produto){
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

Produto *cad_prod_sys(char *nome, int qtd, int volume, Controle *control){
    Produto *produto = (Produto *) malloc(sizeof(Produto));
    if (produto == NULL){
        return NULL;
    }
    char *name = (char *) malloc(strlen(nome)*sizeof(char));
    strcpy(name, nome);
    produto->nome   = name;
    produto->qtd    = qtd;
    produto->volume = volume;
    produto->codigo = gerar_prox_cod();
    inserir_produto(control, produto);
    return produto;
}

//CREATE
Controle *criar_lista(void){
    Controle *control  = (Controle *) malloc(sizeof(Controle));
    if (control == NULL){
        return NULL;
    }
    control->prod_total = 0;
    control->primeiro   = NULL;
    control->ultimo     = NULL;
    return control;
    
}

//READ
Produto *pesquisar_por_nome(char *nome, Controle *control){
    Produto *atual = control->primeiro;
    while (atual != NULL){
        if (comparar_sem_case(nome, atual->nome)==0){
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}
Produto *pesquisar_por_codigo(uint64_t codigo, Controle *control){
    Produto *atual = control->primeiro;
    while (atual != NULL){
        if (atual->codigo == codigo){
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

//UPDATE
void aumentar_quantidade(Produto *produto, int qtd){
    produto->qtd += qtd;
}

//DELETE
void liberar_produto(Produto *produto){
    free(produto->nome);
    free(produto);
}
void liberar_lista(Controle *control){
    Produto *atual = control->primeiro;
    while (atual!=NULL){
        Produto *prox = atual->prox;
        liberar_produto(atual);
        atual = prox;
    }
    free(control);
}
