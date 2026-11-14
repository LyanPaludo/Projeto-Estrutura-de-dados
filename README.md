# Projeto de estrutura de dados

Simulação em C do fluxo de um centro de distribuição (cadastro de produtos, fila de pedidos e montagem de pacotes) usando TADs de lista encadeada, fila e pilha.

## Sobre o projeto

Projeto desenvolvido na disciplina de Estrutura de Dados e Programação (2º semestre de Engenharia de Computação). O sistema simula (em C) o fluxo de um centro de distribuição fictício, da criação do pedido até a expedição dos pacotes em caminhões, passando pela fila de pacotes prontos. 

## Funcionalidades

Atualmente o sistema é capaz de cadastrar um produto e listar todos os produtos cadastrados, cadastrar um pedido e listar todos os pedidos cadastrados em ordem de cadastro, separar o próximo pedido da fila e listar todos os pacotes já prontos. Também é capaz de remover produtos do catálogo, expedir os pacotes (por prioridade) em caminhões nas 5 docas, mostrar o estado das docas e o histórico dos caminhões que já saíram.

## Estruturas de dados utilizadas

**Árvore binária de busca (ABB):** armazena o catálogo de produtos, ordenada pelo código do produto. Substituiu a lista encadeada da Parte 1. Tem inserção, busca por código, busca por nome (percurso completo, pois a árvore não está ordenada por nome), listagem em ordem crescente de código (percurso em ordem), remoção e liberação (pós-ordem). Utilizada em catalogo.

**Lista encadeada**: Armazenar os itens de cada pedido, perfeita para adicionar um novo item ao final. Utilizada em pedido. (Na Parte 1 também guardava os produtos.)

**Fila**: Uma lista encadeada onde é sempre o primeiro elemento quem é removido e os elementos são adicionados ao final (FIRST IN FIRST OUT). Utilizada para listar os pedidos em ordem de cadastro. *OBS*: *Utilizado ponteiro genérico void *, já que a fila também será usada para as caixas e para evitar repetição de código.*

**Fila de prioridade**: composição de três filas simples, uma por prioridade (Expressa > Rápida > Normal). Enfileirar coloca o pacote na fila da sua prioridade; desenfileirar sempre tira da primeira fila não vazia. Dentro da mesma prioridade a ordem de chegada é mantida pelo próprio FIFO de cada fila, sem precisar de contador ou timestamp. Utilizada em fila_prioridade e para os pacotes prontos para expedição.

**Pilha**: Ao contrário da fila, a pilha é uma lista onde o último elemento à entrar é sempre o primeiro à sair (LAST IN FIRST OUT), igual uma pilha de fato. Utilizada para armazenar os produtos de cada pedido dentro de um pacote. Utilizado em pacote e pilha.

## Regras de negócio adotadas

Todas as regras gerais estão definidas em constantes.h, como a capacidade do pacote (PACOTE_CAPACIDADE), o volume do produto (PRODUTO_VOLUME_MIN e MAX, etc...), o número de docas (NUM_DOCAS), as capacidades dos caminhões (30, 50 e 80) e o enum de prioridades de forma que caso no futuro seja necessário alterar esses valores, fique mais fácil.

## Organização do projeto

No momento:

**main.c** -> Loop principal.

**utils.c/.h** -> Armazena as funções utilitárias.

**display.c/.h** -> Armazena as funções que apenas imprimem na tela.

**interface.c/.h** -> Armazena as funções de interação com o usuário.

**catalogo.c/.h** -> TAD que armazena as funções relacionadas aos produtos e ao catálogo.

**pedido.c/.h** -> TAD que armazena as funções relacionadas aos pedidos.

**fila.c/.h** -> TAD que armazena as funções relacionadas às filas.

**fila_prioridade.c/.h** -> TAD da fila de prioridade (usa três filas por dentro).

**pilha.c/.h** -> TAD que armazena as funções relacionadas às pilhas.

**pacotes.c/.h** -> TAD que armazena as funções relacionadas aos pacotes.

**separacao.c/.h** -> TAD que armazena as funções relacionadas à separação dos produtos dos pedidos do estoque e inserção em pacotes.

**caminhao.c/.h** -> TAD de um caminhão: capacidade, volume usado e os pacotes carregados.

**expedicao.c/.h** -> TAD das 5 docas: sorteia caminhões, carrega os pacotes, aplica as regras de saída e guarda o histórico dos caminhões despachados.

**constantes.h** -> Header contendo as regras adotadas, capacidades, volume máximo e mínimo, tamanho de variáveis, etc...

**cores.h** -> Header contendo as cores para o display e interface.

## Como compilar e executar

Ter GCC (minGW) ou MSVC instalado, para compilar e executar (na pasta raíz):

Compilar para DEBUG:

```plaintext
gcc -Wall -Wextra -std=c99 -pedantic -g src/main.c src/utils.c src/catalogo.c src/interface.c src/display.c src/pedido.c src/fila.c src/fila_prioridade.c src/pilha.c src/pacote.c src/separacao.c src/caminhao.c src/expedicao.c -o programa.exe
./programa
```

Compilar para RELEASE:

```plaintext
gcc src/main.c src/utils.c src/catalogo.c src/interface.c src/display.c src/pedido.c src/fila.c src/fila_prioridade.c src/pilha.c src/pacote.c src/separacao.c src/caminhao.c src/expedicao.c -o programa.exe
./programa
```

## Como usar

Ao executar:

1 -> cadastro do produto, escreva nome, quantidade e o volume que ele ocupa no estoque (unitário). OBS: se o nome já existir, a quantidade é somada e o volume antigo é mantido.

2 -> cadastro do pedido, escreva o endereço que deseja enviar, o código do produto e quantos quer pedir.

3 -> visualizar lista de produtos disponíveis no estoque: nome, quantia e volume, em ordem crescente do código.

4 -> visualizar fila de pedidos, ver a fila de pedidos em ordem crescente.

5 -> separar o próximo pedido (tirar produtos do estoque e colocar em pacotes com prioridade sorteada).

6 -> visualizar todos os pacotes prontos, na ordem de que serão expedidos.

7 -> expedir pacotes: esvazia a fila de prioridade carregando os pacotes nos caminhões das docas.

8 -> ver as 5 docas: capacidade, volume usado e pacotes de cada caminhão.

9 -> ver o histórico dos caminhões que já saíram e o que cada um levou.

10 -> remover produto do catálogo (não aparece mais na listagem nem em novos pedidos), mas pedidos e pacotes já criados com ele continuam válidos.

0 -> libera a memória e encerra o programa.

67 -> opção oculta de testes:

- 1: importa/reabastece PC-1 a PC-10 com 10 unidades cada e volumes de 1 a 10.
- 2: enxurrada de pedidos, um pedido para cada produto PC.
- 3: pacotes misteriosos: cria um pacote de uma unidade para cada PC presente no catálogo, com prioridade sorteada, direto na fila de prioridade e sem mexer no estoque.

## Decisões de projeto e dificuldades

Optei por separar as funções auxiliares em um utils.c, pois acabava usando-as em todos os outros módulos.

Optei por usar um TAD para cada estrutura, cada TAD é encapsulado, outros módulos só conseguem acessar via função.

Optei pelo uso de dois TADs separando a interface, um apenas para imprimir e outro para interagir, pois as funções que apenas imprimiam acabavam recebendo muitos includes não necessários.

Optei pelo uso de uint64_t para os IDs, pensei em usar UUID o que torna infinitas as possibilidades, mas achei muito complexo para entender. Pesquisei, e encontrei o uint64_t que é um inteiro unsigned com 64 bits ao invés de 32, apesar de ocupar o dobro de memória em relação ao inteiro comum, a quantidade de identificadores que o uint64_t é em torno de 8,59 bilhões de vezes maior do que o do inteiro comum (int32_t), isso acontece pois dobra a quantidade de bytes, elevando ao quadrado a quantidade de valores, e não considera números negativos (unsigned). OBS: no fim não vai ter tanto ID, usei este mais para ver como é...

Estoque descontado na separação com validação completa, ou seja, se não ter estoque para TODO o pedido, ele não vai separar. Pedido sem estoque permanece na frente da fila até a reposição.

TADs: o nome das funções começa pelo tipo que a função recebe ou cria, depois o verbo (Ex: pilha_empilhar).  
Já na Interface e no display: o verbo primeiro, o que recebe depois.

Optei pelo uso de ponteiro genérico (void *) para não ter que escrever vários TADs de fila (pedidos, pacotes, caminhões) dessa forma um único arquivo consegue desreferenciar a fila em pedido ou em pacote.

Ponteiro pendurado: o produto removido sai da árvore, mas não recebe free. Ele vai para uma lista interna de removidos do catálogo (reaproveitando o ponteiro esq) e só é liberado em catalogo_liberar, no encerramento. Assim pedidos e pacotes já criados continuam apontando para um produto válido. Foi preferido a bloquear a remoção ou usar contador de referências, porque os pacotes despachados ficam no histórico até o fim do programa.

Optei pelo uso de prioridade por pedido, e não por pacote.

## Limitações conhecidas e próximos passos

Scan de valores inteiros, como quantidade ou volume funcionam com entradas como "12abc", armazenando apenas o 12 (considerado aceitável).

O contador do PED (ID do pedido) aumenta mesmo se o usuário cancelar, causando buracos entre um pedido e outro (considerado aceitável)

Um pedido sem estoque trava a fila até alguém repor, ele manda devolta ao menu e espera a reposição, (considerado aceitável).

Se o malloc falhar no meio da montagem do pacote, o estoque já foi descontado e alguns pacotes podem já estar na fila (considerado mais ou menos aceitável -> já que considero falta de memória uma exceção);

A função ler_string (utils) da B.O com uma string de mais de 127 bytes. (considerado mais ou menos aceitável)

A função comparar_sem_case (também do utils) só diferencia maiúsculas e minúsculas em ASCII, mas acentos como Á e á são tratados como diferentes. (considerado aceitável)

A função apenas_espaços só reconhece espaço comum, se o usuário apertar tab várias vezes o nome fica vazio e o programa não reclama (considerao aceitável).

Scanf("%d") ignora linhas em branco, então o usuário pode apertar um monte de enter e o programa ignora.

Árvore inclinada: os códigos dos produtos são sequenciais (1, 2, 3...), então cada novo produto vai sempre para a direita e a BST vira, na prática, uma lista. A busca por código custa O(n) em vez de O(log n). A solução seria balancear a árvore (AVL, ou ARN), deixada como melhoria futura por não ser pedida e por arriscar o que já funciona.

- Pelo mesmo motivo, o caso de remoção de nó com dois filhos está implementado, mas não acontece no uso normal do programa (nenhum nó tem dois filhos com códigos sequenciais).
- A listagem, a busca por nome e a liberação da árvore são recursivas e, com a árvore inclinada, a profundidade é igual ao número de produtos. Com dezenas de milhares de produtos a pilha do programa poderia estourar (considerado aceitável para a simulação).

Produtos removidos só são liberados no encerramento (considerado aceitável).

Se a expedição falhar por falta de memória, os pacotes que sobraram continuam na fila de prioridade e são liberados no encerramento.

Os caminhões despachados ficam no histórico (e na memória) até o encerramento.

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

## **Checklist de desenvolvimento (PARTE 2)**

- [x] **Substituir a lista de produtos por uma ABB (TAD catalogo), mantendo a interface**
- [x] **Implementar busca por código, busca por nome, inserção e listagem em ordem**
- [x] **Implementar a remoção na ABB (três casos)**
- [x] **Adicionar prioridade (sorteada) aos pacotes**
- [x] **Implementar o TAD de fila de prioridade e trocar a fila de pacotes**
- [x] **Implementar o TAD de caminhão**
- [x] **Implementar a expedição com 5 docas em vetor e as regras de saída dos caminhões**
- [x] **Integrar ao menu: expedir, ver docas, ver histórico e remover produto**

- [ ] **Revisão final, teste do fluxo completo e conferência de vazamentos**
