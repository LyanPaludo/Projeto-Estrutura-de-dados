# Projeto de estrutura de dados

Simulação em C do fluxo de um centro de distribuição (cadastro de produtos, fila de pedidos e montagem de pacotes) usando TADs de lista encadeada, fila e pilha.

## Sobre o projeto

Projeto desenvolvido na disciplina de Estrutura de Dados e Programação (2º semestre de Engenharia de Computação). Simula, em C, o fluxo de um centro de distribuição fictício, aplicando TADs, listas encadeadas, filas e pilhas.

## Funcionalidades

*Atualmente o sistema é capaz de cadastrar um produto e listar todos os produtos cadastrados, cadastrar um pedido e listar todos os pedidos cadastrados em ordem de cadastro.*

## Estruturas de dados utilizadas

**Lista encadeada**: Armazenar os produtos, perfeita para adicionar um novo produto à lista e remover, caso necessário, facilitando a manipulação da lista.

**Fila**: Uma lista encadeada onde é sempre o primeiro elemento quem é removido e os elementos são adicionados ao final. Utilizada para listar os pedidos em ordem de cadastro. OBS: Utilizado ponteiro genérico void *, já que a fila também será usada para as caixas e para evitar repetição de código.

> *Para cada estrutura (lista, fila, pilha), uma linha dizendo onde ela é usada no sistema e por que foi a escolha adequada.*

## Regras de negócio adotadas

> *As simplificações e regras que implementei (capacidade da caixa, faixa de volume dos produtos, ordem de empacotamento, etc.). Útil para o professor ver que você entendeu o enunciado.*

## Organização do projeto

No momento:

**main.c** -> Loop principal.

**utils.c/.h** -> Armazena as funções utilitárias, como "limpar_buffer".

**display.c/.h** -> Armazena as funções que apenas imprimem na tela, como "imprimir_produto" e "imprimir_lista_produtos".

**interface.c/.h** -> Armazena as funções de interação com o usuário, como "cadastrar_produto".

**lista_produtos.c/.h** -> TAD que armazena as funções relacionadas aos produtos e à lista de produtos.

pedido.c/.h -> TAD que armazena as funções relacionadas aos pedidos.

fila.c/.h -> TAD que armazena as funções relacionadas às filas (uso de void * para encaixar tanto as filas de pedidos quanto as de pacotes).

cores.h -> Header contendo as cores para o display e interface.

(extra) teste_fila.c -> Arquivo para testar se o arquivo da fila estava funcionando, antes de conectar o restante do projeto.

## Como compilar e executar

Ter GCC (minGW) ou MSVC instalado, para compilar e executar (na pasta raíz):

Compilar para DEBUG:

```plaintext
gcc -Wall -Wextra -std=c99 -pedantic -g src/main.c src/utils.c src/lista_produtos.c src/interface.c src/display.c src/pedido.c src/fila.c -o programa.exe
./programa
```

Compilar para RELEASE:

```plaintext
gcc src/main.c src/utils.c src/lista_produtos.c src/interface.c src/display.c src/pedido.c src/fila.c -o programa.exe
./programa
```

## Como usar

Ao executar:

1 -> cadastro do produto, escreva nome, quantidade e o volume que ele ocupa no estoque (unitário)

2 -> cadastro do pedido, escreva o endereço que deseja enviar, o código do produto e quantos quer pedir

3 -> visualizar lista de produtos, ver todos os produtos disponíveis no estoque, quantia e volume.

4 -> visualizar fila de pedidos, ver a fila de pedidos em ordem crescente.

0 -> finalizar

## Decisões de projeto e dificuldades

Optei por separar as funções auxiliares em um utils.c, pois acabava usando-as em todos os outros módulos.

Optei por usar um TAD para cada estrutura (atualmente conta apenas com o lista_produtos.c), cada TAD é encapsulado, outros módulos só conseguem acessar via função.

Optei pelo uso de dois TADs separando a interface, um apenas para imprimir e outro para interagir, pois as funções que apenas imprimiam acabavam recebendo muitos includes não necessários.

Optei pelo uso de uint64_t para os IDs, pensei em usar UUID o que torna infinitas as possibilidades, mas achei muito complexo para entender. Pesquisei, e encontrei o uint64_t que é um inteiro unsigned com 64 bits ao invés de 32, apesar de ocupar o dobro de memória em relação ao inteiro comum, a quantidade de identificadores que o uint64_t é em torno de 8,76 bilhões de vezes maior do que o do inteiro comum (int32_t), isso acontece pois dobra a quantidade de bytes e não considera números negativos (unsigned). OBS: no fim não vai ter tanto ID, usei este mais para ver como é...

Estoque descontado na separação com validação tudo-ou-nada, pedido sem estoque permanece na frente da fila, código gerado uint64_t, destino em texto fixo, item com ponteiro, fila com void *.

TADs: o nome começa pelo tipo que a função recebe ou cria, depois o verbo.  
Interface e display: verbo primeiro, o que recebe depois.

Optei pelo uso de ponteiro genérico (void *) para não ter que escrever dois tads de fila (uma para o pacote e outra para os pedidos), dessa forma um único arquivo consegue desreferenciar a fila em pedido ou em pacote.

## Limitações conhecidas e próximos passos

Scan de valores inteiros, como quantidade ou volume funcionam com entradas como "12abc", armazenando apenas o 12 (considerado aceitável).

## Checklist de desenvolvimento

- [x] Criar a estrutura inicial do repositório e adicionar o `menu.c` fornecido
- [x] Implementar o TAD de lista simplesmente encadeada (base para produtos e itens)
- [x] Implementar o cadastro de produtos com as validações exigidas
- [x] Implementar o cadastro de pedidos com sua lista de itens
- [x] Implementar o TAD de fila e enfileirar os pedidos
- [ ] Implementar o TAD de pilha
- [ ] Implementar a separação dos pedidos seguindo a ordem da fila
- [ ] Implementar a montagem dos pacotes usando a pilha e a regra de capacidade
- [ ] Implementar a fila de pacotes prontos para expedição
- [ ] Integrar todas as funcionalidades ao menu principal
- [ ] Revisar tratamento de erros e liberar toda a memória alocada
- [ ] Testar diferentes cenários e corrigir problemas encontrados
- [ ] Comentar o código e finalizar o README
