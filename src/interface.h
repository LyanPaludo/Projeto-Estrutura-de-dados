#ifndef INTERFACE_H
#define INTERFACE_H
#include "lista_produtos.h"
#include "fila.h"
#include "fila_prioridade.h"
#include "expedicao.h"

void cadastrar_produto(ListaProdutos *control);
void cadastrar_pedido(Fila *fila_pedidos, ListaProdutos *estoque);
void separar_pedido(Fila *pedidos, FilaPrioridade *pacotes);
void expedir_pacotes(Expedicao *exp, FilaPrioridade *pacotes);

//secret
void secret_function(ListaProdutos *estoque, Fila *pedidos);
#endif