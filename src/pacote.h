#ifndef PACOTE_H
#define PACOTE_H
#include "lista_produtos.h"
#include "constantes.h"

typedef struct Pacote Pacote;

typedef enum{
    PACOTE_ADICIONADO,
    PACOTE_NAO_COUBE,
    PACOTE_ERRO
}ResultadoPacote;


//CREATE
Pacote *pacote_criar(const char *codigo_pedido, int n, const char *destino, int prioridade); //Cria pacote vazio, NULL se algo falhar

//READ
void pacote_percorrer(Pacote *pacote, void (*visitar)(Produto *)); //Percorre os itens do pacote (chama percorrer pilha)
const char *pacote_get_codigo(Pacote *pacote); //Retorna código do pacote
const char *pacote_get_destino(Pacote *pacote); //Retorna destino do pacote
int pacote_get_volume(Pacote *pacote); //Retorna o volume total dos itens dentro do pacote
int pacote_get_qtd(Pacote *pacote); //Retorna a quantidade de itens no pacote
int pacote_get_prioridade(Pacote *pacote); //Retorna a prioridade do pacote
//UPDATE
ResultadoPacote pacote_adicionar_produto(Pacote *pacote, Produto *produto); //Tenta empilhar um produto no pacote, retorna um ENUM ResultadoPacote

//DELETE
void pacote_liberar(Pacote *pacote); //Libera o pacote

#endif