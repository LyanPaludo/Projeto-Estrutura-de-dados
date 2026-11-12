#include "catalogo.h"
#include "utils.h"
#include "constantes.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>

struct Produto{
    uint64_t codigo;
    char *nome;
    int qtd;                //Quantidade deste produto no estoque
    int volume;             //Volume ocupado por um único produto
    struct Produto *prox;   //Próximo produto na lista
};

struct Catalogo{
    int prod_total;     //Quantidade de produtos diferentes
    Produto *primeiro;
    Produto *ultimo;
};

//GERAR PRÓXIMO CÓDIGO
static uint64_t produto_gerar_cod(void) {
    static uint64_t contador_cod = 1;
    return contador_cod++;
}
//INSERT
static void produto_inserir(Catalogo *control, Produto *produto){
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

Produto *produto_cadastrar_estoque(const char *nome, int qtd, int volume, Catalogo *control){
    if (nome == NULL || control == NULL || qtd <= 0 || volume < PRODUTO_VOLUME_MIN || volume > PRODUTO_VOLUME_MAX){
        return NULL;
    }
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
    produto->codigo = produto_gerar_cod();
    produto_inserir(control, produto);
    return produto;
}

//CREATE
Catalogo *catalogo_criar(void){
    Catalogo *control  = (Catalogo *) malloc(sizeof(Catalogo));
    if (control == NULL){
        return NULL;
    }
    control->prod_total = 0;
    control->primeiro   = NULL;
    control->ultimo     = NULL;
    return control;
    
}

//READ
void catalogo_percorrer(Catalogo *estoque, void (*visitar)(Produto *p)){
    if (catalogo_vazio(estoque)){
        return;
    }
    Produto *atual = estoque->primeiro;
    while (atual != NULL){
        visitar(atual);
        atual = atual->prox;
    }
}

bool catalogo_vazio(Catalogo *estoque){
    if (estoque == NULL || estoque->primeiro == NULL){
        return true;
    }
    return false;
}

Produto *produto_search_name(const char *nome, Catalogo *control){
    Produto *atual = control->primeiro;
    while (atual != NULL){
        if (comparar_sem_case(nome, atual->nome)==0){
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}
Produto *produto_search_code(uint64_t codigo, Catalogo *control){
    Produto *atual = control->primeiro;
    while (atual != NULL){
        if (atual->codigo == codigo){
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}
uint64_t produto_get_code(Produto *produto){
    return produto->codigo;
}
const char *produto_get_name(Produto *produto){
    return produto->nome;
}
int produto_get_qtd(Produto *produto){
    return produto->qtd;
}
int produto_get_volume(Produto *produto){
    return produto->volume;
}

//UPDATE
bool produto_aumentar_estoque(Produto *produto, int qtd){
    if (produto == NULL){
        return false;
    }
    if (qtd <= 0 || produto->qtd > (INT_MAX - qtd)){
        return false;
    }
    produto->qtd += qtd;
    return true;
}
bool produto_descontar_estoque(Produto *produto, int qtd){
    if (produto == NULL){
        return false;
    }
    if (qtd <= 0){
        return false;
    }
    if (produto->qtd - qtd < 0){
        return false;
    }
    produto->qtd -= qtd;
    return true;
}

//DELETE
static void produto_liberar(Produto *produto){
    free(produto->nome);
    free(produto);
}
void catalogo_liberar(Catalogo *control){
    Produto *atual = control->primeiro;
    while (atual!=NULL){
        Produto *prox = atual->prox;
        produto_liberar(atual);
        atual = prox;
    }
    free(control);
}




