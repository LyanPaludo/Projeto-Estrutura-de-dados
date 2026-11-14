#include "display.h"
#include "cores.h"
#include "constantes.h"
#include <stdio.h>
#include <inttypes.h>

void imprimir_produto(Produto *produto){
    if (produto == NULL){
        printf(RED BOLD "\nProduto inexistente!\n" RESET);
        return;
    }   
    printf(RESET WHITE BOLD "-----------------------------\n");
    printf(RESET GREEN BOLD "ID: " RESET WHITE "%"PRIu64"\n",       produto_get_code(produto));
    printf(RESET GREEN BOLD "Nome: " RESET WHITE "%s\n",            produto_get_name(produto));
    printf(RESET GREEN BOLD "Qtd. em estoque: " RESET WHITE "%d\n", produto_get_qtd(produto));
    printf(RESET GREEN BOLD "Vol. unitário: " RESET WHITE "%d\n",   produto_get_volume(produto));
    printf(RESET WHITE BOLD "-----------------------------\n"RESET);
}

void imprimir_catalogo(Catalogo *estoque){
    if (catalogo_vazio(estoque)){
        printf(RED BOLD "\nLISTA VAZIA!\n" RESET);
        return;
    }
    printf(RESET RED BOLD ULINED   "\nSuper imprimidor de produto:\n");
    catalogo_percorrer(estoque, imprimir_produto);
    printf(RESET RED BOLD ULINED  "\nEnd\n"RESET);
}

void imprimir_pedido(Pedido *pedido){
    if (pedido == NULL){
        printf(RED "\nPedido vazio\n" RESET);
        return;
    }
    printf(GREEN BOLD "\n-- PEDIDO %s --\n" RESET, pedido_get_code(pedido));
    printf(GREEN "\nDestino: " RESET WHITE "%s" RESET, pedido_get_destino(pedido));
    printf(GREEN "\nStatus: " RESET WHITE "%s\n" RESET, pedido_get_status(pedido));
    PedidoItem *atual = pedido_item_get_first(pedido);
    while (atual != NULL){
        Produto *produto = pedido_item_get_produto(atual);
        printf(GREEN "\nItem: " RESET WHITE "%s" RESET, produto_get_name(produto));
        printf(GREEN "\nQuantidade: " RESET WHITE "%d\n" RESET, pedido_item_get_qtd(atual));
        atual = pedido_item_get_next(atual);
    }
}

static void visitar_pedido(void *dado){
    imprimir_pedido((Pedido *)dado);
}

void imprimir_fila_pedidos(Fila *pedidos){
    if (fila_espiar_frente(pedidos) == NULL){
        printf(RED "\n--A Fila está vazia!--\n" RESET);
        return;
    }
    printf(RED ULINED "\n--Super imprimidor de pedidos--\n" RESET);
    fila_percorrer(pedidos, visitar_pedido);
    printf(RED ULINED "\n--Fim da Impressão--\n" RESET);
}

static void imprimir_item_pacote(Produto *produto){
    if (produto == NULL){
        printf(RED "\nProduto inexistente\n" RESET);
        return;
    }
    printf(GREEN "\n   -> Item: " RESET WHITE "%s" RESET, produto_get_name(produto));
}

static const char *nome_prioridade(int p){
    switch (p){
        case PRIORIDADE_EXPRESSA:
            return "Expressa";
        case PRIORIDADE_RAPIDA:
            return "Rápida";
        case PRIORIDADE_NORMAL:
            return "Normal";
        default:
            return "Desconhecida";
    }
}

void imprimir_pacote(Pacote *pacote){
    if (pacote == NULL){
        printf(RED BOLD "\nPacote inexistente\n" RESET);
        return;
    }
    printf(WHITE BOLD "\n - PACOTE - \n" RESET);
    printf(GREEN "\nPrioridade: " RESET WHITE ULINED "%s" RESET, nome_prioridade(pacote_get_prioridade(pacote)));
    printf(GREEN "\nCod. pacote: " RESET WHITE "%s" RESET, pacote_get_codigo(pacote));
    printf(GREEN "\nDest. pacote: " RESET WHITE "%s" RESET, pacote_get_destino(pacote));
    printf(GREEN "\nVol. pacote: " RESET WHITE "[ %d / %d ]" RESET, pacote_get_volume(pacote), PACOTE_CAPACIDADE);
    printf(GREEN "\nQtd. unidades: " RESET WHITE "%d" RESET, pacote_get_qtd(pacote));
    pacote_percorrer(pacote, imprimir_item_pacote);
    printf("\n");
}

static void visitar_pacote(void *dado){
    imprimir_pacote((Pacote *)dado);
}

void imprimir_fila_pacotes(FilaPrioridade *pacotes){
    if (fila_prioridade_espiar_frente(pacotes) == NULL){
        printf(RED "\n--A Fila está vazia!--\n" RESET);
        return;
    }
    printf(RED ULINED "\n--Super imprimidor de pacotes (Ordem de expedição)--\n" RESET);
    fila_prioridade_percorrer(pacotes, visitar_pacote);
    printf(RED ULINED "\n--Fim da Impressão--\n" RESET);
}

static void visitar_pacote_resumo(void *dado){
    Pacote *pacote = (Pacote *)dado;
    printf(WHITE BOLD "\n-> PACOTE:" RESET);
    printf(GREEN "\n     Prioridade: " RESET WHITE ULINED "%s" RESET, nome_prioridade(pacote_get_prioridade(pacote)));
    printf(GREEN "\n     Cod. pacote: " RESET WHITE "%s" RESET, pacote_get_codigo(pacote));
    printf(GREEN "\n     Dest. pacote: " RESET WHITE "%s" RESET, pacote_get_destino(pacote));
    printf(GREEN "\n     Vol. pacote: " RESET WHITE "[ %d / %d ]" RESET, pacote_get_volume(pacote), PACOTE_CAPACIDADE);
}

void imprimir_caminhao(Caminhao *cmn){
    if (cmn == NULL){
        printf(RED "\nCaminhão inexistente!\n" RESET);
        return;
    }
    printf(GREEN BOLD "\n--CAMINHÃO--\n" RESET);
    printf(GREEN "\nNúmero: " RESET WHITE "%d" RESET, caminhao_get_numero(cmn));
    printf(GREEN "\nCapacidade: " RESET WHITE "[ %d / %d ]" RESET, caminhao_get_usado(cmn), caminhao_get_capacidade(cmn));
    printf(GREEN "\nQtd. Pacotes: " RESET WHITE "%d" RESET, caminhao_get_qtd(cmn));
    caminhao_percorrer(cmn, visitar_pacote_resumo);
    printf("\n");
}

void imprimir_docas(Expedicao *exp){
    printf(RED ULINED "\n--Imprimidor de docas--\n" RESET);
    for (int i=0; i<NUM_DOCAS; i++){
        printf(GREEN BOLD "\nDoca %d" RESET, i+1);
        imprimir_caminhao(expedicao_get_doca(exp, i));
    }
    printf(RED ULINED "\n--Fim do imprimidor de docas--\n" RESET);
}

static void visitar_caminhao(void *dado){
    imprimir_caminhao((Caminhao *)dado);
}

void imprimir_historico(Expedicao *exp){
    if (exp == NULL || expedicao_historico_tamanho(exp) == 0){
        printf(RED "\nNenhum caminhão saiu!\n" RESET);
        return;
    }
    printf(RED ULINED "\n--Super imprimidor de histórico--\n" RESET);
    expedicao_percorrer_historico(exp, visitar_caminhao);
    printf(RED ULINED "\n--Fim do Imprimidor de Históricos--\n" RESET);
}