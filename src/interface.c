#include "interface.h"
#include "catalogo.h"
#include "pedido.h"
#include "utils.h"
#include "display.h"
#include "cores.h"
#include "constantes.h"
#include "separacao.h"
#include <string.h>
#include <stdio.h>

static const char *const NOMES_PC[] = {
        "PC-1",
        "PC-2",
        "PC-3",
        "PC-4",
        "PC-5",
        "PC-6",
        "PC-7",
        "PC-8",
        "PC-9",
        "PC-10"
    };

void cadastrar_produto(Catalogo *control){
    char nome[100];
    int qtd;
    int volume;
    int res;
    while (1){
        printf(WHITE "Digite o nome do produto que desejas cadastrar: " RESET);
        if (!ler_string(nome, 100)){
            printf(RED BOLD "\nEntrada inválida, retornando...\n" RESET);
            pausar();
            return;
        }
        if (strlen(nome) <= 1 || strlen(nome) >= 20){
            printf(RED "\n--O nome deve ter mais do que um e menos do que 20 caracteres--\n" RESET);
            pausar();
            continue;
        }
        if (apenas_espacos(nome)){
            printf(RED "\nO nome não deve ser composto apenas por espaços vazios\n" RESET);
            pausar();
            continue;
        }
        break;
    }

    while (1){//quantidade
        printf(WHITE BOLD "\nDigite a quantidade (>= 1): " RESET);
        res = ler_int(&qtd);
        if (res == EOF){
            printf(RED BOLD "\nFim de arquivo atingido (EOF)\n" RESET);
            pausar();
            return;
        }else if (res == 0){
            printf(RED BOLD "\nErro: entrada inválida.\n" RESET);
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
        if (!produto_aumentar_estoque(produto, qtd)){
            printf(RED BOLD "\nErro: entrada inválida.\n" RESET);
        }
        pausar();
        return;
    }

    while (1){//volume
        printf(WHITE BOLD "\nDigite o volume que o produto ocupa (%d - %d): " RESET, PRODUTO_VOLUME_MIN, PRODUTO_VOLUME_MAX);
        res = ler_int(&volume);
        if (res == EOF){
            printf(RED BOLD "\nFim de arquivo atingido (EOF)\n" RESET);
            pausar();
            return;
        }else if (res == 0){
            printf(RED BOLD "\nErro: entrada inválida.\n" RESET);
            pausar();
            continue;
        }
        if (volume < PRODUTO_VOLUME_MIN || volume > PRODUTO_VOLUME_MAX){
            printf(RED "\n--Volume deve ser um número entre %d e %d--\n" RESET, PRODUTO_VOLUME_MIN, PRODUTO_VOLUME_MAX);
            pausar();
            continue;
        }
        break;
    }

    produto = produto_cadastrar_estoque(nome, qtd, volume, control);
    if (produto == NULL){
        printf(RED BOLD "\nErro: Cadastro do produto\n" RESET);
        pausar();
        return;
    }
    printf(GREEN BOLD "\nCadastro do produto realizado com sucesso!\n" RESET);
    imprimir_produto(produto);
    pausar();
    return;
}

void cadastrar_pedido(Fila *fila_pedidos, Catalogo *estoque){
    if (catalogo_vazio(estoque)){
        printf(RED "\nNão há produtos cadastrados no estoque, impossível prosseguir com o cadastro do pedido.\n" RESET);
        pausar();
        return;
    }
    printf(WHITE BOLD "\n--Cadastro de Pedido--\n" RESET);
    int res;
    int cod;
    int qtd;
    char destino[DESTINO_TAM];
    while (1){
        printf(WHITE BOLD "\nInforme o destino do pedido: " RESET);
        if (!ler_string(destino, DESTINO_TAM)){
            printf(RED BOLD "\nEntrada inválida, retornando...\n" RESET);
            pausar();
            return;
        }
        if (strlen(destino) < 2){
            printf(RED "\nO destino deve conter pelo menos 2 caracteres.\n" RESET);
            pausar();
            continue;
        }
        if (apenas_espacos(destino)){
            printf(RED "\nO destino não deve ser composto apenas por espaços vazios\n" RESET);
            pausar();
            continue;
        }
        break;
    }
    Pedido *pedido = pedido_criar(destino);
    if (pedido == NULL){
        printf(RED BOLD "\nErro interno, retornando...\n" RESET);
        pausar();
        return;
    }

    while (1){
        while (1){//ID DO PRODUTO
            printf(WHITE "\nDigite o código do produto (0 para cancelar o pedido): " RESET);
            res = ler_int(&cod);
            if (res == EOF){
                printf(RED BOLD "\nFim de arquivo atingido (EOF)\n" RESET);
                pedido_liberar(pedido);
                pausar();
                return;
            }else if (res == 0){
                printf(RED BOLD "\nErro: entrada inválida.\n" RESET);
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
                printf(RED BOLD "\nFim de arquivo atingido (EOF)\n" RESET);
                pedido_liberar(pedido);
                pausar();
                return;
            }else if (res == 0){
                printf(RED BOLD "\nErro: entrada inválida.\n" RESET);
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
                printf(RED BOLD "\nFim de arquivo atingido (EOF)\n" RESET);
                pedido_liberar(pedido);
                pausar();
                return;
            }else if (res == 0){
                printf(RED BOLD "\nErro: entrada inválida.\n" RESET);
                pausar();
                continue;
            }
            if (op == 1){
                break;
            }else if (op == 2){
                if (!fila_enfileirar(fila_pedidos, pedido)){
                    printf(RED BOLD "\nErro interno: enfileiramento do pedido\n" RESET);
                    pedido_liberar(pedido);
                    pausar();
                    return;
                }
                printf(WHITE BOLD "\nCadastro do pedido realizado com sucesso!\n" RESET);
                printf(GREEN "\nID do pedido: " RESET);
                printf(WHITE ULINED "%s \n" RESET, pedido_get_code(pedido));
                pausar();
                return;
            }else{
                printf(RED "\nOpção inválida, tente novamente.\n" RESET);
                pausar();
                continue;
            }
        }
    }
}

void separar_pedido(Fila *pedidos, FilaPrioridade *pacotes){
    Pedido *separado = NULL;
    int antes = fila_prioridade_tamanho(pacotes);
    ResultadoSeparacao r = separar_prox_pedido(pedidos, pacotes, &separado);
    if (r == SEPARACAO_FILA_VAZIA){
        printf(RED "\nNão há pedidos!\n" RESET);
        return;
    }
    if (r == SEPARACAO_SEM_ESTOQUE){
        printf(RED "\n -Não há estoque o bastante para separar o próximo pedido!- \n" RESET);
        printf(WHITE BOLD "O próximo pedido permanecerá na fila até o estoque ser reabastecido!\n" RESET);
        printf(GREEN "Reabasteça o estoque com 1 (Cadastrar Produto)\n" RESET);
        return;
    }
    if (r == SEPARACAO_ERRO){
        printf(RED BOLD "\nErro interno: separação do pedido\n" RESET);
        return;
    }
    imprimir_pedido(separado);
    printf(GREEN "\nForam gerados " RESET WHITE "%d" RESET GREEN " novos pacotes!\n" RESET, (fila_prioridade_tamanho(pacotes) - antes));
    pedido_liberar(separado);
    return;
}

void expedir_pacotes(Expedicao *exp, FilaPrioridade *pacotes){
    int pacotes_antes = fila_prioridade_tamanho(pacotes);
    int saidos_antes  = expedicao_historico_tamanho(exp);
    if (pacotes_antes == 0){
        printf(RED "\nNão há pacotes prontos!\n" RESET);
        return;
    }
    if (!expedicao_expedir(exp, pacotes)){
        printf(RED BOLD "\nErro: Não foi possível expedir os pacotes.\n" RESET);
        return;
    }
    printf(GREEN "\nForam expedidos com sucesso " RESET WHITE "%d" RESET GREEN " pacotes!\n", pacotes_antes);
    printf(RED "\n-> %d " RESET WHITE "caminhões deixaram as docas!" RESET RED " <-\n" RESET, expedicao_historico_tamanho(exp) - saidos_antes);
}

void remover_produto(Catalogo *estoque){
    if (catalogo_vazio(estoque)){
        printf(RED "\nO estoque está vazio!\n" RESET);
        return;
    }
    imprimir_catalogo(estoque);
    int cod;
    while (1){
        printf(GREEN "\nDigite o código do produto que deseja remover (0 para cancelar): " RESET);
        int res = ler_int(&cod);
        if (res == EOF){
            printf(RED BOLD "\nFim de arquivo atingido (EOF)\n" RESET);
            return;
        }else if (res == 0){
            printf(RED BOLD "\nErro: entrada inválida.\n" RESET);
            pausar();
            continue;
        }
        if (cod == 0){
            printf(RED "Cancelando..." RESET);
            return;
        }
        break;
    }
    Produto *p = produto_search_code(cod, estoque);
    if (p == NULL){
        printf(RED BOLD "\nCódigo não encontrado\n" RESET);
        return;
    }
    imprimir_produto(p);
    while (1){
        printf(WHITE BOLD "\nConfirmar remoção:\n" RESET);
        printf(GREEN "(1) Remover produto\n" RESET);
        printf(RED   "(2) Cancelar\n" RESET);
        int opc;
        int res = ler_int(&opc);
        if (res == EOF){
            printf(RED BOLD "\nFim de arquivo atingido (EOF)\n" RESET);
            return;
        }else if (res == 0){
            printf(RED BOLD "\nErro: entrada inválida.\n" RESET);
            pausar();
            continue;
        }
        if (opc == 2){
            return;
        }
        if (opc != 1){
            printf(RED "\nÉ 1 ou 2!\n" RESET);
            pausar();
            continue;
        }
        break;
    }
    if (!catalogo_remover(estoque, cod)){
        printf(RED BOLD "\nErro interno.\n" RESET);
        return;
    }
    printf(GREEN BOLD "\nProduto removido com sucesso!\n" RESET);
    printf(WHITE BOLD "OBS: Pedidos e pacotes já criados com esse produto continuam válidos.\n" RESET);
}

//secret

static bool secret_importOfChina(Catalogo *estoque){
    int tamanho = sizeof(NOMES_PC) / sizeof(NOMES_PC[0]);
    for (int i = 0; i < tamanho; i++) {
        Produto *produto = produto_search_name(NOMES_PC[i], estoque);
        if (produto != NULL){
            if (!produto_aumentar_estoque(produto, 10)){
                return false;
            }
        }else{
            produto = produto_cadastrar_estoque(NOMES_PC[i], 10, i+1, estoque);
            if (produto == NULL){
                return false;
            }
        }
    }
    return true;
}

static int secret_ordersFlood(Fila *pedidos, Catalogo *estoque){
    int tamanho = sizeof(NOMES_PC) / sizeof(NOMES_PC[0]);
    int j=0;
    for (int i = 0; i < tamanho; i++) {
        Produto *produto = produto_search_name(NOMES_PC[i], estoque);
        if (produto == NULL){
            continue;
        }
        j++;
        Pedido *pedido = pedido_criar("Brasil");
        if (pedido == NULL){
            printf(RED BOLD "\nErro: falta de memória\n" RESET);
            pausar();
            return j;
        }
        if (pedido_item_cadastrar(pedido, produto, 1+2*(i%6)) == NULL){
            pedido_liberar(pedido);
            printf(RED BOLD "\nErro: falta de memória\n" RESET);
            pausar();
            return j;
        }
        if (!fila_enfileirar(pedidos, pedido)){
            pedido_liberar(pedido);
            printf(RED BOLD "\nErro: cadastro do pedido\n" RESET);
            pausar();
            return j;
        }
    }
    return j;
}

static int secret_gerarPacotes(FilaPrioridade *pacotes, Catalogo *estoque){
    static int contador = 1;
    int tamanho = sizeof(NOMES_PC) / sizeof(NOMES_PC[0]);
    int criados = 0;
    for (int i = 0; i < tamanho; i++){
        Produto *produto = produto_search_name(NOMES_PC[i], estoque);
        if (produto == NULL){
            continue;
        }
        int prioridade = sortear(PRIORIDADE_QTD);
        Pacote *pack = pacote_criar("MISTERIOSO", contador, "Um mistério", prioridade);
        if (pack == NULL){
            return criados;
        }
        if (pacote_adicionar_produto(pack, produto) != PACOTE_ADICIONADO){
            pacote_liberar(pack);
            return criados;
        }
        if (!fila_prioridade_enfileirar(pacotes, pack, prioridade)){
            pacote_liberar(pack);
            return criados;
        }
        contador++;
        criados++;
    }
    return criados;
}

static void secret_packages(FilaPrioridade *pacotes, Catalogo *estoque){
    printf(WHITE BOLD "\nVocê escolheu: " RESET RED "PACOTES MISTERIOSOS" RESET);
    int criados = secret_gerarPacotes(pacotes, estoque);
    if (criados == 0){
        printf(RED BOLD "\nNenhum produto experimental no estoque! Importe-os antes (opção 1).\n" RESET);
        return;
    }
    printf(GREEN "\nForam injetados %d pacotes misteriosos! (Ver menu 6).\n" RESET, criados);
}

void secret_function(Catalogo *estoque, Fila *pedidos, FilaPrioridade *pacotes){
    limpar_tela();
    printf(RED BOLD "\n░░░░░░░░░░░░░░░░░░░░░░░░░░\n" RESET);

    printf(GREEN    "\nFUNÇÃO SECRETA ENCONTRADA!\n" RESET);

    printf(RED BOLD "\n░░░░░░░░░░░░░░░░░░░░░░░░░░\n" RESET);
    printf(WHITE BOLD "\n--Você desbloqueou os privilégios da economia temporal!--\n" RESET);
    while (1){
        printf(WHITE "\n( 1 ) Importar produtos da china." RESET);
        printf(WHITE "\n( 2 ) Enxurrada de pedidos experimentais." RESET);
        printf(WHITE "\n( 3 ) 2 pila ou pacotes misteriosos?" RESET);
        printf(RED ULINED "\n( 0 ) Abster-se dos privilégios" RESET);
        printf(GREEN "\n\n-> Escolha uma opção: " RESET);
        int op = -1;
        int res = ler_int(&op);
        if (res == EOF){
            printf(RED BOLD "\nFim dos privilégios atingido (EOF)\n" RESET);
            return;
        }else if (res == 0){
            printf(RED BOLD "\nOusas falsificar sua escolha?.\n" RESET);
            pausar();
            continue;
        }
        switch (op){
            case 1:
                if (!secret_importOfChina(estoque)){
                    printf(RED BOLD "\nErro na importação\n" RESET);
                    return;
                }
                printf(GREEN "\nProdutos 100%% confiáveis foram importados! Verifique o estoque.\n" RESET);
                return;
            case 2:
                printf(GREEN "\nVocê recebeu uma enxurrada de %d pedidos! Rápido, verifique a fila de pedidos!\n" RESET, secret_ordersFlood(pedidos, estoque));
                return;
            case 3:
                secret_packages(pacotes, estoque);
                return;
            case 0:
                printf(RED "\nVocê absteve-se dos privilégios da economia temporal!\n" RESET);
                return;
            default:
                printf(RED "\nOpção inválida\n" RESET); 
                pausar();
                break;
        }
    }
}
