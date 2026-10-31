#include "interface.h"
#include "lista_produtos.h"
#include "lista_pedidos.h"
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
        if (!ler_string(nome, 100)) return;
        if (strlen(nome) <= 1 || strlen(nome) >= 20){
            printf(RED "\n--O nome deve ter mais do que um e menos do que 20 caracteres--\n" RESET);
            pausar();
            continue;
        }
        break;
    }

    while (1){//quantidade
        printf(WHITE BOLD "\nDigite a quantidade (>= 1): " RESET);
        res = ler_int(&qtd);
        if (res == EOF){
            printf("\nFim de arquivo atingido (EOF)\n");
            pausar();
            return;
        }else if (res == 0){
            printf(RED BOLD "\nErro: scanf da qtd\n" RESET);
            pausar();
            continue;
        }
        if (qtd <= 0){
            printf(RED "\n--Quantidade deve ser um número inteiro positivo--\n" RESET);
            pausar();
            continue;
        }
        break;
    }
    //Verificar se já não existe
    Produto *produto = produto_search_name(nome, control);
    if (produto != NULL){
        printf(RED "\nO produto foi encontrado no depósito!\n" RESET);
        imprimir_produto(produto);
        printf(RED BOLD "\nA quantidade será aumentada e o volume antigo será mantido!\n" RESET);
        pausar();
        produto_aumentar_estoque(produto, qtd);
        return;
    }

    while (1){//volume
        printf(WHITE BOLD "\nDigite o volume que o produto ocupa (1-10): " RESET);
        res = ler_int(&volume);
        if (res == EOF){
            printf("\nFim de arquivo atingido (EOF)\n");
            pausar();
            return;
        }else if (res == 0){
            printf(RED BOLD "\nErro: scanf do volume\n" RESET);
            pausar();
            continue;
        }
        if (volume <= 0 || volume >= 11){
            printf(RED "\n--Volume deve ser um número entre 1 e 10--\n" RESET);
            pausar();
            continue;
        }
        break;
    }

    produto = produto_cadastrar_estoque(nome, qtd, volume, control);
    if (produto == NULL){
        printf(RED BOLD "\nErro: Cadastro do produto (produto_cadastrar_estoque)\n" RESET);
        pausar();
        return;
    }
    printf(GREEN BOLD "\nCadastro do produto realizado com sucesso!\n" RESET);
    imprimir_produto(produto);
    pausar();
    return;
}

void cadastrar_pedido(ListaPedidos *lista, ListaProdutos *estoque){
    if (estoque == NULL || produto_get_first(estoque) == NULL){
        printf(RED "\nNão há produtos cadastrados no estoque, impossível prosseguir com o cadastro do pedido.\n" RESET);
        pausar();
        return;
    }
    printf(WHITE BOLD "\n--Cadastro de Pedido--\n" RESET);
    int res;
    int cod;
    int qtd;
    char destino[128];
    while (1){
        printf(WHITE BOLD "\nInforme o destino do pedido: " RESET);
        if (!ler_string(destino, 128)) return;
        if (strlen(destino) < 2){
            printf(RED "\nO destino deve conter pelo menos 2 caracteres.\n" RESET);
            pausar();
            continue;
        }
        break;
    }
    Pedido *pedido = pedido_criar(destino);
    if (pedido == NULL){
        printf(RED BOLD "\nErro: falha na alocação\n" RESET);
        pausar();
        return;
    }

    while (1){
        while (1){//ID DO PRODUTO
            printf(WHITE "\nDigite o código do produto (0 para cancelar o pedido): " RESET);
            res = ler_int(&cod);
            if (res == EOF){
                printf("\nFim de arquivo atingido (EOF)\n");
                pedido_liberar(pedido);
                pausar();
                return;
            }else if (res == 0){
                printf(RED BOLD "\nErro: scanf do código do produto\n" RESET);
                pausar();
                continue;
            }
            if (cod < 0){
                printf(RED "\nO código não pode ser negativo!\n" RESET);
                pausar();
                continue;
            }
            break;
        }
        if (cod == 0){
            printf(RED "\n--Pedido cancelado.--\n" RESET);
            pedido_liberar(pedido);
            pausar();
            return;
        }
        Produto *produto = produto_search_code(cod, estoque);
        if (produto == NULL){
            printf(RED "\nCódigo não encontrado! Tente novamente.\n" RESET);
            pausar();
            continue;
        }
        while (1){//quantidade do produto
            printf(WHITE "\nDigite a quantidade do produto que deseja: " RESET);
            res = ler_int(&qtd);
            if (res == EOF){
                printf("\nFim de arquivo atingido (EOF)\n");
                pedido_liberar(pedido);
                pausar();
                return;
            }else if (res == 0){
                printf(RED BOLD "\nErro: scanf da qtd do produto\n" RESET);
                pausar();
                continue;
            }
            if (qtd <= 0) {
                printf(RED "\nA quantidade deve ser um número inteiro maior do que 0\n" RESET);
                pausar();
                continue;
            }
            break;
        }
        PedidoItem *item = pedido_item_cadastrar(pedido, produto, qtd);
        if (item == NULL){
            printf(RED BOLD"\nErro: cadastro de item do pedido\n" RESET);
            pedido_liberar(pedido);
            pausar();
            return;
        }
        if (produto_get_qtd(produto) < pedido_item_get_qtd(item)){
            printf(RED "\nA quantidade exigida desse produto excede a disponível em estoque, é possível que o pedido não seja validado!\n" RESET);
            pausar();
        }
        while (1){
            printf(GREEN "\nItem cadastrado com sucesso! Escolha uma opção:\n" RESET);
            printf(WHITE "( 1 ) Cadastrar outro item\n" RESET);
            printf(WHITE "( 2 ) Finalizar pedido\n" RESET);
            int op = -1;
            res = ler_int(&op);
            if (res == EOF){
                printf("\nFim de arquivo atingido (EOF)\n");
                pedido_liberar(pedido);
                return;
            }else if (res == 0){
                printf(RED BOLD "\nErro: scanf da opção\n" RESET);
                pausar();
                continue;
            }
            if (op == 1){
                break;
            }else if (op == 2){
                pedido_cadastrar_lista(lista, pedido);
                printf(WHITE BOLD "\nCadastro do pedido realizado com sucesso!\n" RESET);
                printf(GREEN "\nID do pedido: " RESET);
                printf(WHITE ULINED "%s \n" RESET, pedido_get_code(pedido));
                return;
            }else{
                printf(RED "\nOpção inválida, tente novamente.\n" RESET);
                continue;
            }
        }
    }
    

}