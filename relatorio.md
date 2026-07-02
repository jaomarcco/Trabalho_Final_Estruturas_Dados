# Relatório Técnico: Decisões, Escolhas e Dificuldades de Implementação

Este documento detalha as escolhas arquiteturais e os desafios técnicos superados durante o desenvolvimento do Projeto Final de Estruturas de Dados.

## 1. Decisões de Implementação

* **Foco em Alocação Dinâmica (Requisito Extra):** A principal decisão arquitetural do projeto foi a abstenção total do uso de vetores estáticos. Todas as três estruturas (Lista Encadeada, Pilha e Fila Circular) foram construídas utilizando `malloc` para instanciar novos nós em tempo de execução e `free` para a liberação da memória. Isso tornou o sistema infinitamente escalável, limitado apenas pela memória RAM disponível.
* **Complexidade O(1) no Escalonador (Trabalho C):** No algoritmo Round-Robin, decidimos não destruir e recriar nós caso um processo não termine no tempo estipulado (Quantum). Em vez disso, implementamos uma lógica de re-encadeamento direto (`f->inicio = f->inicio->prox`), rotacionando a fila inteira para frente em tempo constante (O(1)), o que otimizou drasticamente o processamento.
* **Regra LIFO Estrita (Trabalho B):** Para o painel de emergências, a função de atendimento foi travada para não aceitar parâmetros de escolha do usuário. Ela invoca obrigatoriamente um *Pop* no nó apontado pelo ponteiro `topo`, garantindo a integridade absoluta da regra *Last-In, First-Out*.

## 2. Escolhas de Usabilidade e Persistência

* **Interface Colorida e Validações (Requisito Extra):** Optamos por utilizar códigos de escape ANSI nativos do C para criar uma interface colorida, destacando mensagens de erro e sucesso. Além disso, substituímos o `scanf` puro por validações com limpeza de *buffer* (`while ((c = getchar()) != '\n' && c != EOF);`), impedindo que a digitação de caracteres inválidos (letras em vez de números) causasse *loops* infinitos no terminal.
* **Limitação Consciente da Especificação CSV:** Na persistência de dados, utilizamos um modelo CSV simplificado com separador de ponto e vírgula (`;`). Por uma escolha de escopo, decidimos não implementar o tratamento de aspas duplas (RFC 4180). Assumimos como premissa que as entradas de texto do usuário não conterão o caractere `;`, focando o esforço computacional no manuseio correto dos ponteiros.

## 3. Dificuldades Encontradas

* **Rastreamento de Memory Leaks:** O maior desafio técnico foi o gerenciamento manual da memória. Tivemos dificuldades iniciais ao usar a função `free` durante as exclusões do meio da Lista Encadeada (Trabalho A), pois perdíamos a referência do nó seguinte. Isso foi resolvido criando um ponteiro temporário para segurar o endereço antes de aplicar a liberação.
* **Manutenção do Anel na Fila Circular:** No Trabalho C, foi complexo garantir que o ponteiro `prox` do último elemento sempre apontasse de volta para o `inicio` após uma inserção, especialmente na transição de uma fila vazia (onde `inicio` e `fim` são o mesmo nó) para uma fila populada. Foi necessário desenhar testes de mesa rigorosos para validar essa amarração e evitar *Segmentation Faults*.
