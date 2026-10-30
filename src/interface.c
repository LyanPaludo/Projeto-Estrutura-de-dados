#include "interface.h"
#include "lista_produtos.h"
#include "utils.h"
#include "display.h"
#include "cores.h"
#include <string.h>
#include <stdio.h>

void cadastrar_produto(ListaProdutos *control){
    char nome[100];
    int qtd;
    int volume;
    int res;
    while (1){
        printf(WHITE "Digite o nome do produto que desejas cadastrar: " RESET);
        ler_string(nome, 100);
        if (strlen(nome) <= 1 || strlen(nome) >= 20){
            printf(RED "\n--O nome deve ter mais do que um e menos do que 20 dígitos--\n" RESET);
            pausar();
            continue;
        }
        break;
    }

    while (1){//quantidade
        printf(WHITE BOLD "\nDigite a quantidade (>= 1): " RESET);
        res = scanf("%d", &qtd);
        if (res!=1){
            if (res == EOF) {
                printf("\nFim de arquivo atingido (EOF)\n");
                return;
            }
            printf(RED BOLD "\nErro: scanf da qtd\n" RESET);
            limpar_buffer();
            pausar();
            continue;
        }
        limpar_buffer();
        if (qtd <= 0){
            printf(RED "\n--Quantidade deve ser um número inteiro positivo--\n" RESET);
            pausar();
            continue;
        }
        break;
    }
    //Verificar se já não existe
    Produto *produto = pesquisar_por_nome(nome, control);
    if (produto != NULL){
        printf(RED "\nO produto foi encontrado no depósito!\n" RESET);
        imprimir_produto(produto);
        printf(RED BOLD "\nA quantidade será aumentada e o volume antigo será mantido!\n" RESET);
        pausar();
        aumentar_estoque(produto, qtd);
        return;
    }

    while (1){//volume
        printf(WHITE BOLD "\nDigite o volume que o produto ocupa (1-10): " RESET);
        res = scanf("%d", &volume);
        if (res!=1){
            if (res == EOF) {
                printf("\nFim de arquivo atingido (EOF)\n");
                return;
            }
            printf(RED BOLD "\nErro: scanf do volume\n" RESET);
            limpar_buffer();
            pausar();
            continue;
        }
        limpar_buffer();
        if (volume <= 0 || volume >= 11){
            printf(RED "\n--Volume deve ser um número entre 1 e 10--\n" RESET);
            pausar();
            continue;
        }
        break;
    }

    produto = cad_prod_sys(nome, qtd, volume, control);
    if (produto == NULL){
        printf(RED BOLD "\nErro: Cadastro do produto (cad_prod_sys)\n" RESET);
        pausar();
        return;
    }
    printf(GREEN BOLD "\nCadastro do produto realizado com sucesso!\n" RESET);
    imprimir_produto(produto);
    pausar();
    return;
}