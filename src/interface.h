#ifndef INTERFACE_H
#define INTERFACE_H
#include "catalogo.h"
#include "fila.h"
#include "fila_prioridade.h"
#include "expedicao.h"

void cadastrar_produto(Catalogo *control);
void cadastrar_pedido(Fila *fila_pedidos, Catalogo *estoque);
void separar_pedido(Fila *pedidos, FilaPrioridade *pacotes);
void expedir_pacotes(Expedicao *exp, FilaPrioridade *pacotes);
void remover_produto(Catalogo *estoque);
//secret
void secret_function(Catalogo *estoque, Fila *pedidos, FilaPrioridade *pacotes);
#endif