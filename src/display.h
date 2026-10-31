#ifndef DISPLAY_H
#define DISPLAY_H
#include "lista_produtos.h"
#include "lista_pedidos.h"
#include "fila.h"

void imprimir_produto(Produto *produto); //Função para imprimir um único produto
void imprimir_lista_produtos(ListaProdutos *control); //Função para imprimir toda uma lista
void imprimir_pedido(Pedido *pedido);
void imprimir_fila_pedidos(Fila *fila);

#endif