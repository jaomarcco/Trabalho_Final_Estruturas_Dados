#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COR_VERMELHA "\x1b[31m"
#define COR_VERDE "\x1b[32m"
#define COR_AMARELA "\x1b[33m"
#define COR_CIANO "\x1b[36m"
#define COR_RESET "\x1b[0m"

typedef struct Chamada {
    int protocolo;
    char local[50];
    char tipo[50];
    char horario[10];
} Chamada;

typedef struct No {
    Chamada dados;
    struct No *prox;
} No;

typedef struct Pilha {
    No *topo;
    int tamanho;
} Pilha;

void inicializarPilha(Pilha *p) {
    p->topo = NULL;
    p->tamanho = 0;
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void registrarChamada(Pilha *p) {
    No *novoNo = (No *)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf(COR_VERMELHA "[ERRO] Falha de alocacao de memoria!\n" COR_RESET);
        return;
    }

    printf("\n" COR_CIANO "=== REGISTRAR EMERGENCIA ===" COR_RESET "\n");
    printf("Protocolo (Inteiro): ");
    scanf("%d", &novoNo->dados.protocolo);
    limparBuffer();

    if (p->topo != NULL && p->topo->dados.protocolo == novoNo->dados.protocolo) {
        printf(COR_AMARELA "[AVISO] Protocolo duplicado no topo. Tente outro.\n" COR_RESET);
        free(novoNo);
        return;
    }

    printf("Local da Ocorrencia: ");
    fgets(novoNo->dados.local, sizeof(novoNo->dados.local), stdin);
    novoNo->dados.local[strcspn(novoNo->dados.local, "\n")] = '\0';

    printf("Tipo de Ocorrencia (Ex: Incendio, Roubo): ");
    fgets(novoNo->dados.tipo, sizeof(novoNo->dados.tipo), stdin);
    novoNo->dados.tipo[strcspn(novoNo->dados.tipo, "\n")] = '\0';

    printf("Horario (HH:MM): ");
    fgets(novoNo->dados.horario, sizeof(novoNo->dados.horario), stdin);
    novoNo->dados.horario[strcspn(novoNo->dados.horario, "\n")] = '\0';

    novoNo->prox = p->topo;
    p->topo = novoNo;
    p->tamanho++;

    printf(COR_VERDE "[SUCESSO] Chamada empilhada!\n" COR_RESET);
}

void atenderChamada(Pilha *p) {
    if (p->topo == NULL) {
        printf(COR_VERMELHA "\n[ERRO] Nenhuma chamada de emergencia na fila!\n" COR_RESET);
        return;
    }

    No *temp = p->topo;
    p->topo = p->topo->prox;
    p->tamanho--;

    printf("\n" COR_VERDE "=== CHAMADA ATENDIDA ===" COR_RESET "\n");
    printf("Protocolo: %d | Local: %s | Tipo: %s\n", temp->dados.protocolo, temp->dados.local, temp->dados.tipo);
    
    free(temp);
}

void consultarUltima(Pilha *p) {
    if (p->topo == NULL) {
        printf(COR_AMARELA "\n[AVISO] A pilha esta vazia.\n" COR_RESET);
        return;
    }
    printf("\n" COR_CIANO "=== ULTIMA CHAMADA (TOPO) ===" COR_RESET "\n");
    printf("Protocolo: %d\nLocal: %s\nTipo: %s\nHorario: %s\n", 
           p->topo->dados.protocolo, p->topo->dados.local, p->topo->dados.tipo, p->topo->dados.horario);
}

void salvarPilhaCSV(Pilha *p, const char *arquivo) {
    FILE *f = fopen(arquivo, "w");
    if (!f) return;

    No *atual = p->topo;
    while (atual != NULL) {
        fprintf(f, "%d;%s;%s;%s\n", atual->dados.protocolo, atual->dados.local, atual->dados.tipo, atual->dados.horario);
        atual = atual->prox;
    }
    fclose(f);
    printf(COR_VERDE "[SISTEMA] Pilha salva em CSV.\n" COR_RESET);
}

void liberarPilha(Pilha *p) {
    No *atual = p->topo;
    while (atual != NULL) {
        No *temp = atual;
        atual = atual->prox;
        free(temp);
    }
}

int main() {
    Pilha emergencias;
    inicializarPilha(&emergencias);
    int opcao;

    do {
        printf("\n" COR_AMARELA "=== SISTEMA DE EMERGENCIA (LIFO) ===" COR_RESET "\n");
        printf("Pendente(s): %d\n", emergencias.tamanho);
        printf("[1] Registrar Chamada (Empilhar)\n[2] Atender Chamada (Desempilhar)\n");
        printf("[3] Consultar Ultima Chamada\n[0] Salvar e Sair\nEscolha: ");
        
        if(scanf("%d", &opcao) != 1) { limparBuffer(); opcao = -1; }
        limparBuffer();

        switch(opcao) {
            case 1: registrarChamada(&emergencias); break;
            case 2: atenderChamada(&emergencias); break;
            case 3: consultarUltima(&emergencias); break;
            case 0: 
                salvarPilhaCSV(&emergencias, "dados_b.csv");
                liberarPilha(&emergencias);
                break;
            default: printf(COR_VERMELHA "Opcao invalida!\n" COR_RESET);
        }
    } while (opcao != 0);

    return 0;
}
