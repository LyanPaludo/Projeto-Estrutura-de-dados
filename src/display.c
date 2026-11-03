#include "display.h"
#include "cores.h"
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
}//imprimir um produto

void imprimir_lista_produtos(ListaProdutos *control){
    if (control == NULL || produto_get_first(control) == NULL){
        printf(RED BOLD "\nLISTA VAZIA!\n" RESET);
        return;
    }
    Produto *atual = produto_get_first(control);
    printf(RESET RED BOLD ULINED   "Super imprimidor de produto:\n");
    while (atual != NULL){
        imprimir_produto(atual);
        atual = produto_get_next(atual);
    }
    printf(RESET RED BOLD ULINED  "End\n"RESET);
}//imprimir toda uma lista de produtos

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

void imprimir_pacote(Pacote *pacote){
    if (pacote == NULL){
        printf(RED BOLD "\nPacote inexistente\n" RESET);
        return;
    }
    printf(WHITE BOLD "\n - PACOTE - \n" RESET);
    printf(GREEN "\nCod. pacote: " RESET WHITE "%s" RESET, pacote_get_codigo(pacote));
    printf(GREEN "\nDest. pacote: " RESET WHITE "%s" RESET, pacote_get_destino(pacote));
    printf(GREEN "\nVol. pacote: " RESET WHITE "%d" RESET, pacote_get_volume(pacote));
    printf(GREEN "\nQtd. unidades: " RESET WHITE "%d" RESET, pacote_get_qtd(pacote));
    pacote_percorrer(pacote, imprimir_item_pacote);
    printf("\n");
}

static void visitar_pacote(void *dado){
    imprimir_pacote((Pacote *)dado);
}

void imprimir_fila_pacotes(Fila *pacotes){
    if (fila_espiar_frente(pacotes) == NULL){
        printf(RED "\n--A Fila está vazia!--\n" RESET);
        return;
    }
    printf(RED ULINED "\n--Super imprimidor de pacotes--\n" RESET);
    fila_percorrer(pacotes, visitar_pacote);
    printf(RED ULINED "\n--Fim da Impressão--\n" RESET);
}