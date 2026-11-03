#include "pacote.h"
#include "lista_produtos.h"
#include "constantes.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

static Produto *vistos[32];
static int n_vistos;
static void coletar(Produto *p){
    vistos[n_vistos++] = p;
}

static void teste_pacote_novo(void){
    ListaProdutos *lista = lista_produtos_criar();
    produto_cadastrar_estoque("A", 10, 3, lista);
    Pacote *pack = pacote_criar("PED1", 1, "Rua Almeidas");
    pacote_percorrer(pack, coletar);
    assert(pacote_get_volume(pack) == 0);
    assert(strcmp(pacote_get_codigo(pack), "PAC-PED1-1") == 0);
    pacote_liberar(pack);
    lista_produtos_liberar(lista);
}

int main(void){
    teste_pacote_novo();
    printf("\nOK");
    return 0;
}