# Trabalho Final - Estruturas de Dados

**Aviso Importante sobre a Implementação (Ponto Extra):** Informamos que todo o projeto foi desenvolvido cumprindo os requisitos extras propostos. Os três programas não utilizam vetores estáticos, sendo integralmente implementados com **Alocação Dinâmica, Nós Encadeados, ponteiros, malloc e free** (Lista, Pilha e Fila Circular).

## Integrantes do Grupo
* [Davi Lopes Amorim]
* [Ivan de Brito Cunha Junior]
* [João Marcos de Jesus Santos]
* [Joel Pereira Costa]
* **Turma:** [Engenharia de Computaçao]
* **Link do Vídeo de Apresentação:** [Cole aqui o link do YouTube]

---

## Temas Escolhidos e Descrição Básica

### 1. Trabalho A: Playlist de Músicas (Lista Simplesmente Encadeada)
* **Arquivo:** `/Trabalho_A/trabalho_a.c`
* **Descrição:** Um sistema de gerenciamento de faixas musicais. Permite cadastrar, buscar, editar, excluir e listar músicas. O sistema mantém a base de dados sincronizada através de arquivos `.csv` e gera estatísticas sobre a duração das faixas.

### 2. Trabalho B: Chamadas de Emergência (Pilha Dinâmica - LIFO)
* **Arquivo:** `/Trabalho_B/trabalho_b.c`
* **Descrição:** Simulação de um painel de despacho de emergências. Respeita a regra *Last-In, First-Out*, onde a ocorrência registrada mais recentemente assume o topo da pilha e tem prioridade máxima no momento do atendimento.

### 3. Trabalho C: Escalonador de Processos (Fila Circular Dinâmica - FIFO)
* **Arquivo:** `/Trabalho_C/trabalho_c.c`
* **Descrição:** Simulação de gerenciamento de CPU utilizando o algoritmo Round-Robin. Os processos possuem um *Quantum* estipulado. Caso não finalizem no tempo previsto, os ponteiros da fila são rotacionados em O(1), mandando o processo para o final da fila de forma contínua.

---

## Instruções de Compilação e Execução

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
### 3. Trabalho B: Escalonador de Processos
```Bash
gcc trabalho_c.c -o trabalho_c.exe
.\trabalho_c.exe

```
⚠️ Observações sobre o Funcionamento

Menus Interativos: Todos os sistemas possuem menus numéricos protegidos contra entradas inválidas de caracteres, evitando loops infinitos.

Cores e Interface (Ponto Extra Geral): Implementamos códigos de escape ANSI para colorir os painéis e feedbacks do terminal.

Persistência de Dados: Os sistemas possuem salvamento automático. Para que os arquivos .csv sejam carregados e salvos corretamente, o programa deve ser executado no mesmo diretório em que o arquivo de texto se encontra.

---

Dificuldades Encontradas

Gerenciamento de Memória: O maior desafio técnico foi garantir que não houvesse memory leaks (vazamentos de memória). Foi necessário implementar a lógica do free com muito cuidado, especialmente nas funções de re-encadeamento das listas e ao encerrar o sistema, garantindo que todos os nós fossem devolvidos ao sistema operacional com segurança.

Lógica Circular: Entender a manipulação de ponteiros na Fila Circular para que o programa não perdesse a referência do inicio e do fim ao rotacionar os processos.
