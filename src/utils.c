#include "utils.h"
#include <stdio.h>

void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void limpar_tela(void) {
    printf("\033[H\033[2J");
}

void pausar(void) {
    printf("\nPressione [Enter] para continuar...");
    getchar();
    limpar_tela();
}

char minusculizar(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + 32; //'a' até 'A' é 32 em ASCII
    }
    return c;
}//Função auxiliar para comparar_sem_case
int comparar_sem_case(const char *s1, const char *s2) { 
    while (*s1 && *s2) {
        char c1 = minusculizar(*s1);
        char c2 = minusculizar(*s2);
        if (c1 != c2) {
            return (unsigned char)c1 - (unsigned char)c2;
        }
        s1++;
        s2++;
    }    
    return (unsigned char)minusculizar(*s1) - (unsigned char)minusculizar(*s2);
}