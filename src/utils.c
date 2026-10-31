#include "utils.h"
#include <stdio.h>
#include <string.h>

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

static char minusculizar(char c) {
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

bool apenas_espacos(const char *str){
    if (str[0] == '\0'){
        return false;
    }
    while (*str){
        if (*str != ' '){
            return false;
        }
        str++;
    }
    return true;
}

bool ler_string(char *dest, int tamanho){
    if (fgets(dest, tamanho, stdin) != NULL){
        size_t len = strlen(dest);
        if (len > 0 && dest[len-1] == '\n'){
            dest[len-1] = '\0';
        }else{
            limpar_buffer();
        }
        return true;
    }else{
        dest[0] = '\0';
        return false;
    }
}

int ler_int(int *var){
    int res = scanf("%d", var);
    if (res != 1){
        if (res == EOF) {
            limpar_buffer();
            return EOF;
        }
        limpar_buffer();
        return 0;
    }
    limpar_buffer();
    return 1;
}