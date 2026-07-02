#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char corTexto[50] = "\x1b[0m";
char corReset[50] = "\x1b[0m";  

typedef struct {
    int id;
    char titulo[50];
    char artista[50];
    int duracao; 
    char genero[30];
} Musica;

typedef struct No {
    Musica dados;
    struct No *prox;
} No;

typedef struct {
    No *inicio;
    int total;  
} ListaPlaylist;

void inicializarLista(ListaPlaylist *lista);
void exibirMenu();
void cadastrarMusica(ListaPlaylist *lista);
void listarMusicas(ListaPlaylist *lista);
void buscarMusica(ListaPlaylist *lista);
void editarMusica(ListaPlaylist *lista);
void excluirMusica(ListaPlaylist *lista);
void exibirEstatisticas(ListaPlaylist *lista);
void salvarCSV(ListaPlaylist *lista, const char *nomeArquivo);
void carregarCSV(ListaPlaylist *lista, const char *nomeArquivo);
void limparBuffer();
No* buscarPorId(ListaPlaylist *lista, int id);
void selecionarCorSistema();
void liberarMemoria(ListaPlaylist *lista);

void inicializarLista(ListaPlaylist *lista) {
    lista->inicio = NULL;
    lista->total = 0;
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

No* buscarPorId(ListaPlaylist *lista, int id) {
    No *atual = lista->inicio;
    while (atual != NULL) {
        if (atual->dados.id == id) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

void selecionarCorSistema() {
    int escolha;
    printf("\n=========================================\n");
    printf("         MENU DE CORES DO SISTEMA        \n");
    printf("=========================================\n");
    printf("  [1] Branco / Padrao\n");
    printf("  [2] Verde\n");
    printf("  [3] Azul\n");
    printf("  [4] Ciano Claro\n");
    printf("  [5] Amarelo\n");
    printf("=========================================\n");
    printf("Escolha uma cor para o menu: ");

    if (scanf("%d", &escolha) != 1) {
        printf("\n[ERRO] Entrada invalida.\n");
        limparBuffer();
        return;
    }
    limparBuffer();

    switch(escolha) {
        case 1: strcpy(corTexto, "\x1b[0m"); break;
        case 2: strcpy(corTexto, "\x1b[32m"); break;
        case 3: strcpy(corTexto, "\x1b[34m"); break;
        case 4: strcpy(corTexto, "\x1b[36m"); break;
        case 5: strcpy(corTexto, "\x1b[33m"); break;
        default: 
            printf("\n[AVISO] Opcao invalida. Mantendo a cor atual.\n"); 
            return;
    }
    printf("\n[SUCESSO] Cor do menu alterada com sucesso!\n");
}

void exibirMenu() {
    printf("%s", corTexto);
    printf("-----------------------------------------\n");
    printf("================ PLAYLIST ================\n");
    printf("-----------------------------------------\n");
    printf("  [1] Cadastrar Musica\n");
    printf("  [2] Listar Todas as Musicas\n");
    printf("  [3] Buscar Musica por ID\n");
    printf("  [4] Editar Musica\n");
    printf("  [5] Excluir Musica\n");
    printf("  [6] Relatorios e Estatisticas\n");
    printf("  [7] Personalizar Cor do Menu\n");
    printf("  [0] Salvar e Sair\n");
    printf("-----------------------------------------\n");
    printf("%s", corReset);
}

void cadastrarMusica(ListaPlaylist *lista) {
    No *novoNo = (No *)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("\n[ERRO] Falha ao alocar memoria para a nova musica!\n");
        return;
    }

    int idDigitado;
    No *resultadoBusca;

    printf("\n=========================================\n");
    printf("         CADASTRO DE NOVA MUSICA         \n");
    printf("=========================================\n");

    do {
        printf("Digite o ID da musica (numero inteiro): ");
        if (scanf("%d", &idDigitado) != 1) {
            printf("[ERRO] Entrada invalida! Digite apenas numeros.\n");
            limparBuffer();
            resultadoBusca = (No *)-1;
            continue;
        }
        limparBuffer();

        if (idDigitado <= 0) {
            printf("[AVISO] O ID deve ser maior que zero.\n");
            resultadoBusca = (No *)-1;
            continue;
        }

        resultadoBusca = buscarPorId(lista, idDigitado);
        if (resultadoBusca != NULL) {
            printf("[ERRO] O ID ja pertence a outra musica!\n");
        }
    } while (resultadoBusca != NULL || idDigitado <= 0);

    novoNo->dados.id = idDigitado;

    printf("Digite o titulo da musica: ");
    fgets(novoNo->dados.titulo, sizeof(novoNo->dados.titulo), stdin);
    novoNo->dados.titulo[strcspn(novoNo->dados.titulo, "\n")] = '\0';

    printf("Digite o artista/banda: ");
    fgets(novoNo->dados.artista, sizeof(novoNo->dados.artista), stdin);
    novoNo->dados.artista[strcspn(novoNo->dados.artista, "\n")] = '\0';

    printf("Digite o genero musical: ");
    fgets(novoNo->dados.genero, sizeof(novoNo->dados.genero), stdin);
    novoNo->dados.genero[strcspn(novoNo->dados.genero, "\n")] = '\0';

    do {
        printf("Digite a duracao da musica (em segundos): ");
        if (scanf("%d", &novoNo->dados.duracao) != 1) {
            printf("[ERRO] Digite um tempo numerico valido.\n");
            limparBuffer();
            novoNo->dados.duracao = 0;
            continue;
        }
        limparBuffer();

        if (novoNo->dados.duracao <= 0) {
            printf("[AVISO] A duracao deve ser maior que zero.\n");
        }
    } while (novoNo->dados.duracao <= 0);

    novoNo->prox = NULL;
    if (lista->inicio == NULL) {
        lista->inicio = novoNo;
    } else {
        No *atual = lista->inicio;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novoNo;
    }
    
    lista->total++;
    printf("\n[SUCESSO] Musica cadastrada com exito!\n");
}

void listarMusicas(ListaPlaylist *lista) {
    if (lista->total == 0) {
        printf("\n[AVISO] A playlist esta vazia!\n");
        return;
    }

    printf("\n=========================================================================================\n");
    printf("                                   MUSICAS CADASTRADAS                                   \n");
    printf("=========================================================================================\n");
    printf("%-6s | %-25s | %-20s | %-12s | %s\n", "ID", "Titulo", "Artista", "Genero", "Duracao");
    printf("-----------------------------------------------------------------------------------------\n");

    No *atual = lista->inicio;
    while (atual != NULL) {
        int min = atual->dados.duracao / 60;
        int seg = atual->dados.duracao % 60;
        printf("%-6d | %-25.25s | %-20.20s | %-12.12s | %02d:%02d\n", 
               atual->dados.id, atual->dados.titulo, atual->dados.artista, atual->dados.genero, min, seg);
        atual = atual->prox;
    }
    printf("=========================================================================================\n");
}

void buscarMusica(ListaPlaylist *lista) {
    if (lista->total == 0) {
        printf("\n[AVISO] Playlist vazia. Nao ha o que buscar.\n");
        return;
    }

    int idBusca;
    printf("\nDigite o ID da musica para consulta: ");
    if (scanf("%d", &idBusca) != 1) {
        printf("[ERRO] Entrada invalida.\n");
        limparBuffer();
        return;
    }
    limparBuffer();

    No *encontrada = buscarPorId(lista, idBusca);
    if (encontrada == NULL) {
        printf("[ERRO] Musica com ID nao encontrada.\n");
    } else {
        printf("\n--- MUSICA ENCONTRADA ---\n");
        printf("ID: %d\nTitulo: %s\nArtista: %s\nGenero: %s\nDuracao: %02dm:%02ds\n",
               encontrada->dados.id, encontrada->dados.titulo, encontrada->dados.artista, 
               encontrada->dados.genero, encontrada->dados.duracao / 60, encontrada->dados.duracao % 60);
    }
}

void editarMusica(ListaPlaylist *lista) {
    if (lista->total == 0) {
        printf("\n[AVISO] Playlist vazia.\n");
        return;
    }

    int idBusca;
    printf("\nDigite o ID da musica que deseja editar: ");
    if (scanf("%d", &idBusca) != 1) {
        printf("[ERRO] Entrada invalida.\n");
        limparBuffer();
        return;
    }
    limparBuffer();

    No *alvo = buscarPorId(lista, idBusca);
    if (alvo == NULL) {
        printf("[ERRO] ID nao localizado.\n");
        return;
    }

    printf("\nEditando: %s (Deixe em branco para manter o atual)\n", alvo->dados.titulo);
    
    char entradaTemp[50];

    printf("Novo Titulo: ");
    fgets(entradaTemp, sizeof(entradaTemp), stdin);
    if (entradaTemp[0] != '\n') {
        entradaTemp[strcspn(entradaTemp, "\n")] = '\0';
        strcpy(alvo->dados.titulo, entradaTemp);
    }

    printf("Novo Artista: ");
    fgets(entradaTemp, sizeof(entradaTemp), stdin);
    if (entradaTemp[0] != '\n') {
        entradaTemp[strcspn(entradaTemp, "\n")] = '\0';
        strcpy(alvo->dados.artista, entradaTemp);
    }

    printf("[SUCESSO] Registro atualizado!\n");
}

void excluirMusica(ListaPlaylist *lista) {
    if (lista->total == 0) {
        printf("\n[ERRO] Nenhuma musica cadastrada.\n");
        return;
    }

    int idBusca;
    printf("\nDigite o ID da musica que deseja REMOVER: ");
    if (scanf("%d", &idBusca) != 1) {
        printf("[ERRO] Entrada invalida.\n");
        limparBuffer();
        return;
    }
    limparBuffer();

    No *atual = lista->inicio;
    No *anterior = NULL;

    while (atual != NULL && atual->dados.id != idBusca) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("[AVISO] Codigo ID nao encontrado.\n");
        return;
    }

    char conf;
    printf("[CONFIRMACAO] Excluir permanentemente '%s'? (s/n): ", atual->dados.titulo);
    scanf("%c", &conf);
    limparBuffer();

    if (conf == 's' || conf == 'S') {
        if (anterior == NULL) {
            lista->inicio = atual->prox;
        } else {
            anterior->prox = atual->prox;
        }
        
        free(atual);
        lista->total--;
        printf("[SUCESSO] Musica removida!\n");
    } else {
        printf("[INFO] Operacao cancelada.\n");
    }
}

void exibirEstatisticas(ListaPlaylist *lista) {
    if (lista->total == 0) {
        printf("\n[AVISO] Sem dados para processar relatorios.\n");
        return;
    }

    int tempoTotal = 0;
    No *atual = lista->inicio;
    No *maior = atual;
    No *menor = atual;

    while (atual != NULL) {
        tempoTotal += atual->dados.duracao;
        if (atual->dados.duracao > maior->dados.duracao) maior = atual;
        if (atual->dados.duracao < menor->dados.duracao) menor = atual;
        atual = atual->prox;
    }

    int h = tempoTotal / 3600;
    int m = (tempoTotal % 3600) / 60;
    int s = tempoTotal % 60;

    printf("\n==================================================\n");
    printf("             ESTATISTICAS DA PLAYLIST             \n");
    printf("==================================================\n");
    printf(" Quantidade de Musicas: %d\n", lista->total);
    printf(" Tempo Total de Audio:  %02dh:%02dm:%02ds\n", h, m, s);
    printf(" Duracao Media:         %d segundos\n", tempoTotal / lista->total);
    printf("--------------------------------------------------\n");
    printf(" Longa: %s (%02dm:%02ds)\n", maior->dados.titulo, maior->dados.duracao/60, maior->dados.duracao%60);
    printf(" Curta: %s (%02dm:%02ds)\n", menor->dados.titulo, menor->dados.duracao/60, menor->dados.duracao%60);
    printf("==================================================\n");
}

void salvarCSV(ListaPlaylist *lista, const char *nomeArquivo) {
    FILE *f = fopen(nomeArquivo, "w");
    if (!f) {
        printf("[ERRO] Falha de escrita no arquivo disco.\n");
        return;
    }

    No *atual = lista->inicio;
    while (atual != NULL) {
        fprintf(f, "%d;%s;%s;%d;%s\n", 
                atual->dados.id, atual->dados.titulo, atual->dados.artista, 
                atual->dados.duracao, atual->dados.genero);
        atual = atual->prox;
    }

    fclose(f);
    printf("[OK] Base de dados CSV sincronizada.\n");
}

void carregarCSV(ListaPlaylist *lista, const char *nomeArquivo) {
    FILE *f = fopen(nomeArquivo, "r");
    if (!f) return; 

    Musica m;
    while (fscanf(f, "%d;%[^;];%[^;];%d;%[^\n]\n", &m.id, m.titulo, m.artista, &m.duracao, m.genero) == 5) {
        No *novoNo = (No *)malloc(sizeof(No));
        if (novoNo) {
            novoNo->dados = m;
            novoNo->prox = NULL;
            
            if (lista->inicio == NULL) {
                lista->inicio = novoNo;
            } else {
                No *atual = lista->inicio;
                while (atual->prox != NULL) {
                    atual = atual->prox;
                }
                atual->prox = novoNo;
            }
            lista->total++;
        }
    }
    fclose(f);
    printf("[SISTEMA] Registros locais carregados com sucesso.\n");
}

void liberarMemoria(ListaPlaylist *lista) {
    No *atual = lista->inicio;
    while (atual != NULL) {
        No *temp = atual;
        atual = atual->prox;
        free(temp);
    }
    lista->inicio = NULL;
    lista->total = 0;
}

int main() {
    ListaPlaylist minhaPlaylist;
    
    inicializarLista(&minhaPlaylist);
    carregarCSV(&minhaPlaylist, "playlist.csv");

    int opcao;
    do {
        exibirMenu();
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            printf("\n[ERRO] Opcao invalida! Digite um numero.\n");
            limparBuffer();
            opcao = -1; 
            continue; 
        }
        limparBuffer(); 

        switch (opcao) {
            case 1: cadastrarMusica(&minhaPlaylist); break;
            case 2: listarMusicas(&minhaPlaylist); break;
            case 3: buscarMusica(&minhaPlaylist); break;
            case 4: editarMusica(&minhaPlaylist); break;
            case 5: excluirMusica(&minhaPlaylist); break;
            case 6: exibirEstatisticas(&minhaPlaylist); break;
            case 7: selecionarCorSistema(); break; 
            case 0: 
                salvarCSV(&minhaPlaylist, "playlist.csv");
                liberarMemoria(&minhaPlaylist); 
                printf("\n[SISTEMA CONCLUIDO] Obrigado por usar o nosso sistema de playlist!\n");
                break;
            default: 
                printf("\n[AVISO] Opcao inexistente. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
