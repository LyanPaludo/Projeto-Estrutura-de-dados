#include "expedicao.h"
#include "fila.h"
#include "utils.h"
#include <stdlib.h>

struct Expedicao{
    Caminhao *docas[NUM_DOCAS];
    Fila *historico;
    int prox_num;
};

//create
static int sortear_capacidade(void){
    int a = sortear(3);
    switch (a){
        case 0:
            return CAMINHAO_CAP_PEQUENO;
        case 1:
            return CAMINHAO_CAP_MEDIO;
        default:
            return CAMINHAO_CAP_GRANDE;
    }
}
static Caminhao *novo_caminhao(Expedicao *exp){
    int cap = sortear_capacidade();
    Caminhao *caminhao = caminhao_criar(exp->prox_num, cap);
    if (caminhao == NULL){
        return NULL;
    }
    exp->prox_num++;
    return caminhao;
}

Expedicao *expedicao_criar(void){
    Expedicao *exp = (Expedicao *) malloc(sizeof(Expedicao));
    if (exp == NULL){
        return NULL;
    }
    exp->historico = fila_criar();
    if (exp->historico == NULL){
        free(exp);
        return NULL;
    }
    exp->prox_num = 1;
    for (int i=0; i<NUM_DOCAS; i++){
        exp->docas[i] = novo_caminhao(exp);
        if (exp->docas[i] == NULL){
            for (int j=0; j<i; j++){
                caminhao_liberar(exp->docas[j]);
            }
            fila_liberar(exp->historico, NULL);
            free(exp);
            return NULL;
        }
    }
    return exp;
}

//read
static int doca_mais_cheia(Expedicao *exp){
    int maisCheia = 0;
    int ind = 0;
    for (int i=0; i<NUM_DOCAS; i++){
        int atual = caminhao_get_usado(exp->docas[i]);
        if (atual > maisCheia){
            maisCheia = atual;
            ind = i;
        }
    }
    return ind;
}

Caminhao *expedicao_get_doca(Expedicao *exp, int i){
    if (exp == NULL || i < 0 || i >= NUM_DOCAS){
        return NULL;
    }
    return exp->docas[i];
}

int expedicao_historico_tamanho(Expedicao *exp){
    return fila_tamanho(exp->historico);
}

void expedicao_percorrer_historico(Expedicao *exp, void (*visitar)(void *)){
    fila_percorrer(exp->historico, visitar);
}

//update
static bool despachar_doca(Expedicao *exp, int i){
    Caminhao *new_caminhao = novo_caminhao(exp);
    if (new_caminhao == NULL){
        return false;
    }
    if (!fila_enfileirar(exp->historico, exp->docas[i])){
        caminhao_liberar(new_caminhao);
        exp->prox_num--;
        return false;
    }
    exp->docas[i] = new_caminhao;
    return true;
}

bool expedicao_expedir(Expedicao *exp, FilaPrioridade *pacotes){
    if (exp == NULL || pacotes == NULL){
        return false;
    }
    Pacote *pack = fila_prioridade_desenfileirar(pacotes);
    while (pack != NULL){
        bool carregado = false;
        while (!carregado){
            for (int i=0; i<NUM_DOCAS; i++){
                if (caminhao_cabe(exp->docas[i], pack)){
                    if (!caminhao_carregar(exp->docas[i], pack)){
                        pacote_liberar(pack);
                        return false;
                    }
                    carregado = true;
                    if (caminhao_cheio(exp->docas[i])){
                        if (!despachar_doca(exp, i)){
                            return false;
                        }
                    }
                    break;
                }
                
            }
            if (!carregado){
                int i = doca_mais_cheia(exp);
                if (!despachar_doca(exp, i)){
                    pacote_liberar(pack);
                    return false;
                }       
            }
        }
        pack = fila_prioridade_desenfileirar(pacotes);
    }
    for (int i=0; i<NUM_DOCAS; i++){
        if (caminhao_get_qtd(exp->docas[i]) > 0){
            if (!despachar_doca(exp, i)){
                return false;
            }
        }
    }
    return true;
}

//delete
static void liberar_caminhao_void(void *dado){ 
    caminhao_liberar((Caminhao *)dado); 
}
void expedicao_liberar(Expedicao *exp){
    if (exp == NULL){
        return;
    }
    for (int i=0; i<NUM_DOCAS; i++){
        caminhao_liberar(exp->docas[i]);
    }
    fila_liberar(exp->historico, liberar_caminhao_void);
    free(exp);
}
