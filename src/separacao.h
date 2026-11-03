#ifndef SEPARACAO_H
#define SEPARACAO_H
#include "fila.h"
#include "pedido.h"

typedef enum{
    SEPARACAO_OK,
    SEPARACAO_FILA_VAZIA,
    SEPARACAO_SEM_ESTOQUE,
    SEPARACAO_ERRO
}ResultadoSeparacao;

ResultadoSeparacao separar_prox_pedido(Fila *pedidos, Fila *pacotes, Pedido **separado);

#endif