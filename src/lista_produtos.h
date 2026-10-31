#ifndef LISTA_PRODUTOS_H
#define LISTA_PRODUTOS_H
#include <stdint.h>
#include <stdbool.h>

typedef struct Produto Produto;

typedef struct ListaProdutos ListaProdutos;

//INSERT
Produto *produto_cadastrar_estoque(const char *nome, int qtd, int volume, ListaProdutos *control); //Função para cadastrar produto em uma lista de produtos

//CREATE
ListaProdutos *lista_produtos_criar(void);//Funcao para criar a lista

//READ
Produto *produto_search_name(const char *nome, ListaProdutos *control); //Pesquisar por nome
Produto *produto_search_code(uint64_t codigo, ListaProdutos *control); //Pesquisar por código

uint64_t produto_get_code(Produto *produto); //Código do produto
const char *produto_get_name(Produto *produto);    //Nome   do produto
int produto_get_qtd(Produto *produto);       //Quant. do produto
int produto_get_volume(Produto *produto);    //Volume do produto

Produto *produto_get_first(ListaProdutos *control);  //Primeiro produto da lista
Produto *produto_get_last(ListaProdutos *control);   //Último   produto da lista
Produto *produto_get_next(Produto *produto);         //Próximo  produto da lista


//UPDATE
void produto_aumentar_estoque(Produto *produto, int qtd);//Aumentar estoque
bool produto_descontar_estoque(Produto *produto, int qtd);//Descontar do estoque

//DELETE
void lista_produtos_liberar(ListaProdutos *control);


#endif 