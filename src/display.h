#ifndef DISPLAY_H
#define DISPLAY_H
#include "catalogo.h"
#include "pedido.h"
#include "fila.h"
#include "pacote.h"
#include "fila_prioridade.h"
#include "caminhao.h"
#include "expedicao.h"

void imprimir_produto(Produto *produto);              //Função para imprimir um único produto do catalogo

void imprimir_catalogo(Catalogo *control);            //Função para imprimir todo o catalogo

void imprimir_pedido(Pedido *pedido);                 //Função para imprimir um único pedido

void imprimir_fila_pedidos(Fila *pedidos);            //Função para imprimir toda a fila de pedidos

void imprimir_pacote(Pacote *pacote);                 //Função para imprimir um único pacote

void imprimir_fila_pacotes(FilaPrioridade *pacotes);  //Função para imprimir toda a fila de pacotes

void imprimir_caminhao(Caminhao *cmn);                //Função para imprimir um caminhão e seus pacotes

void imprimir_docas(Expedicao *exp);                  //Função para imprimir todas as docas e seus caminhões   

void imprimir_historico(Expedicao *exp);              //Função para imprimir todo o histórico de caminhões já enviados

#endif