#include <stdio.h>
#include <stdlib.h>
#include "catalogo.h"
#include "utils.h"
#include "display.h"
#include "interface.h"
#include "pedido.h"
#include "fila.h"
#include "separacao.h"
#include "pacote.h"
#include "fila_prioridade.h"
#include "expedicao.h"
#include "cores.h"

#ifdef _WIN32
#include <windows.h>  
#endif

static void liberar_pedido_void(void *dado){ 
    pedido_liberar((Pedido *)dado); 
}
static void liberar_pacote_void(void *dado){ 
    pacote_liberar((Pacote *)dado); 
}

int main(void){
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
    #endif
    iniciar_sorteio();
    int op = -1;
    int res;
    Catalogo *estoque = catalogo_criar();
    if (estoque == NULL){
        return EXIT_FAILURE;
    }

    Fila *fila_pedidos = fila_criar();
    if (fila_pedidos == NULL){
        catalogo_liberar(estoque);
        return EXIT_FAILURE;
    }

    FilaPrioridade *fila_pacotes = fila_prioridade_criar();
    if (fila_pacotes == NULL){
        catalogo_liberar(estoque);
        fila_liberar(fila_pedidos, liberar_pedido_void);
        return EXIT_FAILURE;
    }

    Expedicao *exp = expedicao_criar();
    if (exp == NULL){
        catalogo_liberar(estoque);
        fila_liberar(fila_pedidos, liberar_pedido_void);
        fila_prioridade_liberar(fila_pacotes, liberar_pacote_void);
        return EXIT_FAILURE;
    }

    do {
        printf(GREEN BOLD "=== VENDA CERTA ===\n\n" RESET);
        printf(WHITE BOLD "1. Cadastrar Produto\n" RESET);
        printf(WHITE BOLD "2. Cadastrar Pedido\n" RESET);
        printf(WHITE BOLD "3. Listar produtos\n" RESET);
        printf(WHITE BOLD "4. Ver fila de pedidos\n" RESET);
        printf(WHITE BOLD "5. Separar próximo pedido\n" RESET);
        printf(WHITE BOLD "6. Ver pacotes prontos\n" RESET);
        printf(WHITE BOLD "7. Expedir pacotes\n" RESET);
        printf(WHITE BOLD "8. Ver docas\n" RESET);
        printf(WHITE BOLD "9. Ver caminhões despachados\n" RESET);
        printf(WHITE BOLD "10. Remover produto\n" RESET);
        printf(RED "0. Encerrar\n\n" RESET);

        printf("Informe sua opção: ");
        res = ler_int(&op);
        if (res == EOF){
            printf(RED BOLD "\nFim de arquivo atingido (EOF)\n" RESET);
            break;
        }else if (res == 0){
            printf(RED "\nValor inválido\n" RESET);
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
                imprimir_catalogo(estoque);
                pausar();
                break;
            case 4:
                imprimir_fila_pedidos(fila_pedidos);
                pausar();
                break;
            case 5:
                separar_pedido(fila_pedidos, fila_pacotes);
                pausar();
                break;
            case 6:
                imprimir_fila_pacotes(fila_pacotes);
                pausar();
                break;
            case 7:
                expedir_pacotes(exp, fila_pacotes);
                pausar();
                break;
            case 8:
                imprimir_docas(exp);
                pausar();
                break;
            case 9:
                imprimir_historico(exp);
                pausar();
                break;
            case 10:
                remover_produto(estoque);
                pausar();
                break;
            case 67: 
                secret_function(estoque, fila_pedidos, fila_pacotes); 
                pausar();
                break;
            case 0:
                printf(RED "Encerrando...\n" RESET);
                break;

            default:
                printf(RED "Opção inválida!\n" RESET);
                pausar();
                break;
        }
    } while (op != 0);

    expedicao_liberar(exp);
    fila_prioridade_liberar(fila_pacotes, liberar_pacote_void);
    fila_liberar(fila_pedidos, liberar_pedido_void);
    catalogo_liberar(estoque);
    return 0;
}
//Para compilar na versão atual: 
//gcc -Wall -Wextra -std=c99 -pedantic -g src/main.c src/utils.c src/catalogo.c src/interface.c src/display.c src/pedido.c src/fila.c src/fila_prioridade.c src/pilha.c src/pacote.c src/separacao.c src/caminhao.c src/expedicao.c -o programa.exe
//Opção oculta de testes: 67