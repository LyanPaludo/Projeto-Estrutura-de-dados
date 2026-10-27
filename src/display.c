#include "display.h"
#include "lista_produtos.h"
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
        pausar();
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

void cadastrar_produto(Controle *control){
    char nome[100];
    int qtd;
    int volume;
    while (1){
        printf(WHITE "Digite o nome do produto que desejas cadastrar: " RESET);
        if (fgets(nome, sizeof(nome), stdin) != NULL){
            nome[strcspn(nome, "\n")] = '\0';
        }else{
            printf(RED BOLD "\nErro: Nome não reconhecido em cadastrar produto!\n" RESET);
            pausar();
            return;
        }

        printf(WHITE BOLD "\nDigite a quantidade (>= 1 | <= 0 para cancelar): " RESET);
        if (scanf("%d", &qtd)!=1){
            printf(RED BOLD "\nErro: scanf da qtd\n" RESET);
            limpar_buffer();
            pausar();
            continue;
        }
        limpar_buffer();
        if (qtd <= 0){
            free(nome);
            return;
        }

        printf(WHITE BOLD "\nDigite o volume que o produto ocupa (1-10 | <= 0 ou >= 11 para cancelar): " RESET);
        if (scanf("%d", &volume)!=1){
            printf(RED BOLD "\nErro: scanf do volume\n" RESET);
            limpar_buffer();
            pausar();
            continue;
        }
        limpar_buffer();
        if (volume <= 0 || volume >= 11){
            free(nome);
            return;
        }
        Produto *produto = cad_prod_sys(nome, qtd, volume, control);
        if (produto == NULL){
            printf(RED BOLD "\nErro: Cadastro do produto (cad_prod_sys)\n" RESET);
            free(produto);
            free(nome);
            pausar();
            return;
        }
        printf(GREEN BOLD "\nCadastro do produto realizado com sucesso!\n" RESET);
        imprimir_produto(produto);
        pausar();
        return;
    }
}