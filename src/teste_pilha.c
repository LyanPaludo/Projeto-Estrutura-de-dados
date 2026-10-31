#include "pilha.h"
#include "lista_produtos.h"
#include "display.h"
#include <stdio.h>
#include <assert.h>

int main(void){
    ListaProdutos *lista = lista_produtos_criar();
    Produto *A = produto_cadastrar_estoque("A", 10, 3, lista);
    Produto *B = produto_cadastrar_estoque("B", 10, 5, lista);
    Produto *C = produto_cadastrar_estoque("C", 10, 4, lista);
    Produto *D = produto_cadastrar_estoque("D", 10, 10, lista);
    Pilha *pilha = pilha_criar();
    pilha_empilhar(pilha, A);
    pilha_empilhar(pilha, B);
    pilha_empilhar(pilha, C);
    pilha_empilhar(pilha, D);
    pilha_percorrer(pilha, imprimir_produto);
    pilha_desempilhar(pilha);
    printf("\nDesempilhadinha: \n");
    assert(pilha_volume(pilha) == 12);
    pilha_percorrer(pilha, imprimir_produto);
    pilha_desempilhar(pilha);
    pilha_desempilhar(pilha);
    printf("\nDesempilhadinha: \n");
    pilha_percorrer(pilha, imprimir_produto);
    pilha_desempilhar(pilha);
    printf("\nDesempilhadinha: \n");
    pilha_percorrer(pilha, imprimir_produto);
    printf("\nTeste com POP em pilha vazia: \n");
    pilha_desempilhar(pilha);

    pilha_empilhar(pilha, A);
    pilha_empilhar(pilha, B);
    pilha_empilhar(pilha, C);
    pilha_empilhar(pilha, D);

    printf("\nEmpilhado após esvaziar: \n");
    pilha_percorrer(pilha, imprimir_produto);

    printf("\nEmpilhar um NULL: \n");
    pilha_empilhar(pilha, NULL);
    pilha_percorrer(pilha, imprimir_produto);

    pilha_liberar(pilha);
    lista_produtos_liberar(lista);

    return 0;
}