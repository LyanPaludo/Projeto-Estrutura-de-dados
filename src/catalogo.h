#ifndef CATALOGO_H
#define CATALOGO_H
#include <stdint.h>
#include <stdbool.h>

typedef struct Produto Produto;

typedef struct Catalogo Catalogo;

//INSERT
Produto *produto_cadastrar_estoque(const char *nome, int qtd, int volume, Catalogo *control); //Função para cadastrar produto em um catálogo

//CREATE
Catalogo *catalogo_criar(void);//Funcao para criar o catalogo

//READ
void catalogo_percorrer(Catalogo *estoque, void (*visitar)(Produto *p)); //Percorre o catálogo
bool catalogo_vazio(Catalogo *estoque); //Verifica se o catálogo está vazio

Produto *produto_search_name(const char *nome, Catalogo *control); //Pesquisar por nome
Produto *produto_search_code(uint64_t codigo, Catalogo *control); //Pesquisar por código

uint64_t produto_get_code(Produto *produto); //Código do produto
const char *produto_get_name(Produto *produto);    //Nome   do produto
int produto_get_qtd(Produto *produto);       //Quant. do produto
int produto_get_volume(Produto *produto);    //Volume do produto

//UPDATE
bool produto_aumentar_estoque(Produto *produto, int qtd);//Aumentar estoque
bool produto_descontar_estoque(Produto *produto, int qtd);//Descontar do estoque

//DELETE
void catalogo_liberar(Catalogo *control);


#endif 