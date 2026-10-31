#ifndef PEDIDO_H
#define PEDIDO_H
#include "lista_produtos.h"

typedef enum{
    AGUARDANDO,
    SEPARADO
}STATUS;

typedef struct PedidoItem PedidoItem;

typedef struct Pedido Pedido;

//INSERT
PedidoItem *pedido_item_cadastrar(Pedido *pedido, Produto *produto, int qtd);

//CREATE
Pedido *pedido_criar(const char *destino);
//READ
PedidoItem *pedido_item_search(Pedido *pedido, Produto *produto);

PedidoItem *pedido_item_get_next(PedidoItem *item);
PedidoItem *pedido_item_get_first(Pedido *pedido);
PedidoItem *pedido_item_get_last(Pedido *pedido);
const char *pedido_get_code(Pedido *pedido);
const char *pedido_get_destino(Pedido *pedido);
const char *pedido_get_status(Pedido *pedido);
int pedido_item_get_qtd(PedidoItem *item);
Produto *pedido_item_get_produto(PedidoItem *item);

//UPDATE

//DELETE
void pedido_liberar(Pedido *pedido);

#endif