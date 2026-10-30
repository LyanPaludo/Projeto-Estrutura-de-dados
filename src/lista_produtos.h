#ifndef LISTA_PRODUTOS_H
#define LISTA_PRODUTOS_H
#include <stdint.h>

typedef struct Produto Produto;

typedef struct ListaProdutos ListaProdutos;

//INSERT
Produto *cad_prod_sys(char *nome, int qtd, int volume, ListaProdutos *control); //Função para cadastrar produto em uma lista de produtos

//CREATE
ListaProdutos *criar_lista_produto(void);//Funcao para criar a lista

//READ
Produto *pesquisar_por_nome(char *nome, ListaProdutos *control); //Pesquisar por nome
Produto *pesquisar_por_codigo(uint64_t codigo, ListaProdutos *control); //Pesquisar por código

const uint64_t getCode(Produto *produto); //Código do produto
const char *getName(Produto *produto);    //Nome   do produto
const int getQtd(Produto *produto);       //Quant. do produto
const int getVolume(Produto *produto);    //Volume do produto

Produto *getFirst(ListaProdutos *control);  //Primeiro produto da lista
Produto *getLast(ListaProdutos *control);   //Último   produto da lista
Produto *getNext(Produto *produto);         //Próximo  produto da lista


//UPDATE
void aumentar_estoque(Produto *produto, int qtd);//Aumentar estoque
bool descontar_estoque(Produto *produto, int qtd);//Descontar do estoque

//DELETE
void liberar_lista(ListaProdutos *control);


#endif 