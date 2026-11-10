#ifndef INTERFACE_H
#define INTERFACE_H
#include "lista_produtos.h"
#include "fila.h"
void cadastrar_produto(ListaProdutos *control);
void cadastrar_pedido(Fila *fila_pedidos, ListaProdutos *estoque);
void separar_pedido(Fila *pedidos, Fila *pacotes);
//secret
void secret_function(ListaProdutos *estoque, Fila *pedidos);
#endif