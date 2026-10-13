#ifndef LISTASIMPLES_H
#define LISTASIMPLES_H

// Definição incompleta do registro para evitar que o usuário modifique valores diretamente
typedef struct ListaSimples ListaSimples;
typedef struct No No;


// Função para criar uma nova Lista Simplesmente encadeada
ListaSimples* criar_lista();

// Outras operações disponibilizadas pelo nosso TAD
void destruir_lista(ListaSimples *lista);

// Acesso
No *buscar(ListaSimples *lista, int dado);
void imprimir_lista(ListaSimples *lista);

// Inserção
No *inserir_inicio(ListaSimples *lista, int dado);
No *inserir_fim(ListaSimples *lista, int dado);
No *inserir_posicao(ListaSimples *lista, int dado, int posicao);

// Remoção
int remover_inicio(ListaSimples *lista);
int remover_fim(ListaSimples *lista);
int remover_posicao(ListaSimples *lista, int posicao);

#endif /* LISTASIMPLES_H */
