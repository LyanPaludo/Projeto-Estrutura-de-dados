#ifndef UTILS_H
#define UTILS_H
#include <stdbool.h>

void limpar_buffer(void);//limpar buffer depois do scanf
int comparar_sem_case(const char *s1, const char *s2); //checar se duas strings são iguais (sem diferenciar maiúsculas de minúsculas)
void limpar_tela(void); // Limpar terminal
void pausar(void);      // Pausar até apertar enter
bool apenas_espacos(const char *str); // verifica se só tem espaço em uma string
bool ler_string(char *dest, int tamanho);//Função para ler string limitada e limpar excedentes;
int ler_int(int *var);//Função auxiliar para ler inteiro (1: leu, 0: entrada inválida, EOF: fim de arquivo)
void iniciar_sorteio(void);// Função para iniciar a seed pseudoaleatória
int sortear(int n);// Função para sortear um número inteiro pseudoaleatório de 0 até n-1.
#endif  