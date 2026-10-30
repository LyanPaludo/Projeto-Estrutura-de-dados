# Projeto de estrutura de dados

Simulação em C do fluxo de um centro de distribuição (cadastro de produtos, fila de pedidos e montagem de pacotes) usando TADs de lista encadeada, fila e pilha.

## Sobre o projeto

Projeto desenvolvido na disciplina de Estrutura de Dados e Programação (2º semestre de Engenharia de Computação). Simula, em C, o fluxo de um centro de distribuição fictício, aplicando TADs, listas encadeadas, filas e pilhas.

## Funcionalidades

> *Atualmente o sistema é capaz de cadastrar um produto e listar todos os produtos cadastrados.*

## Estruturas de dados utilizadas

**Lista encadeada**: Armazenar os produtos, perfeita para adicionar um novo produto à lista e remover, caso necessário, facilitando a manipulação da lista.

> *Para cada estrutura (lista, fila, pilha), uma linha dizendo onde ela é usada no sistema e por que foi a escolha adequada.*

## Regras de negócio adotadas

> *As simplificações e regras que implementei (capacidade da caixa, faixa de volume dos produtos, ordem de empacotamento, etc.). Útil para o professor ver que você entendeu o enunciado.*

## Organização do projeto

No momento:

**main.c** -> Loop principal;

**utils.c/.h** -> Armazena as funções utilitárias, como "limpar_buffer";

**display.c/.h** -> Armazena as funções que apenas imprimem na tela, como "imprimir_produto" e "imprimir_lista";

**interface.c/.h** -> Armazena as funções de interação com o usuário, como "cadastrar_produto";

**lista_produtos.c/.h** -> Armazena as funções relacionadas aos produtos e à lista de produtos.

> *Árvore de pastas/arquivos e uma frase sobre o papel de cada TAD (.h e .c). Explique também o que é o* `main`

## Como compilar e executar

Ter GCC (minGW) ou MSVC instalado, para compilar e executar (na pasta raíz):

```plaintext
gcc src/main.c src/utils.c src/lista_produtos.c src/interface.c src/display.c -o programa.exe
./programa
```

## Como usar

> *Passo a passo curto de uso do menu, com um exemplo de fluxo (cadastrar produto, cadastrar pedido, ver o resultado). Prints do terminal ajudam.*

## Decisões de projeto e dificuldades

Optei por separar as funções auxiliares em um utils.c, pois acabava usando-as em todos os outros módulos.

Optei por usar um TAD para cada estrutura (atualmente conta apenas com o lista_produtos.c).

Optei pelo uso de dois TADs separando a interface, um apenas para imprimir e outro para interagir, pois as funções que apenas imprimiam acabavam recebendo muitos includes não necessários.

Optei pelo uso de uint64_t para os IDs, pensei em usar UUID o que torna infinitas as possibilidades, mas achei muito complexo para entender. Pesquisei, e encontrei o uint64_t que é um inteiro unsigned com 64 bits ao invés de 32, apesar de ocupar o dobro de memória em relação ao inteiro comum, a quantidade de identificadores que o uint64_t é em torno de 8,76 bilhões de vezes maior do que o do inteiro comum (int32_t), isso acontece pois dobra a quantidade de bytes e não considera números negativos (unsigned). OBS: no fim não vai ter tanto ID, usei este mais para ver como é...

> *Escolhas que você fez onde o enunciado deixava aberto, problemas que apareceram e como resolveu. Rende pontos de clareza e ajuda na hora de explicar o trabalho.*

## Limitações conhecidas e próximos passos

> *O que ainda não faz ou faz de forma simplificada, e o que está previsto para as próximas partes (ex.: carregamento em caminhões).*

## Checklist de desenvolvimento

- [x] Criar a estrutura inicial do repositório e adicionar o `menu.c` fornecido
- [x] Implementar o TAD de lista simplesmente encadeada (base para produtos e itens)
- [x] Implementar o cadastro de produtos com as validações exigidas
- [ ] Implementar o cadastro de pedidos com sua lista de itens
- [ ] Implementar o TAD de fila e enfileirar os pedidos
- [ ] Implementar o TAD de pilha
- [ ] Implementar a separação dos pedidos seguindo a ordem da fila
- [ ] Implementar a montagem dos pacotes usando a pilha e a regra de capacidade
- [ ] Implementar a fila de pacotes prontos para expedição
- [ ] Integrar todas as funcionalidades ao menu principal
- [ ] Revisar tratamento de erros e liberar toda a memória alocada
- [ ] Testar diferentes cenários e corrigir problemas encontrados
- [ ] Comentar o código e finalizar o README
