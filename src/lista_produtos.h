#ifndef LISTA_PRODUTOS_H
#define LISTA_PRODUTOS_H
#include <stdint.h>

typedef struct Produto{
    uint64_t codigo;
    char *nome;
    int qtd;                //Quantidade deste produto no estoque
    int volume;             //Volume ocupado por um único produto
    struct Produto *prox;   //Próximo produto na lista
}Produto;

typedef struct Controle{
    int prod_total;     //Quantidade de produtos diferentes
    Produto *primeiro;
    Produto *ultimo;
}Controle;

//INSERT
Produto *cad_prod_sys(char *nome, int qtd, int volume, Controle *control); //Função para cadastrar produto em uma lista de produtos
void inserir_produto(Controle *control, Produto *produto);//inserir produto

//CREATE
Controle *criar_lista(void);//Funcao para criar a lista

//READ
Produto *pesquisar_por_nome(char *nome, Controle *control); //Pesquisar por nome
Produto *pesquisar_por_codigo(uint64_t codigo, Controle *control); //Pesquisar por código

//UPDATE
void aumentar_quantidade(Produto *produto, int qtd);//aumentar quantidade do produto

//DELETE
void liberar_produto(Produto *produto);
void liberar_lista(Controle *control);


#endif 