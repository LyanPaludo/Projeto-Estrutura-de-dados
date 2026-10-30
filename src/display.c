#include "display.h"
#include "lista_produtos.h"
#include "utils.h"
#include <string.h>
#include <stdio.h>
#include <inttypes.h>

// https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
#define RESET "\x1b[0m"     //RESET
#define RED "\x1b[31m"      // VERMELHO
#define GREEN "\x1b[32m"    // VERDE
#define WHITE "\x1b[37m"    // BRANCO
#define BOLD "\x1b[1m"      //  NEGRITO
#define ULINED "\x1b[4m"    //  SUBLINHADO

void imprimir_produto(Produto *produto){
    if (produto == NULL){
        printf(RED BOLD "\nProduto inexistente!\n" RESET);
        return;
    }
    printf(RESET WHITE BOLD "-----------------------------\n");
    printf(RESET GREEN BOLD "ID: " RESET WHITE "%"PRIu64"\n", produto->codigo);
    printf(RESET GREEN BOLD "Nome: " RESET WHITE "%s\n", produto->nome);
    printf(RESET GREEN BOLD "Qtd. em estoque: " RESET WHITE "%d\n", produto->qtd);
    printf(RESET GREEN BOLD "Vol. unitário: " RESET WHITE "%d\n", produto->volume);
    printf(RESET WHITE BOLD "-----------------------------\n"RESET);
}//imprimir um produto

void imprimir_lista(Controle *control){
    if (control == NULL || control->primeiro == NULL){
        printf(RED BOLD "\nLISTA VAZIA!\n" RESET);
        pausar();
        return;
    }
    Produto *atual = control->primeiro;
    printf(RESET RED BOLD ULINED   "Super imprimidor de produto:\n");
    while (atual != NULL){
        imprimir_produto(atual);
        atual = atual->prox;
    }
    printf(RESET RED BOLD ULINED  "End\n"RESET);
    pausar();
}//imprimir toda uma lista de produtos