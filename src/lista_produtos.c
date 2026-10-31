#include "lista_produtos.h"
#include "utils.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

struct Produto{
    uint64_t codigo;
    char *nome;
    int qtd;                //Quantidade deste produto no estoque
    int volume;             //Volume ocupado por um único produto
    struct Produto *prox;   //Próximo produto na lista
};

struct ListaProdutos{
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
static void produto_inserir(ListaProdutos *control, Produto *produto){
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

Produto *produto_cadastrar_estoque(const char *nome, int qtd, int volume, ListaProdutos *control){
    if (qtd <= 0 || volume < 1 || volume > 10){
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
ListaProdutos *lista_produtos_criar(void){
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
Produto *produto_search_name(const char *nome, ListaProdutos *control){
    Produto *atual = control->primeiro;
    while (atual != NULL){
        if (comparar_sem_case(nome, atual->nome)==0){
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}
Produto *produto_search_code(uint64_t codigo, ListaProdutos *control){
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
Produto *produto_get_first(ListaProdutos *control){
    return control->primeiro;
}
Produto *produto_get_last(ListaProdutos *control){
    return control->ultimo;
}
Produto *produto_get_next(Produto *produto){
    return produto->prox;
}

//UPDATE
void produto_aumentar_estoque(Produto *produto, int qtd){
    produto->qtd += qtd;
}
bool produto_descontar_estoque(Produto *produto, int qtd){
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
void lista_produtos_liberar(ListaProdutos *control){
    Produto *atual = control->primeiro;
    while (atual!=NULL){
        Produto *prox = atual->prox;
        produto_liberar(atual);
        atual = prox;
    }
    free(control);
}




