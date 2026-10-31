#ifndef LISTA_PEDIDOS_H
#define LISTA_PEDIDOS_H
#include "lista_produtos.h"

typedef enum{
    AGUARDANDO,
    SEPARADO
}STATUS;

typedef struct PedidoItem PedidoItem;

typedef struct Pedido Pedido;

typedef struct ListaPedidos ListaPedidos;

//INSERT
PedidoItem *pedido_item_cadastrar(Pedido *pedido, Produto *produto, int qtd);
Pedido *pedido_cadastrar_lista(ListaPedidos *lista, Pedido *pedido);

//CREATE
ListaPedidos *lista_pedidos_criar(void);
Pedido *pedido_criar(const char *destino);
//READ
Pedido *pedido_search_code(ListaPedidos *control, const char *codigo);
PedidoItem *pedido_item_search(Pedido *pedido, Produto *produto);

PedidoItem *pedido_item_get_next(PedidoItem *item);
PedidoItem *pedido_item_get_first(Pedido *pedido);
PedidoItem *pedido_item_get_last(Pedido *pedido);
Pedido *pedido_get_next(Pedido *pedido);
Pedido *pedido_get_first(ListaPedidos *control);
Pedido *pedido_get_last(ListaPedidos *control);
const char *pedido_get_code(Pedido *pedido);
const char *pedido_get_destino(Pedido *pedido);
const char *pedido_get_status(Pedido *pedido);
int pedido_item_get_qtd(PedidoItem *item);
Produto *pedido_item_get_produto(PedidoItem *item);

//UPDATE

//DELETE
void pedido_liberar(Pedido *pedido);
void lista_pedidos_liberar(ListaPedidos *lista);

#endif