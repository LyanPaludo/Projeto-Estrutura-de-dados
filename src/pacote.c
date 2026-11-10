#include "lista_produtos.h"
#include "constantes.h"
#include "pilha.h"
#include "pacote.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Pacote{
    char *codigo;
    char destino[DESTINO_TAM];
    Pilha *itens;
    int prioridade;
};

static char *pacote_gerar_cod(const char *codigo_pedido, int n){
    char buffer[40];  
    int res = snprintf(buffer, sizeof(buffer), "PAC-%s-%d", codigo_pedido, n);
    if (res < 0 || (unsigned long long)res >= sizeof(buffer)){
        return NULL;
    }
    char *codigo = (char *) malloc(strlen(buffer) + 1);
    if (codigo != NULL) {
        strcpy(codigo, buffer);
    }
    return codigo;
}

//CREATE
Pacote *pacote_criar(const char *codigo_pedido, int n, const char *destino, int prioridade){
    if (codigo_pedido == NULL || destino == NULL || n < 1){
        return NULL;
    }
    if (prioridade < 0 || prioridade > PRIORIDADE_QTD-1){
        return NULL;
    }
    Pacote *pack = (Pacote *) malloc(sizeof(Pacote));
    if (pack == NULL){
        return NULL;
    }
    pack->codigo = pacote_gerar_cod(codigo_pedido, n);
    if (pack->codigo == NULL){
        free(pack);
        return NULL;
    }
    pack->itens = pilha_criar();
    if (pack->itens == NULL){
        free(pack->codigo);
        free(pack);
        return NULL;
    }
    strncpy(pack->destino, destino, DESTINO_TAM - 1);
    pack->destino[DESTINO_TAM - 1] = '\0';
    pack->prioridade = prioridade;
    return pack;
}

//READ
void pacote_percorrer(Pacote *pacote, void (*visitar)(Produto *)){
    pilha_percorrer(pacote->itens, visitar);
}


const char *pacote_get_codigo(Pacote *pacote){
    if (pacote == NULL){
        return NULL;
    }
    return pacote->codigo;
}

const char *pacote_get_destino(Pacote *pacote){
    if (pacote == NULL){
        return NULL;
    }
    return pacote->destino;
}

int pacote_get_volume(Pacote *pacote){
    return pilha_volume(pacote->itens);
}

int pacote_get_qtd(Pacote *pacote){
    return pilha_tamanho(pacote->itens);
}

int pacote_get_prioridade(Pacote *pacote){
    return pacote->prioridade;
}

//UPDATE
ResultadoPacote pacote_adicionar_produto(Pacote *pacote, Produto *produto){
    if (produto == NULL || pacote == NULL){
        return PACOTE_ERRO;
    }
    if (!pilha_empilhar(pacote->itens, produto)){
        return PACOTE_ERRO;
    }
    if (pilha_volume(pacote->itens) > PACOTE_CAPACIDADE){
        pilha_desempilhar(pacote->itens);
        return PACOTE_NAO_COUBE;
    }
    return PACOTE_ADICIONADO;
}

//DELETE
void pacote_liberar(Pacote *pacote){
    pilha_liberar(pacote->itens);
    free(pacote->codigo);
    free(pacote);
}