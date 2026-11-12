#include "caminhao.h"
#include "fila.h"
#include <stdlib.h>

struct Caminhao{
    int numero;
    int capacidade;
    int usado;
    Fila *pacotes;
};

//create
Caminhao *caminhao_criar(int numero, int capacidade){
    if (capacidade < PACOTE_CAPACIDADE || numero < 1){
        return NULL;
    }
    Caminhao *cmn = (Caminhao *) malloc(sizeof(Caminhao));
    if (cmn == NULL){
        return NULL;
    }
    cmn->pacotes = fila_criar();
    if (cmn->pacotes == NULL){
        free(cmn);
        return NULL;
    }
    cmn->capacidade = capacidade;
    cmn->numero = numero;
    cmn->usado = 0;
    return cmn;
}

//read
bool caminhao_cabe(Caminhao *cmn, Pacote *pacote){
    if (cmn == NULL || pacote == NULL){
        return false;
    }
    if (cmn->usado + pacote_get_volume(pacote) > cmn->capacidade){
        return false;
    }
    return true;
}
bool caminhao_cheio(Caminhao *cmn){
    if (cmn == NULL){
        return false;
    }
    return cmn->capacidade == cmn->usado;
   
}
void caminhao_percorrer(Caminhao *cmn, void (*visitar)(void *dado)){
    if (cmn == NULL){
        return;
    }
    fila_percorrer(cmn->pacotes, visitar);
}
int caminhao_get_numero(Caminhao *cmn){
    return cmn->numero;
}
int caminhao_get_capacidade(Caminhao *cmn){
    return cmn->capacidade;
}
int caminhao_get_usado(Caminhao *cmn){
    return cmn->usado;
}
int caminhao_get_qtd(Caminhao *cmn){
    return fila_tamanho(cmn->pacotes);
}

//update
bool caminhao_carregar(Caminhao *cmn, Pacote *pacote){
    if (cmn == NULL || pacote == NULL){
        return false;
    }
    if (!caminhao_cabe(cmn, pacote)){
        return false;
    }
    if (!fila_enfileirar(cmn->pacotes, pacote)){
        return false;
    }
    cmn->usado += pacote_get_volume(pacote);
    return true;
}

//delete
static void liberar_pacote_void(void *dado){ 
    pacote_liberar((Pacote *)dado); 
}
void caminhao_liberar(Caminhao *cmn){
    if (cmn == NULL){
        return;
    }
    fila_liberar(cmn->pacotes, liberar_pacote_void);
    free(cmn);
}
