#include <stdio.h>
#include <stdlib.h>
#include "lista_produtos.h"
#include "utils.h"
#include "display.h"
#include "interface.h"
#include "pedido.h"
#include "fila.h"

#ifdef _WIN32
#include <windows.h>  
#endif

static void liberar_pedido_void(void *dado){ 
    pedido_liberar((Pedido *)dado); 
}

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

    Fila *fila_pedidos = fila_criar();
    if (fila_pedidos == NULL){
        lista_produtos_liberar(estoque);
        return EXIT_FAILURE;
    }

    do {
        printf("=== VENDA CERTA ===\n\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Cadastrar Pedido\n");
        printf("3. Listar produtos\n");
        printf("4. Ver fila de pedidos\n");
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
                cadastrar_pedido(fila_pedidos, estoque);
                break;
            case 3:
                imprimir_lista_produtos(estoque);
                pausar();
                break;
            case 4:
                imprimir_fila_pedidos(fila_pedidos);
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

    fila_liberar(fila_pedidos, liberar_pedido_void);
    lista_produtos_liberar(estoque);
    return 0;
}
//Para compilar na versão atual: gcc -Wall -Wextra -std=c99 -pedantic -g src/main.c src/utils.c src/lista_produtos.c src/interface.c src/display.c src/pedido.c src/fila.c -o programa.exe
//OBS: NÃO APAGAR -> Mais pra frente utilizar EPOCH como parâmetro na lista de prioridades (Lá na parte 2)
