#include <stdio.h>

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void limpar_tela() {
    printf("\033[H\033[2J");
}

void pausar() {
    printf("\nPressione [Enter] para continuar...");
    getchar();
    limpar_tela();
}

void cadastrar_produto() {
    printf("Cadastrar produto...\n");

    // Implementar cadastro do produto
}

void cadastrar_pedido() {
    printf("Cadastrar pedido...\n");

    // Implementar cadastro do pedido
}

int main(void) {
    int op;

    do {
        printf("=== VENDA CERTA ===\n\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Cadastrar Pedido\n");
        printf("0. Encerrar\n\n");

        printf("Informe sua opcao: ");
        scanf("%d", &op);

        // Remove o '\n' deixado pelo scanf
        limpar_buffer();

        switch (op) {
            case 1:
                cadastrar_produto();
                pausar();
                break;

            case 2:
                cadastrar_pedido();
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

    return 0;
}