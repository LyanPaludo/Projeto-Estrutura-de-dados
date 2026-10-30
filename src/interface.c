#include "interface.h"
#include "lista_produtos.h"
#include "utils.h"
#include "display.h"
#include <string.h>
#include <stdio.h>

// https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
#define RESET "\x1b[0m"     //RESET
#define RED "\x1b[31m"      // VERMELHO
#define GREEN "\x1b[32m"    // VERDE
#define WHITE "\x1b[37m"    // BRANCO
#define BOLD "\x1b[1m"      //  NEGRITO
#define ULINED "\x1b[4m"    //  SUBLINHADO


void cadastrar_produto(Controle *control){
    char nome[100];
    int qtd;
    int volume;
    while (1){
        while (1){
            printf(WHITE "Digite o nome do produto que desejas cadastrar: " RESET);
            if (fgets(nome, sizeof(nome), stdin) != NULL){
                nome[strcspn(nome, "\n")] = '\0';
            }else{
                printf(RED BOLD "\nErro: Nome não reconhecido em cadastrar produto!\n" RESET);
                pausar();
                return;
            }
            if (strlen(nome) <= 1 || strlen(nome) >= 20){
                printf(RED "\n--O nome deve ter mais do que um e menos do que 20 dígitos--\n" RESET);
                pausar();
                continue;
            }
            break;
        }

        while (1){//quantidade
            printf(WHITE BOLD "\nDigite a quantidade (>= 1 | <= 0 para cancelar): " RESET);
            if (scanf("%d", &qtd)!=1){
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
            imprimir_produto(pesquisar_por_nome(nome, control));
            printf(RED BOLD "\nA quantidade será aumentada e o volume antigo será mantido!\n" RESET);
            pausar();
            aumentar_quantidade(produto, qtd);
            return;
        }

        while (1){//volume
            printf(WHITE BOLD "\nDigite o volume que o produto ocupa (1-10): " RESET);
            if (scanf("%d", &volume)!=1){
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
}