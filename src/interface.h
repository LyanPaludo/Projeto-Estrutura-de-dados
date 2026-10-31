#ifndef INTERFACE_H
#define INTERFACE_H
#include "lista_produtos.h"
#include "lista_pedidos.h"

void cadastrar_produto(ListaProdutos *control);
void cadastrar_pedido(ListaPedidos *lista, ListaProdutos *estoque);

#endif