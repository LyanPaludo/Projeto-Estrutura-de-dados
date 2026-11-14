#include "catalogo.h"
#include "utils.h"
#include "constantes.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>

struct Produto{
    uint64_t codigo;
    char *nome;
    int qtd;                //Quantidade deste produto no estoque
    int volume;             //Volume ocupado por um único produto
    struct Produto *esq;   //Esquerda do produto na arvore
    struct Produto *dir;   //Direita do produto na arvore
    int altura; // AVL
};

struct Catalogo{
    Produto *removidos; //Produtos removidos da arvore
    Produto *raiz;      //Raíz da arvore
};

//GERAR PRÓXIMO CÓDIGO
static uint64_t produto_gerar_cod(void) {
    static uint64_t contador_cod = 1;
    return contador_cod++;
}

//FUNÇÕES AVL
static int altura(Produto *produto){
    if (produto == NULL){
        return 0;
    }
    return produto->altura;
}
static int fator_balanceamento(Produto *produto){
    if (produto == NULL){
        return 0;
    }
    return altura(produto->esq) - altura(produto->dir);
}
static int maior(int a, int b){
    return a > b ? a : b;
}
static void atualizar_altura(Produto *produto){
    produto->altura = 1 + maior(altura(produto->esq), altura(produto->dir));
}
static Produto *rotacao_direita(Produto *a){
    Produto *b = a->esq;
    a->esq = b->dir;
    b->dir = a;
    atualizar_altura(a);
    atualizar_altura(b);
    return b;
}
static Produto *rotacao_esquerda(Produto *a){
    Produto *b = a->dir;
    a->dir = b->esq;
    b->esq = a;
    atualizar_altura(a);
    atualizar_altura(b);
    return b;
}
static Produto *rebalancear(Produto *no){
    if (no == NULL){
        return NULL;
    }
    atualizar_altura(no);
    int fb = fator_balanceamento(no);
    if (fb > 1){
        if (fator_balanceamento(no->esq) < 0){
            no->esq = rotacao_esquerda(no->esq);
        }
        return rotacao_direita(no);
    }else if (fb < -1){
        if (fator_balanceamento(no->dir) > 0){
            no->dir = rotacao_direita(no->dir);
        }
        return rotacao_esquerda(no);
    }
    return no;
}
static Produto *inserir_no(Produto *no, Produto *novo){
    if (no == NULL){
        return novo;
    }
    if (novo->codigo < no->codigo){
        no->esq = inserir_no(no->esq, novo);
    }else{
        no->dir = inserir_no(no->dir, novo);
    }
    return rebalancear(no);
}
static void produto_inserir(Catalogo *control, Produto *produto){
    produto->esq = NULL;
    produto->dir = NULL;
    produto->altura = 1;
    control->raiz = inserir_no(control->raiz, produto);
}


//CREATE
Catalogo *catalogo_criar(void){
    Catalogo *control  = (Catalogo *) malloc(sizeof(Catalogo));
    if (control == NULL){
        return NULL;
    }
    control->raiz = NULL;
    control->removidos = NULL;
    return control;
    
}

//READ
static void percorrer_em_ordem(Produto *no, void (*visitar)(Produto *p)){
    if (no == NULL){
        return;
    }
    percorrer_em_ordem(no->esq, visitar);
    visitar(no);
    percorrer_em_ordem(no->dir, visitar);
}
void catalogo_percorrer(Catalogo *estoque, void (*visitar)(Produto *p)){
    if (catalogo_vazio(estoque)){
        return;
    }
    percorrer_em_ordem(estoque->raiz, visitar);
}

bool catalogo_vazio(Catalogo *estoque){
    if (estoque == NULL || estoque->raiz == NULL){
        return true;
    }
    return false;
}

static Produto *produto_buscar_nome(Produto *no, const char *nome){
    if (no == NULL){
        return NULL;
    }
    if (comparar_sem_case(no->nome, nome) == 0){
        return no;
    }
    Produto *subs = produto_buscar_nome(no->esq, nome);
    if (subs != NULL){
        return subs;
    }else{
        return produto_buscar_nome(no->dir, nome);
    }
}

Produto *produto_search_name(const char *nome, Catalogo *control){
    if (control == NULL){
        return NULL;
    }
    return produto_buscar_nome(control->raiz, nome);
}

Produto *produto_search_code(uint64_t codigo, Catalogo *control){
    if (control == NULL){
        return NULL;
    }
    Produto *atual = control->raiz;
    while (atual != NULL){
        if (atual->codigo == codigo){
            return atual;
        }else if (atual->codigo < codigo){
            atual = atual->dir;
        }else{
            atual = atual->esq;
        }
    }
    return NULL;
}
uint64_t produto_get_code(Produto *produto){
    return produto->codigo;
}
const char *produto_get_name(Produto *produto){
    return produto->nome;
}
int produto_get_qtd(Produto *produto){
    return produto->qtd;
}
int produto_get_volume(Produto *produto){
    return produto->volume;
}

//UPDATE
bool produto_aumentar_estoque(Produto *produto, int qtd){
    if (produto == NULL){
        return false;
    }
    if (qtd <= 0 || produto->qtd > (INT_MAX - qtd)){
        return false;
    }
    produto->qtd += qtd;
    return true;
}
bool produto_descontar_estoque(Produto *produto, int qtd){
    if (produto == NULL){
        return false;
    }
    if (qtd <= 0){
        return false;
    }
    if (produto->qtd - qtd < 0){
        return false;
    }
    produto->qtd -= qtd;
    return true;
}

Produto *produto_cadastrar_estoque(const char *nome, int qtd, int volume, Catalogo *control){
    if (nome == NULL || control == NULL || qtd <= 0 || volume < PRODUTO_VOLUME_MIN || volume > PRODUTO_VOLUME_MAX){
        return NULL;
    }
    Produto *produto = (Produto *) malloc(sizeof(Produto));
    if (produto == NULL){
        return NULL;
    }
    char *name = (char *) malloc((strlen(nome)+1)*sizeof(char));
    if (name == NULL){
        free(produto);
        return NULL;
    }
    strcpy(name, nome);
    produto->nome   = name;
    produto->qtd    = qtd;
    produto->volume = volume;
    produto->codigo = produto_gerar_cod();
    produto_inserir(control, produto);
    return produto;
}

//DELETE
static void produto_liberar(Produto *produto){
    free(produto->nome);
    free(produto);
}

static void liberar_arvore(Produto *no){
    if (no == NULL){
        return;
    }
    liberar_arvore(no->esq);
    liberar_arvore(no->dir);
    produto_liberar(no);
}

void catalogo_liberar(Catalogo *control){
    if (control == NULL){
        return NULL;
    }
    liberar_arvore(control->raiz);
    Produto *atual = control->removidos;
    while (atual != NULL){
        Produto *prox = atual->esq;
        produto_liberar(atual);
        atual = prox;
    }
    free(control);
}

static Produto *destacar_minimo(Produto *no, Produto **min){
    if (no->esq == NULL){
        *min = no;
        return no->dir; 
    }else{
        no->esq = destacar_minimo(no->esq, min);
        return rebalancear(no);
    }
}//encontra o mínimo, remove da subárvore e reaponta o pai.

static Produto *remover_no(Produto *no, uint64_t codigo, Produto **removido){
    if (no == NULL){
        return NULL;
    }
    if (codigo < no->codigo){
        no->esq = remover_no(no->esq, codigo, removido);
    }else if (codigo > no->codigo){
        no->dir = remover_no(no->dir, codigo, removido);
    }else{
        if (no->esq != NULL){
            if (no->dir != NULL){
                Produto *suc;
                no->dir = destacar_minimo(no->dir, &suc);
                suc->esq = no->esq;
                suc->dir = no->dir;
                *removido = no;
                return rebalancear(suc);
            }else{
                *removido = no;
                return no->esq;
            }
        }else{
            *removido = no;
            return no->dir;
        }
    }
    return rebalancear(no);
}
bool catalogo_remover(Catalogo *control, uint64_t codigo){
    if (control == NULL){
        return false;
    }   
    Produto *removido = NULL;
    control->raiz = remover_no(control->raiz, codigo, &removido);
    if (removido == NULL){
        return false;
    }
    removido->esq = control->removidos;
    removido->dir = NULL;
    control->removidos = removido;
    return true;
}



