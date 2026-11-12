#ifndef DISPLAY_H
#define DISPLAY_H
#include "lista_produtos.h"
#include "pedido.h"
#include "fila.h"
#include "pacote.h"
#include "fila_prioridade.h"
#include "caminhao.h"
#include "expedicao.h"

void imprimir_produto(Produto *produto);              //Função para imprimir um único produto do estoque

void imprimir_lista_produtos(ListaProdutos *control); //Função para imprimir todo o estoque

void imprimir_pedido(Pedido *pedido);                 //Função para imprimir um único pedido

void imprimir_fila_pedidos(Fila *pedidos);            //Função para imprimir toda a fila de pedidos

void imprimir_pacote(Pacote *pacote);                 //Função para imprimir um único pacote

void imprimir_fila_pacotes(FilaPrioridade *pacotes);            //Função para imprimir toda a fila de pacotes

void imprimir_caminhao(Caminhao *cmn);

void imprimir_docas(Expedicao *exp);

void imprimir_historico(Expedicao *exp);

#endif