#include "listaSimples.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct No {
  int dado;
  No *proximo;
} No;

typedef struct ListaSimples {
  No *primeiro; // Ponteiro para o primeiro nó (excluindo o cabeçalho)
  No *ultimo; // Ponteiro para o último nó
} ListaSimples;

ListaSimples *criar_lista() {
  ListaSimples *lista = (ListaSimples *) malloc(sizeof(ListaSimples));
  if (lista == NULL) {
    return NULL; // Falha na alocação de memória
  }
  lista->primeiro = NULL;
  lista->ultimo = NULL;
  return lista;
}


No *inserir_inicio(ListaSimples *lista, int dado) {
  // Alocar memória para o novo nó
  No *novo = (No *) malloc(sizeof(No));
  if (novo == NULL) {
    return NULL; // Falha na alocação de memória
  }
  // Atribuir valor e inicializar ponteiro 'proximo'
  novo->dado = dado;
  novo->proximo = NULL;
  // Inserir o novo nó no início da lista
  if (lista->primeiro == NULL) {
    // Lista vazia: novo nó é o primeiro e último nó
    lista->primeiro = novo;
    lista->ultimo = novo;
  } else {
    // Lista não vazia: novo nó se torna o primeiro nó
    novo->proximo = lista->primeiro;
    lista->primeiro = novo;
  }
  return novo; // Retornar o ponteiro para o nó inserido
}

int remover_inicio(ListaSimples *lista) {
  if (lista->primeiro == NULL) {
    return -1; // Lista vazia
  }
  No *removido = lista->primeiro;
  int valor_removido = removido->dado;
  if (lista->primeiro == lista->ultimo) {
    // Único nó: lista fica vazia
    lista->primeiro = NULL;
    lista->ultimo = NULL;
  } else {
    // Vários nós: atualizar ponteiros
    lista->primeiro = lista->primeiro->proximo;
  }
  free(removido);
  return valor_removido;
}

void imprimir_lista(ListaSimples *lista) {
  if (lista->primeiro == NULL) {
    printf("Lista vazia!\n");
    return;
  }
  No *atual = lista->primeiro;
  while (atual != NULL) {
    printf("%d ", atual->dado);
    atual = atual->proximo;
  }
  printf("\n");
}

void destruir_lista(ListaSimples *lista) {
  if (lista->primeiro == NULL) {
    return;
  }
  No *atual = lista->primeiro;
  No *anterior;
  while (atual != NULL) {
    anterior = atual;
    atual = atual->proximo;
    free(anterior);
  }
  lista->primeiro = NULL;
  lista->ultimo = NULL;
}
