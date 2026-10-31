#include <stdio.h>
#include <stdlib.h>
#include "lista_produtos.h"
#include "utils.h"
#include "display.h"
#include "interface.h"
#include "lista_pedidos.h"

#ifdef _WIN32
#include <windows.h>  
#endif


int main(void){
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
    #endif
    int op = -1;
    int res;
    ListaProdutos *estoque = lista_produto_criar();
    if (estoque == NULL){
        return EXIT_FAILURE;
    }

    ListaPedidos *pedidos = lista_pedidos_criar();
    if (pedidos == NULL){
        lista_produtos_liberar(estoque);
        return EXIT_FAILURE;
    }

    do {
        printf("=== VENDA CERTA ===\n\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Cadastrar Pedido\n");
        printf("3. Listar produtos\n");
        printf("0. Encerrar\n\n");

        printf("Informe sua opcao: ");
        res = ler_int(&op);
        if (res == EOF){
            printf("\nFim de arquivo atingido (EOF)\n");
            break;
        }else if (res == 0){
            printf("\nValor inválido\n");
            pausar();
            continue;
        }
        switch (op) {
            case 1:
                cadastrar_produto(estoque);
                break;
            case 2:
                cadastrar_pedido(pedidos, estoque);
                break;
            case 3:
                imprimir_lista_produtos(estoque);
                pausar();
                break;
            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opcao invalida!\n");
                pausar();
                break;
        }
    } while (op != 0);

    lista_pedidos_liberar(pedidos);
    lista_produtos_liberar(estoque);
    return 0;
}

//OBS: NÃO APAGAR -> Mais pra frente utilizar EPOCH como parâmetro na lista de prioridades (Lá na parte 2)