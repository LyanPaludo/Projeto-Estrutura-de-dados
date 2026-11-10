#include "lista_produtos.h"
#include "separacao.h" 
#include "pacote.h"
#include <stdbool.h>
#include "utils.h"
#include "constantes.h"

static bool estoque_suficiente(Pedido *pedido){
    if (pedido == NULL){
        return false;
    }
    PedidoItem *item = pedido_item_get_first(pedido);
    Produto *produto;
    while (item != NULL){
        produto = pedido_item_get_produto(item);
        if (produto_get_qtd(produto) < pedido_item_get_qtd(item)){
            return false;
        }
        item = pedido_item_get_next(item);
    }
    return true;
}//Verifica se tem estoque suficiente para atender todo o pedido

static bool montar_pacotes(Pedido *pedido, FilaPrioridade *pacotes, int prioridade){
    int n = 1;
    PedidoItem *item = pedido_item_get_first(pedido);
    Pacote *pack = pacote_criar(pedido_get_code(pedido), n, pedido_get_destino(pedido), prioridade);
    if (pack == NULL){
        return false;
    }
    while (item != NULL){
        for (int i=0; i<(pedido_item_get_qtd(item)); i++){
            ResultadoPacote r = pacote_adicionar_produto(pack, pedido_item_get_produto(item));
            if (r == PACOTE_ERRO){
                pacote_liberar(pack);
                return false;
            }
            if (r == PACOTE_NAO_COUBE){
                if (pacote_get_qtd(pack) == 0){
                    pacote_liberar(pack);
                    return false;
                }
                if (!fila_prioridade_enfileirar(pacotes, pack, prioridade)){
                    pacote_liberar(pack);
                    return false;
                }
                n++;
                pack = pacote_criar(pedido_get_code(pedido), n, pedido_get_destino(pedido), prioridade);
                if (pack == NULL){
                    return false;
                }
                if (pacote_adicionar_produto(pack, pedido_item_get_produto(item)) != PACOTE_ADICIONADO){
                    pacote_liberar(pack);
                    return false;
                }
            }
        }
        item = pedido_item_get_next(item);
    }
    if (!fila_prioridade_enfileirar(pacotes, pack, prioridade)){
        pacote_liberar(pack);
        return false;
    }
    return true;
}

ResultadoSeparacao separar_prox_pedido(Fila *pedidos, FilaPrioridade *pacotes, Pedido **separado){
    *separado = NULL;
    Pedido *pedido = fila_espiar_frente(pedidos);
    if (pedido == NULL){
        return SEPARACAO_FILA_VAZIA;
    }
    if (!estoque_suficiente(pedido)){
        return SEPARACAO_SEM_ESTOQUE;
    }
    pedido = fila_desenfileirar(pedidos);
    PedidoItem *item = pedido_item_get_first(pedido);
    while (item != NULL){
        if (!produto_descontar_estoque(pedido_item_get_produto(item), pedido_item_get_qtd(item))){
            pedido_liberar(pedido);
            return SEPARACAO_ERRO;
        }
        item = pedido_item_get_next(item);
    }
    int prioridade = sortear(PRIORIDADE_QTD);
    if (!montar_pacotes(pedido, pacotes, prioridade)){
        pedido_liberar(pedido);
        return SEPARACAO_ERRO;
    }
    pedido_marcar_separado(pedido);
    *separado = pedido;
    return SEPARACAO_OK;
}
