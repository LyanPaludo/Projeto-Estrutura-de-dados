#include "lista_produtos.h"
#include "lista_pedidos.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

struct PedidoItem{
    Produto *produto;
    int qtd;
    PedidoItem *prox;
};

struct Pedido{
    char *codigo;
    char destino[128];
    STATUS stat;
    PedidoItem *primeiro;
    PedidoItem *ultimo;
    Pedido *prox;
};

struct ListaPedidos{
    Pedido *primeiro;
    Pedido *ultimo;
};
    
//GERAR CÓDIGO DO PEDIDO
static char* pedido_gerar_cod(void) {
    static uint64_t contador_cod = 1;
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "PED%" PRIu64, contador_cod++);
    char *codigo = (char *) malloc(strlen(buffer) + 1);
    if (codigo != NULL) {
        strcpy(codigo, buffer);
    }
    return codigo;
}

//INSERT
PedidoItem *pedido_item_cadastrar(Pedido *pedido, Produto *produto, int qtd){
    PedidoItem *item = pedido_item_search(pedido, produto);
    if (item != NULL){
        item->qtd += qtd;
        return item;
    }
    item = (PedidoItem *) malloc(sizeof(PedidoItem));
    if (item == NULL){
        return NULL;
    }
    item->produto = produto;
    item->qtd = qtd;
    item->prox = NULL;
    if (pedido->primeiro == NULL){
        pedido->primeiro = item;
        pedido->ultimo   = item;
    }else{
        pedido->ultimo->prox = item;
        pedido->ultimo       = item;
    }   
    return item;
}

Pedido *pedido_cadastrar_lista(ListaPedidos *lista, Pedido *pedido){
    if (lista->primeiro == NULL){
        lista->primeiro = pedido;
        lista->ultimo   = pedido;
    }else{
        lista->ultimo->prox = pedido;
        lista->ultimo = pedido;
    }
    return pedido;
}

//CREATE
ListaPedidos *lista_pedidos_criar(void){
    ListaPedidos *lista  = (ListaPedidos *) malloc(sizeof(ListaPedidos));
    if (lista == NULL){
        return NULL;
    }
    lista->primeiro   = NULL;
    lista->ultimo     = NULL;
    return lista;
}

Pedido *pedido_criar(const char *destino){
    Pedido *pedido = (Pedido *) malloc(sizeof(Pedido));
    if (pedido == NULL){
        return NULL;
    }
    pedido->primeiro = NULL;
    pedido->ultimo   = NULL;
    pedido->prox     = NULL;
    
    strncpy(pedido->destino, destino, sizeof(pedido->destino) - 1);
    pedido->destino[sizeof(pedido->destino) - 1] = '\0';
    
    pedido->codigo = pedido_gerar_cod();
    if (pedido->codigo == NULL){
        free(pedido);
        return NULL;
    }
    pedido->stat = AGUARDANDO;
    return pedido;
}

//READ
Pedido *pedido_search_code(ListaPedidos *control, const char *codigo){
    Pedido *atual = control->primeiro;
    while (atual != NULL){
        if (strcmp(atual->codigo, codigo) == 0){
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

PedidoItem *pedido_item_search(Pedido *pedido, Produto *produto){
    PedidoItem *atual = pedido->primeiro;
    while (atual != NULL){
        if (atual->produto == produto){
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}



PedidoItem *pedido_item_get_next(PedidoItem *item){
    return item->prox;
}
PedidoItem *pedido_item_get_first(Pedido *pedido){
    return pedido->primeiro;
}
PedidoItem *pedido_item_get_last(Pedido *pedido){
    return pedido->ultimo;
}
Pedido *pedido_get_next(Pedido *pedido){
    return pedido->prox;
}
Pedido *pedido_get_first(ListaPedidos *control){
    return control->primeiro;
}
Pedido *pedido_get_last(ListaPedidos *control){
    return control->ultimo;
}

const char *pedido_get_code(Pedido *pedido){
    return pedido->codigo;
}
const char *pedido_get_destino(Pedido *pedido){
    return pedido->destino;
}
const char *pedido_get_status(Pedido *pedido){
    if (pedido->stat == AGUARDANDO){
        return "AGUARDANDO";
    }else{
        return "SEPARADO";
    }
}

int pedido_item_get_qtd(PedidoItem *item){
    return item->qtd;
}
Produto *pedido_item_get_produto(PedidoItem *item){
    return item->produto;
}

//UPDATE

//DELETE
static void pedido_item_liberar(PedidoItem *item){
    free(item);
}

void pedido_liberar(Pedido *pedido){
    PedidoItem *atual = pedido->primeiro;
    while (atual != NULL){
        PedidoItem *prox = atual->prox;
        pedido_item_liberar(atual);
        atual = prox;
    }
    free(pedido->codigo);
    free(pedido);
}

void lista_pedidos_liberar(ListaPedidos *lista){
    Pedido *atual = lista->primeiro;
    while (atual != NULL){
        Pedido *prox = atual->prox;
        pedido_liberar(atual);
        atual = prox;
    }
    free(lista);
}




