#include "display.h"
#include "lista_produtos.h"
#include "utils.h"
#include "cores.h"
#include <stdio.h>
#include <inttypes.h>

void imprimir_produto(Produto *produto){
    if (produto == NULL){
        printf(RED BOLD "\nProduto inexistente!\n" RESET);
        return;
    }   
    printf(RESET WHITE BOLD "-----------------------------\n");
    printf(RESET GREEN BOLD "ID: " RESET WHITE "%"PRIu64"\n",       getCode(produto));
    printf(RESET GREEN BOLD "Nome: " RESET WHITE "%s\n",            getName(produto));
    printf(RESET GREEN BOLD "Qtd. em estoque: " RESET WHITE "%d\n", getQtd(produto));
    printf(RESET GREEN BOLD "Vol. unitário: " RESET WHITE "%d\n",   getVolume(produto));
    printf(RESET WHITE BOLD "-----------------------------\n"RESET);
}//imprimir um produto

void imprimir_lista(ListaProdutos *control){
    if (control == NULL){
        printf(RED BOLD "\nLISTA VAZIA!\n" RESET);
        pausar();
        return;
    }
    Produto *atual = getFirst(control);
    printf(RESET RED BOLD ULINED   "Super imprimidor de produto:\n");
    while (atual != NULL){
        imprimir_produto(atual);
        atual = getNext(atual);
    }
    printf(RESET RED BOLD ULINED  "End\n"RESET);
    pausar();
}//imprimir toda uma lista de produtos