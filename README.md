# Projeto de estrutura de dados

Simulação em C do fluxo de um centro de distribuição (cadastro de produtos, fila de pedidos e montagem de pacotes) usando TADs de lista encadeada, fila e pilha.

## Sobre o projeto

Projeto desenvolvido na disciplina de Estrutura de Dados e Programação (2º semestre de Engenharia de Computação). Simula, em C, o fluxo de um centro de distribuição fictício, aplicando TADs, listas encadeadas, filas e pilhas.

## Funcionalidades

> *Lista curta do que o sistema faz hoje.*

## Estruturas de dados utilizadas

> *Para cada estrutura (lista, fila, pilha), uma linha dizendo onde ela é usada no sistema e por que foi a escolha adequada.*

## Regras de negócio adotadas

> *As simplificações e regras que implementei (capacidade da caixa, faixa de volume dos produtos, ordem de empacotamento, etc.). Útil para o professor ver que você entendeu o enunciado.*

## Organização do projeto

> *Árvore de pastas/arquivos e uma frase sobre o papel de cada TAD (.h e .c). Explique também o que é o* `main`

## Como compilar e executar

> *Pré-requisitos (compilador, SO testado), comando de compilação e comando de execução. Testar em uma máquina "limpa" antes de entregar.*

## Como usar

> *Passo a passo curto de uso do menu, com um exemplo de fluxo (cadastrar produto, cadastrar pedido, ver o resultado). Prints do terminal ajudam.*

## Decisões de projeto e dificuldades

> *Escolhas que você fez onde o enunciado deixava aberto, problemas que apareceram e como resolveu. Rende pontos de clareza e ajuda na hora de explicar o trabalho.*

## Limitações conhecidas e próximos passos

> *O que ainda não faz ou faz de forma simplificada, e o que está previsto para as próximas partes (ex.: carregamento em caminhões).*

## Checklist de desenvolvimento

- [ ] Criar a estrutura inicial do repositório e adicionar o `menu.c` fornecido
- [ ] Implementar o TAD de lista simplesmente encadeada (base para produtos e itens)
- [ ] Implementar o cadastro de produtos com as validações exigidas
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
