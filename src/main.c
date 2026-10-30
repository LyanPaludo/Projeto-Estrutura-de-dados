#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include "lista_produtos.h"
#include "utils.h"
#include "display.h"
#include "interface.h"

// void cadastrar_pedido() {
//     printf("Cadastrar pedido...\n");

//     // Implementar cadastro do pedido
// }

int main(){
    setlocale(LC_ALL, "");
    int op = -1;
    Controle *control = criar_lista();
    if (control == NULL){
        return EXIT_FAILURE;
    }
    do {
        printf("=== VENDA CERTA ===\n\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Cadastrar Pedido\n");
        printf("3. Listar produtos\n");
        printf("0. Encerrar\n\n");

        printf("Informe sua opcao: ");
        if (scanf("%d", &op)!=1){
            printf("\nValor Inválido\n");
            limpar_buffer();
            pausar();
            continue;
        }

        limpar_buffer();

        switch (op) {
            case 1:
                cadastrar_produto(control);
                break;
            case 2:
                break;
            case 3:
                imprimir_lista(control);
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

    liberar_lista(control);
    return 0;
}
/*
Fechar a base de produtos: corrigir o que está listado na próxima seção e fazer um commit.
Decidir e anotar no README:
    quando o estoque é descontado (na criação do pedido ou na separação);
    se o código do pedido é digitado ou gerado;
    se o destino é endereço ou código de entrega.
TAD de itens do pedido: lista encadeada cujo nó guarda o que a montagem precisa (qual produto, quantidade e volume unitário). Decida se guarda o código ou um ponteiro para o produto.
Estrutura do pedido: código, destino, status e a lista de itens.
TAD de fila: com descritor de início e fim. Ela será usada para pedidos aguardando separação e para pacotes prontos para expedição, então decida como reaproveitar a mesma fila para dois tipos de dado, ou se vai ter duas versões. Vale perguntar ao professor se ele já apresentou void *.
Cadastro de pedido (interface): ler código e destino, repetir a adição de itens (buscar produto, validar quantidade e estoque) e, ao fim, enfileirar o pedido.
TAD de pilha: push, pop, topo e vazia, com controle do volume atual do pacote e da capacidade 10.
Estrutura do pacote: identificador (ex.: PAC-1001-1), destino herdado do pedido, pilha de itens e volume total.
Separação e montagem: tirar o pedido da frente da fila e processar os itens na ordem, unidade por unidade. Quando o volume estourar, desfazer o último push, fechar o pacote, enfileirá-lo na fila de expedição e abrir outro já com aquela unidade. Ao acabar os itens, fechar o último pacote.
Novas opções no menu: ver a fila de pedidos, separar o próximo, ver pacotes prontos.
Impressão de pedido, pacote e filas.
Liberação de memória de tudo ao encerrar.
Testes: o exemplo do slide 6 é um ótimo caso (P1 qtd 4 vol 2, P2 qtd 1 vol 1, P3 qtd 2 vol 2 deve gerar um pacote de volume 9 e outro de volume 4). Teste também pedido com produto de volume 10, pedido com um único item e fila vazia.
Atualizar o README e marcar o checklist.
*/

//OBS: NÃO APAGAR -> Mais pra frente utilizar EPOCH como parâmetro na lista de prioridades (Lá na parte 2)