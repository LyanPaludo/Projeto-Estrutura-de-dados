#ifndef UTILS_H
#define UTILS_H

void limpar_buffer(void);//limpar buffer depois do scanf
char minusculizar(char c);//deixar uma letra minúscula
int comparar_sem_case(const char *s1, const char *s2); //checar se duas strings são iguais (sem diferenciar maiúsculas de minúsculas)
void limpar_tela(void); // Limpar terminal
void pausar(void);      // Pausar até apertar enter
void ler_string(char *dest, int tamanho);//Função para ler string limitada e limpar excedentes;
#endif 