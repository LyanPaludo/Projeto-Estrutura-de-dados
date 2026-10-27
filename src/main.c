#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include "lista_produtos.h"
#include "utils.h"
#include "display.h"

// void cadastrar_pedido() {
//     printf("Cadastrar pedido...\n");

//     // Implementar cadastro do pedido
// }

int main(){
    setlocale(LC_ALL, "");
    int op = 0;
    Controle *control = criar_lista();
    if (control == NULL){
        liberar_lista(control);
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

        // Remove o '\n' deixado pelo scanf
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

/*
lista_produtos.c chama pesquisa_por_nome, mas a função se chama pesquisar_por_nome.
display.c usa pausar, limpar_buffer e free, mas não inclui utils.h nem <stdlib.h>.
static no header: gerar_prox_cod está declarada como static no .h, mas definida só no .c. Quem inclui o header recebe uma declaração sem definição. Tire essa linha do .h, já que a função é interna.
O nome do produto aponta para um array local: em cad_prod_sys, produto->nome = nome guarda o ponteiro do array nome de cadastrar_produto, que deixa de existir quando a função termina. Você precisa alocar memória e copiar o texto, como fazia antes.
free(nome) em array local: em cadastrar_produto, o nome é char nome[100], e free só vale para memória do malloc. Isso aparece em três lugares e derruba o programa. Como o nome é uma cópia, é na hora de copiar que a alocação vai acontecer.
liberar_lista(NULL) no main: quando criar_lista falha, você chama liberar_lista(control), que desreferencia NULL. Nesse caso não há nada a liberar.
O programa fecha sozinho na primeira entrada inválida: op começa em 0 e, quando o scanf falha, o continue vai direto ao while (op != 0), que já é falso. Use um valor inicial que não seja o de saída.
EOF ainda gera loop: se a entrada acabar, scanf falha, limpar_buffer e pausar retornam na hora e o menu se repete sem fim. Esse caso precisa encerrar.
*/

/*
Comportamento confuso:

Quando o produto já existe, a tela diz “Cadastro do produto realizado” e o volume digitado é ignorado (vale o antigo), sem avisar. O usuário também não fica sabendo que o estoque foi somado. Faça o sistema informar se o produto é novo ou existente, e avisar sobre o volume.
Quantidade ≤ 0 ou volume fora de 1 a 10 cancela em silêncio. Quem digita 11 provavelmente quer corrigir, não cancelar. Separe “valor inválido, tente de novo” de “cancelar”.
O nome vazio é aceito, e nomes com mais de 99 caracteres deixam o resto no buffer.
imprimir_produto chama pausar quando o produto é NULL. Funções de impressão que serão reutilizadas (em pedido, em pacote) não devem pausar. Deixe isso para quem chama.
*/

/*
cadastrar_produto agora vive em display.c, mas lê dados do usuário, e display deveria só exibir. Mova para um módulo de interface (interface.c/.h), que também receberá o cadastro de pedido. Faz sentido renomear: a função de tela como tela_cadastrar_produto e a de lógica como cadastrar_produto.
cad_prod_sys mistura “criar” e “somar ao existente” e abrevia o nome, o que destoa do resto. Uma busca antes, no módulo de interface, deixa as duas operações separadas e resolve o problema do aviso acima.
Em lista_produtos.c, criar_lista ainda imprime erro com cor, e as macros de cor só existem por causa disso. Deixe a mensagem no main, que já trata o NULL. As macros duplicadas em display.c poderiam ir para um cores.h comum.
limpar_tela() e pausar() no utils usam () em vez de (void).
Restos: o comentário “COM CORZINHA” em lista_produtos.c, o #include <stdint.h> repetido no .c e o bloco comentado no main.
Os rótulos de seção ainda não batem: cad_prod_sys está em “INSERT” no .h, enquanto no .c a mesma função fica logo depois de inserir_produto, e criar_lista aparece em “CREATE” separada.
*/