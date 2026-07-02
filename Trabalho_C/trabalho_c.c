#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COR_AZUL "\x1b[34m"
#define COR_VERDE "\x1b[32m"
#define COR_VERMELHA "\x1b[31m"
#define COR_RESET "\x1b[0m"

#define QUANTUM 10

typedef struct Processo {
    int pid;
    char nome[50];
    int prioridade;
    int tempoRestante;
} Processo;

typedef struct NoFila {
    Processo dados;
    struct NoFila *prox;
} NoFila;

typedef struct FilaCircular {
    NoFila *inicio;
    NoFila *fim;
    int quantidade;
} FilaCircular;

void inicializarFila(FilaCircular *f) {
    f->inicio = NULL;
    f->fim = NULL;
    f->quantidade = 0;
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void adicionarProcesso(FilaCircular *f) {
    NoFila *novoNo = (NoFila *)malloc(sizeof(NoFila));
    if (!novoNo) return;

    printf("\n" COR_AZUL "=== NOVO PROCESSO ===" COR_RESET "\n");
    printf("PID: ");
    scanf("%d", &novoNo->dados.pid);
    limparBuffer();

    printf("Nome do Processo: ");
    fgets(novoNo->dados.nome, sizeof(novoNo->dados.nome), stdin);
    novoNo->dados.nome[strcspn(novoNo->dados.nome, "\n")] = '\0';

    printf("Prioridade (1-Alta, 3-Baixa): ");
    scanf("%d", &novoNo->dados.prioridade);

    printf("Tempo total de execucao (segundos): ");
    scanf("%d", &novoNo->dados.tempoRestante);
    limparBuffer();

    if (f->quantidade == 0) {
        f->inicio = novoNo;
        f->fim = novoNo;
        novoNo->prox = f->inicio;
    } else {
        f->fim->prox = novoNo;
        f->fim = novoNo;
        novoNo->prox = f->inicio;
    }
    f->quantidade++;
    printf(COR_VERDE "[SUCESSO] Processo enfileirado!\n" COR_RESET);
}

void executarProcesso(FilaCircular *f) {
    if (f->quantidade == 0) {
        printf(COR_VERMELHA "\n[ERRO] Nenhum processo na fila!\n" COR_RESET);
        return;
    }

    NoFila *atual = f->inicio;
    printf("\n" COR_AZUL "=== EXECUTANDO PROCESSO ===" COR_RESET "\n");
    printf("Processando [%s] (PID: %d)...\n", atual->dados.nome, atual->dados.pid);

    atual->dados.tempoRestante -= QUANTUM;

    if (atual->dados.tempoRestante <= 0) {
        printf(COR_VERDE "[CONCLUIDO] Processo PID %d finalizou!\n" COR_RESET, atual->dados.pid);
        
        if (f->quantidade == 1) {
            f->inicio = NULL;
            f->fim = NULL;
        } else {
            f->inicio = atual->prox;
            f->fim->prox = f->inicio;
        }
        free(atual);
        f->quantidade--;
    } else {
        printf("[AGUARDANDO] Tempo restante: %d seg. Voltando para o fim da fila.\n", atual->dados.tempoRestante);
        f->fim = f->inicio;
        f->inicio = f->inicio->prox;
    }
}

void listarProcessos(FilaCircular *f) {
    if (f->quantidade == 0) {
        printf(COR_VERMELHA "\n[AVISO] Fila vazia.\n" COR_RESET);
        return;
    }
    
    printf("\n" COR_AZUL "=== PROCESSOS NA FILA ===" COR_RESET "\n");
    NoFila *atual = f->inicio;
    for (int i = 0; i < f->quantidade; i++) {
        printf("PID: %-5d | Nome: %-15s | Faltam: %d seg\n", 
               atual->dados.pid, atual->dados.nome, atual->dados.tempoRestante);
        atual = atual->prox;
    }
}

void salvarCSV(FilaCircular *f, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (!arquivo) {
        printf(COR_VERMELHA "[ERRO] Nao foi possivel criar o arquivo CSV.\n" COR_RESET);
        return;
    }

    if (f->quantidade > 0) {
        NoFila *atual = f->inicio;
        for (int i = 0; i < f->quantidade; i++) {
            fprintf(arquivo, "%d;%s;%d;%d\n", 
                    atual->dados.pid, atual->dados.nome, 
                    atual->dados.prioridade, atual->dados.tempoRestante);
            atual = atual->prox;
        }
    }
    fclose(arquivo);
    printf(COR_VERDE "[OK] Base de dados do Escalonador salva em CSV.\n" COR_RESET);
}

void carregarCSV(FilaCircular *f, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) return;

    Processo p;
    while (fscanf(arquivo, "%d;%[^;];%d;%d\n", &p.pid, p.nome, &p.prioridade, &p.tempoRestante) == 4) {
        NoFila *novoNo = (NoFila *)malloc(sizeof(NoFila));
        if (novoNo) {
            novoNo->dados = p;
            
            if (f->quantidade == 0) {
                f->inicio = novoNo;
                f->fim = novoNo;
                novoNo->prox = f->inicio;
            } else {
                f->fim->prox = novoNo;
                f->fim = novoNo;
                novoNo->prox = f->inicio;
            }
            f->quantidade++;
        }
    }
    fclose(arquivo);
    printf(COR_VERDE "[SISTEMA] Registros locais carregados com sucesso.\n" COR_RESET);
}

void liberarFila(FilaCircular *f) {
    if (f->quantidade == 0) return;
    NoFila *atual = f->inicio;
    for (int i = 0; i < f->quantidade; i++) {
        NoFila *temp = atual;
        atual = atual->prox;
        free(temp);
    }
}

int main() {
    FilaCircular escalonador;
    inicializarFila(&escalonador);
    
    carregarCSV(&escalonador, "dados_c.csv");
    
    int opcao;

    do {
        printf("\n" COR_AZUL "=== ESCALONADOR ROUND-ROBIN ===" COR_RESET "\n");
        printf("Processos em fila: %d\n", escalonador.quantidade);
        printf("[1] Adicionar Processo\n[2] Executar Ciclo (Quantum: 10s)\n");
        printf("[3] Listar Processos\n[0] Sair\nEscolha: ");
        
        if(scanf("%d", &opcao) != 1) { limparBuffer(); opcao = -1; }
        limparBuffer();

        switch(opcao) {
            case 1: adicionarProcesso(&escalonador); break;
            case 2: executarProcesso(&escalonador); break;
            case 3: listarProcessos(&escalonador); break;
            case 0: 
                salvarCSV(&escalonador, "dados_c.csv");
                liberarFila(&escalonador); 
                printf("Sistema encerrado.\n"); 
                break;
            default: printf(COR_VERMELHA "Opcao invalida!\n" COR_RESET);
        }
    } while (opcao != 0);

    return 0;
}