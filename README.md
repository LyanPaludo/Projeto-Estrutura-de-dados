# Projeto de estrutura de dados

Simulação em C do fluxo de um centro de distribuição (cadastro de produtos, fila de pedidos e montagem de pacotes) usando TADs de lista encadeada, fila e pilha.

## Sobre o projeto

Projeto desenvolvido na disciplina de Estrutura de Dados e Programação (2º semestre de Engenharia de Computação). O sistema simula (em C) o fluxo de um centro de distribuição fictício, da criação do pedido até a fila de pacotes prontos para expedição.

## Funcionalidades

*Atualmente o sistema é capaz de cadastrar um produto e listar todos os produtos cadastrados, cadastrar um pedido e listar todos os pedidos cadastrados em ordem de cadastro, separar o próximo pedido da fila e listar todos os pacotes já prontos.*

## Estruturas de dados utilizadas

**Lista encadeada**: Armazenar os produtos, perfeita para adicionar um novo produto à lista e remover, caso necessário, facilitando a manipulação da lista. Utilizada em lista_produtos e pedido.

**Fila**: Uma lista encadeada onde é sempre o primeiro elemento quem é removido e os elementos são adicionados ao final (FIRST IN FIRST OUT). Utilizada para listar os pedidos em ordem de cadastro. *OBS*: *Utilizado ponteiro genérico void *, já que a fila também será usada para as caixas e para evitar repetição de código.*

**Pilha**: Ao contrário da fila, a pilha é uma lista onde o último elemento à entrar é sempre o primeiro à sair (LAST IN FIRST OUT), igual uma pilha de fato. Utilizada para armazenar os produtos de cada pedido dentro de um pacote. Utilizado em pacote e pilha.

## Regras de negócio adotadas

Todas as regras gerais estão definidas em constantes.h, como a capacidade do pacote (PACOTE_CAPACIDADE), o volume do produto (PRODUTO_VOLUME_MIN e MAX, etc...) de forma que caso no futuro seja necessário alterar esses valores, fique mais fácil.

## Organização do projeto

No momento:

**main.c** -> Loop principal.

**utils.c/.h** -> Armazena as funções utilitárias.

**display.c/.h** -> Armazena as funções que apenas imprimem na tela.

**interface.c/.h** -> Armazena as funções de interação com o usuário.

**lista_produtos.c/.h** -> TAD que armazena as funções relacionadas aos produtos e à lista de produtos.

**pedido.c/.h** -> TAD que armazena as funções relacionadas aos pedidos.

**fila.c/.h** -> TAD que armazena as funções relacionadas às filas.

**pilha.c/.h** -> TAD que armazena as funções relacionadas às pilhas.

**pacotes**.c/.h -> TAD que armazena as funções relacionadas aos pacotes.

**separacao**.c/.h -> TAD que armazena as funções relacionadas à separação dos produtos dos pedidos do estoque e inserção em pacotes.

**constantes.h** -> Header contendo as regras adotadas, capacidades, volume máximo e mínimo, tamanho de variáveis, etc...

**cores.h** -> Header contendo as cores para o display e interface.

## Como compilar e executar

Ter GCC (minGW) ou MSVC instalado, para compilar e executar (na pasta raíz):

Compilar para DEBUG:

```plaintext
gcc -Wall -Wextra -std=c99 -pedantic -g src/main.c src/utils.c src/lista_produtos.c src/interface.c src/display.c src/pedido.c src/fila.c src/pilha.c src/pacote.c src/separacao.c -o programa.exe
./programa
```

Compilar para RELEASE:

```plaintext
gcc src/main.c src/utils.c src/lista_produtos.c src/interface.c src/display.c src/pedido.c src/fila.c src/pilha.c src/pacote.c src/separacao.c -o programa.exe
./programa
```

## Como usar

Ao executar:

1 -> cadastro do produto, escreva nome, quantidade e o volume que ele ocupa no estoque (unitário). OBS: se o nome já existir, a quantidade é somada e o volume antigo é mantido.

2 -> cadastro do pedido, escreva o endereço que deseja enviar, o código do produto e quantos quer pedir.

3 -> visualizar lista de produtos disponíveis no estoque: nome, quantia e volume.

4 -> visualizar fila de pedidos, ver a fila de pedidos em ordem crescente.

5 -> separar o próximo pedido (tirar produtos do estoque e colocar em pacotes).

6 -> visualizar todos os pacotes prontos.

0 -> libera a memória e encerra o programa.

## Decisões de projeto e dificuldades

Optei por separar as funções auxiliares em um utils.c, pois acabava usando-as em todos os outros módulos.

Optei por usar um TAD para cada estrutura, cada TAD é encapsulado, outros módulos só conseguem acessar via função.

Optei pelo uso de dois TADs separando a interface, um apenas para imprimir e outro para interagir, pois as funções que apenas imprimiam acabavam recebendo muitos includes não necessários.

Optei pelo uso de uint64_t para os IDs, pensei em usar UUID o que torna infinitas as possibilidades, mas achei muito complexo para entender. Pesquisei, e encontrei o uint64_t que é um inteiro unsigned com 64 bits ao invés de 32, apesar de ocupar o dobro de memória em relação ao inteiro comum, a quantidade de identificadores que o uint64_t é em torno de 8,59 bilhões de vezes maior do que o do inteiro comum (int32_t), isso acontece pois dobra a quantidade de bytes, elevando ao quadrado a quantidade de valores, e não considera números negativos (unsigned). OBS: no fim não vai ter tanto ID, usei este mais para ver como é...

Estoque descontado na separação com validação completa, ou seja, se não ter estoque para TODO o pedido, ele não vai separar. Pedido sem estoque permanece na frente da fila até a reposição.

**TADs**: o nome das funções começa pelo tipo que a função recebe ou cria, depois o verbo (Ex: pilha_empilhar).  
Já na **Interface e no display**: o verbo primeiro, o que recebe depois.

Optei pelo uso de ponteiro genérico (void *) para não ter que escrever dois tads de fila (uma para o pacote e outra para os pedidos), dessa forma um único arquivo consegue desreferenciar a fila em pedido ou em pacote.

## Limitações conhecidas e próximos passos

Scan de valores inteiros, como quantidade ou volume funcionam com entradas como "12abc", armazenando apenas o 12 (considerado aceitável).

O contador do PED (ID do pedido) aumenta mesmo se o usuário cancelar, causando buracos entre um pedido e outro (considerado aceitável)

Um pedido sem estoque trava a fila até alguém repor, ele manda devolta ao menu e espera a reposição, (considerado aceitável).

Se o malloc falhar no meio da montagem do pacote, o estoque já foi descontado e alguns pacotes podem já estar na fila (considerado mais ou menos aceitável -> já que considero falta de memória uma exceção);

A função ler_string (utils) da B.O com uma string de mais de 127 bytes. (considerado mais ou menos aceitável)

A função comparar_sem_case (também do utils) só diferencia maiúsculas e minúsculas em ASCII, mas acentos como Á e á são tratados como diferentes. (considerado aceitável)

A função apenas_espaços só reconhece espaço comum, se o usuário apertar tab várias vezes o nome fica vazio e o programa não reclama (considerao aceitável).

Scanf("%d") ignora linhas em branco, então o usuário pode apertar um monte de enter e o programa ignora.

Não há remoção de produtos (considerado, por hora)

## Checklist de desenvolvimento (PARTE 1)

- [x] Criar a estrutura inicial do repositório e adicionar o `menu.c` fornecido
- [x] Implementar o TAD de lista simplesmente encadeada (base para produtos e itens)
- [x] Implementar o cadastro de produtos com as validações exigidas
- [x] Implementar o cadastro de pedidos com sua lista de itens
- [x] Implementar o TAD de fila e enfileirar os pedidos
- [x] Implementar o TAD de pilha
- [x] Implementar a separação dos pedidos seguindo a ordem da fila
- [x] Implementar a montagem dos pacotes usando a pilha e a regra de capacidade
- [x] Implementar a fila de pacotes prontos para expedição
- [x] Integrar todas as funcionalidades ao menu principal
- [x] Revisar tratamento de erros e conferir vazamentos de memória
- [x] Testar diferentes cenários e corrigir problemas encontrados
- [x] Comentar o código e finalizar o README
