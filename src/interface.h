#ifndef INTERFACE_H
#define INTERFACE_H
#include "lista_produtos.h"
#include "fila.h"

void cadastrar_produto(ListaProdutos *control);
void cadastrar_pedido(Fila *fila_pedidos, ListaProdutos *estoque);

#endif