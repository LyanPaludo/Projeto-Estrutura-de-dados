#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Produto{
    int codigo;
    char *nome;
    int qtd;
    int volume;
}Produto;

typedef struct No{
    Produto produto;
    struct No *prox;
}No;

typedef struct Controle{
    No *primeiro;
    No *ultimo;
}Controle;

void cadatrar_produto(Controle *lista){
    printf("\n-- Digite o nome do produto: ");
    Produto *produto;
    char nome[100];
    fgets(nome, 100, stdin);
    produto = pesquisar_por_nome(nome, lista);
    if (produto!=NULL){
        printf("\nNosso sistema encontrou um produto com esse nome:\n");
        imprimir_produto(produto);
        while (1){
            printf("\nEscolha uma ação:\n");
            printf("( 1 ) Aumentar quantidade do produto\n");
            printf("( 2 ) Sair\n");
            int opcao;
            scanf("%d", &opcao);
            switch (opcao){
                case 1:
                    aumentar_quantidade(produto);
                    break;
                case 2:
                    break;
                default:
                    printf("\n!!!!!!!!!!!!!!\n");
                    printf("\nOpção inválida\n");
                    printf("\n!!!!!!!!!!!!!!\n");
                    break;
            }
        }
    }else{
        return;
    }
}
// FUNÇÃO PARA IMPRIMIR PRODUTO, COM CORZINHA
// cores e reset
// https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
#define RESET "\x1b[0m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define WHITE "\x1b[37m"
//formatação de texto
#define BOLD "\x1b[1m"
#define ULINED "\x1b[4m"

void imprimir_produto(Produto produto){
    printf(RESET WHITE BOLD "-----------------------------\n");
    printf(RESET GREEN BOLD "ID: " RESET WHITE "%d\n", produto.codigo);
    printf(RESET GREEN BOLD "Nome: " RESET WHITE "%s\n", produto.nome);
    printf(RESET GREEN BOLD "Qtd. em estoque: " RESET WHITE "%d\n", produto.qtd);
    printf(RESET GREEN BOLD "Vol. no armazém: " RESET WHITE "%d\n", produto.volume);
    printf(RESET WHITE BOLD "-----------------------------\n");
}

void imprimir_lista(Controle *control){
    No *atual = control->primeiro;
    printf(RESET RED BOLD ULINED   "Super imprimidor de produto:\n");
    while (atual->prox != NULL){
        imprimir_produto(atual->produto);
    }
    printf(RESET RED BOLD ULINED  "End\n");
}