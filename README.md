# Trabalho Final - Estruturas de Dados em C

**Aviso Importante sobre a Implementação (Ponto Extra):** Informamos que todo o projeto foi desenvolvido cumprindo os requisitos extras propostos. Os três programas não utilizam vetores estáticos, sendo integralmente implementados com **Alocação Dinâmica**, Nós Encadeados, manipulação de ponteiros, `malloc` e `free` (Lista, Pilha e Fila Circular).

### 👥 Integrantes do Grupo
* Davi Lopes Amorim
* Ivan de Brito Cunha Junior
* João Marcos de Jesus Santos
* Joel Pereira Costa

**Turma:** Engenharia de Computação  
🎥 **Vídeo de Apresentação:** [Clique aqui para assistir no YouTube](https://youtu.be/eY7EozCtn1o?si=cA9nnTapaY_suMEA)

---

## 📂 Temas Escolhidos e Descrição Básica

### 1. Trabalho A: Playlist de Músicas (Lista Simples Encadeada)
* **Arquivo:** `/Trabalho_A/trabalho_a.c`
* **Descrição:** Um sistema de gerenciamento de faixas musicais. Permite cadastrar, buscar, editar, excluir e listar músicas. O sistema mantém a base de dados sincronizada através de arquivos `.csv` e gera estatísticas automáticas sobre a duração das faixas.

### 2. Trabalho B: Chamadas de Emergência (Pilha Dinâmica - LIFO)
* **Arquivo:** `/Trabalho_B/trabalho_b.c`
* **Descrição:** Simulação de um painel de despacho de emergências. Respeita a regra *Last-In, First-Out* (LIFO), onde a ocorrência registrada mais recentemente assume o topo da pilha e tem prioridade máxima no momento do atendimento.

### 3. Trabalho C: Escalonador de Processos (Fila Circular Dinâmica - FIFO)
* **Arquivo:** `/Trabalho_C/trabalho_c.c`
* **Descrição:** Simulação de gerenciamento de CPU utilizando o algoritmo *Round-Robin*. Os processos possuem um *Quantum* estipulado. Caso não finalizem no tempo previsto, os ponteiros da fila são rotacionados em complexidade **O(1)**, mandando o processo para o final da fila de forma contínua e otimizada.

---

## ⚙️ Instruções de Compilação e Execução
Para rodar os programas, certifique-se de ter um compilador C (como o GCC) instalado na sua máquina. Abra o terminal na pasta de cada trabalho e execute os comandos abaixo:

### 1. Trabalho A: Playlist de Músicas
```bash
gcc trabalho_a.c -o trabalho_a.exe
.\trabalho_a.exe

```
### 2. Trabalho B: Chamadas de Emergência
```bash
gcc trabalho_b.c -o trabalho_b.exe
.\trabalho_b.exe

```
### 3. Trabalho C: Escalonador de Processos
```Bash
gcc trabalho_c.c -o trabalho_c.exe
.\trabalho_c.exe

```
📝 Relatório Simples: Decisões, Escolhas e Dificuldades
Atendendo aos requisitos do barema, detalhamos abaixo nossas decisões de projeto:

Decisões de Implementação e Usabilidade
Menus Interativos e Seguros: Todos os sistemas possuem menus numéricos protegidos contra entradas inválidas de caracteres (utilizando limpeza de buffer), evitando loops infinitos e quebras de execução.

Cores e Interface (Ponto Extra Geral): Implementamos códigos de escape ANSI para colorir os painéis e os feedbacks do terminal, melhorando a experiência do usuário.

Persistência de Dados: Os sistemas possuem carregamento inicial e salvamento automático ao encerrar. Para que os arquivos .csv sejam manipulados corretamente, o executável deve rodar no mesmo diretório em que o arquivo de texto se encontra.

Limitações Conhecidas
Especificação CSV: Para manter a leveza do sistema de arquivos e focar na lógica das estruturas de dados dinâmicas na memória RAM, o sistema utiliza uma versão simplificada do formato CSV (separado por ;). Atualmente, o sistema assume como premissa que o utilizador não inserirá o caractere separador (;) nos campos de texto (como Título ou Nome do Processo).

Dificuldades Encontradas
Gerenciamento de Memória: O maior desafio técnico foi garantir que não houvesse memory leaks (vazamentos de memória). Foi necessário implementar a lógica do free com muito cuidado, especialmente nas funções de re-encadeamento das listas e ao encerrar o sistema, garantindo que todos os nós fossem devolvidos ao sistema operacional com segurança.

Lógica Circular: Entender a manipulação de ponteiros na Fila Circular (Trabalho C) para que o programa não perdesse a referência do inicio e do fim ao rotacionar os processos exigiu testes rigorosos de teste de mesa.
Lógica Circular: Entender a manipulação de ponteiros na Fila Circular para que o programa não perdesse a referência do inicio e do fim ao rotacionar os processos.
