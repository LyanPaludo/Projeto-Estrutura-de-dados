#ifndef UTILS_H
#define UTILS_H
#include <stdbool.h>

void limpar_buffer(void);//limpar buffer depois do scanf
int comparar_sem_case(const char *s1, const char *s2); //checar se duas strings são iguais (sem diferenciar maiúsculas de minúsculas)
void limpar_tela(void); // Limpar terminal
void pausar(void);      // Pausar até apertar enter
bool ler_string(char *dest, int tamanho);//Função para ler string limitada e limpar excedentes;
int ler_int(int *var);//Função auxiliar para ler inteiro (1: leu, 0: entrada inválida, EOF: fim de arquivo)
#endif 