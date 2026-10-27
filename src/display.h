#ifndef DISPLAY_H
#define DISPLAY_H
#include "lista_produtos.h"

void imprimir_produto(Produto *produto); //Função para imprimir um único produto
void imprimir_lista(Controle *control); //Função para imprimir toda uma lista
void cadastrar_produto(Controle *control);

#endif