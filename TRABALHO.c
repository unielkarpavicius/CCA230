#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>
#define MAX_PRIORITARIO 20
#define LEN 100
#ifdef _WIN32
#define strcasecmp _stricmp
#endif


//Cor das letras
enum{BLACK,                 //0
    BLUE,                  //1
    GREEN,                 //2
    CYAN,                  //3
    RED,                   //4
    MAGENTA,               //5
    BROWN,                 //6
    LIGHTGRAY,             //7
    DARKGRAY,              //8
    LIGHTBLUE,             //9
    LIGHTGREEN,            //10
    LIGHTCYAN,             //11
    LIGHTRED,              //12
    LIGHTMAGENTA,          //13
    YELLOW,                //14
    WHITE                  //15
    
    };  

//Cor do fundo
enum{_BLACK=0,                 //0
    _BLUE=16,                  //1
    _GREEN=32,                 //2
    _CYAN=48,                  //3
    _RED=64,                   //4
    _MAGENTA=80,               //5
    _BROWN=96,                 //6
    _LIGHTGRAY=112,             //7
    _DARKGRAY=128,              //8
    _LIGHTBLUE=144,             //9
    _LIGHTGREEN=160,            //10
    _LIGHTCYAN=176,             //11
    _LIGHTRED=192,              //12
    _LIGHTMAGENTA=208,          //13
    _YELLOW=224,                //14
    _WHITE=240                  //15       
    };  
typedef struct Data {
        int dia;
        int mes;
        int ano;
} Data;

typedef struct Celula {
    char nome[LEN];
    char RG[LEN];
    int idade;
    Data *entrada;
    struct Celula *proxima;
} Celula;

typedef struct FilaP { 
    Celula* heap[MAX_PRIORITARIO];
    int qtde;
}FilaP;


typedef struct Lista {
    int qtde;
    Celula *primeiro;
} Lista;

typedef struct Efila{
    Celula *Dados; 
    struct Efila *Proximo; 
}Efila;

typedef struct Fila { 
    Efila *Head; 
    Efila *Tail;
    int Qtde; 
}Fila;

typedef struct NO{
    Celula* paciente;
    struct NO *esq, *dir;
}NO;

typedef struct {
    NO *raiz;
    int qtde;
}Arvore;

// Função para a inicialização da fila 
Fila *inicializa_fila(){
    Fila *fila = malloc(sizeof(Fila));
    if(fila == NULL){
        printf("Erro de alocação de memória!\n");
        exit(1);
    }
    fila->Qtde = 0;
    fila->Head = NULL;
    fila->Tail = NULL;
    return fila;
}

// Funções de inicialização
Lista *inicializa_lista() {
    Lista *lista = malloc(sizeof(Lista));
    if (lista == NULL) {
        printf("Erro de alocação de memória!\n");
        exit(1);
    }
    lista->primeiro = NULL;
    lista->qtde = 0;
    return lista;
}

// Inicializa a celula
Celula *inicializa_celula() {
    Celula *novo = malloc(sizeof(Celula));
    if (novo == NULL) {
        printf("Erro de alocação de memória!\n");
        exit(1);
    }
    novo->proxima = NULL;
    strcpy(novo->nome, "-");
    strcpy(novo->RG, "000000000-00");
    novo->idade = 0;

    novo->entrada = malloc(sizeof(Data));
    if (novo->entrada == NULL) {
        printf("Erro de alocação de memória!\n");
        exit(1);
    }
    novo->entrada->dia = 0;
    novo->entrada->mes = 0;
    novo->entrada->ano = 0;
    return novo;
}

//Função para a inicialização da efila 
Efila *inicializa_efila(){
    Efila *nova = (Efila*)malloc(sizeof(Efila));
    if (nova == NULL) {
        printf("Erro de alocação de memória!\n");
        exit(1);
    }
    nova->Dados = inicializa_celula();
    nova->Proximo = NULL; 
    return nova;
}
// Função para limpar espaços extras no nome
void limpar_espacos(char *str) {
    int len = strlen(str);
    while (len > 0 && (str[len-1] == ' ' || str[len-1] == '\n'))
        str[--len] = '\0';
}

// Função para buscar paciente por nome
Celula *buscar_paciente(Lista *l, const char *nome) {
    Celula *atual = l->primeiro;
    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            return atual;
        }
        atual = atual->proxima;
    }
    return NULL;
}

// Função para cadastrar um paciente
void cadastrar_paciente(Lista *l, char *nome, char *rg, int idade, Data *entrada) {
    Celula *novo = inicializa_celula();
    strcpy(novo->nome, nome);
    strcpy(novo->RG, rg);
    novo->idade = idade;
    novo->entrada->dia = entrada->dia;
    novo->entrada->mes = entrada->mes;
    novo->entrada->ano = entrada->ano;

    novo->proxima = l->primeiro;
    l->primeiro = novo;

    l->qtde++;
}

void salvar_pacientes(Lista *l) {
    FILE *arquivo = fopen("pacientes.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo para escrita!\n");
        return;
    }
    printf("cheguei aqui 2\n");
    Celula *atual = l->primeiro;
    while (atual != NULL) {
        fprintf(arquivo, "%s\n", atual->nome);
        fprintf(arquivo, "%s\n", atual->RG);
        fprintf(arquivo, "%d\n", atual->idade);
        fprintf(arquivo, "%d %d %d\n", atual->entrada->dia, atual->entrada->mes, atual->entrada->ano);
        atual = atual->proxima;
    }
    printf("cheguei aqui 3\n");
    fclose(arquivo);
    printf("cheguei aqui 4\n");
}

void salvar_pacientes_remov(Lista *l) {
    FILE *arquivo = fopen("pacientes.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo para escrita!\n");
        return;
    }
    printf("cheguei aqui 2\n");
    Celula *atual = l->primeiro;
    while (atual != NULL) {
        fprintf(arquivo, "%s\n", atual->nome);
        fprintf(arquivo, "%s\n", atual->RG);
        fprintf(arquivo, "%d\n", atual->idade);
        fprintf(arquivo, "%d %d %d\n", atual->entrada->dia, atual->entrada->mes, atual->entrada->ano);
        atual = atual->proxima;
    }
    printf("cheguei aqui 3\n");
    fclose(arquivo);
    printf("cheguei aqui 4\n");
}

// Função para remover paciente
void remover_paciente(Lista *l, char *nome) {
    
    Celula *atual = l->primeiro;
    Celula *anterior = NULL;
    
    limpar_espacos(nome);

    while (atual != NULL && strcmp(atual->nome, nome) != 0) {
        anterior = atual;
        atual = atual->proxima;
    }

    if (atual == NULL) {
        printf("Não foi encontrado nenhum paciente com este nome!\n");
        return;
    }

    if (anterior == NULL) {
        l->primeiro = atual->proxima;
    } else {
        anterior->proxima = atual->proxima;
    }

    free(atual->entrada);
    free(atual);
    l->qtde--;
    salvar_pacientes_remov(l);


    printf("Paciente removido com sucesso!\n");
}

// Função para atualizar dados
void atualiza_dados(Lista *l) {
    char buffer[256], nome[LEN];
    char novo_nome[LEN], novo_rg[LEN];
    int nova_idade;
    Data nova_entrada;
    char opcao;

    printf("Digite o nome do paciente que deseja atualizar: ");
    fgets(nome, LEN, stdin);
    limpar_espacos(nome);

    Celula *paciente = buscar_paciente(l, nome);
    if (paciente == NULL) {
        printf("Paciente não encontrado!\n");
        return;
    }

    while (1) {
        printf("\n==========================================\n");
        printf("           MENU DE ATUALIZAÇÃO\n");
        printf("\n==========================================\n");
        printf("1 - Atualizar Nome\n");
        printf("2 - Atualizar RG\n");
        printf("3 - Atualizar Idade\n");
        printf("4 - Atualizar Data de Entrada\n");
        printf("0 - Voltar ao Menu Principal\n");
        printf("\n==========================================\n");
        printf("Escolha: ");
        fgets(buffer, sizeof(buffer), stdin);
        opcao = buffer[0];

        switch (opcao) {
            case '1':
                printf("Digite o novo nome: ");
                fgets(novo_nome, LEN, stdin);
                limpar_espacos(novo_nome);
                strcpy(paciente->nome, novo_nome);
                salvar_pacientes_remov(l);
                printf("Nome atualizado com sucesso!\n");
                break;
            case '2':
                printf("Digite o novo RG: ");
                fgets(novo_rg, LEN, stdin);
                limpar_espacos(novo_rg);
                strcpy(paciente->RG, novo_rg);
                salvar_pacientes_remov(l);
                printf("RG atualizado com sucesso!\n");
                break;
            case '3':
                printf("Digite a nova idade: ");
                scanf("%d", &nova_idade);
                paciente->idade = nova_idade;
                getchar(); // limpa '\n'
                salvar_pacientes_remov(l);
                printf("Idade atualizada com sucesso!\n");
                break;
            case '4':
                printf("Digite o novo dia de entrada: ");
                scanf("%d", &nova_entrada.dia);
                printf("Digite o novo mês de entrada: ");
                scanf("%d", &nova_entrada.mes);
                printf("Digite o novo ano de entrada: ");
                scanf("%d", &nova_entrada.ano);
                getchar(); // limpa '\n'
                paciente->entrada->dia = nova_entrada.dia;
                paciente->entrada->mes = nova_entrada.mes;
                paciente->entrada->ano = nova_entrada.ano;
                salvar_pacientes_remov(l);
                printf("Data de entrada atualizada com sucesso!\n");
                break;
            case '0':
                return;
            default:
                printf("Opção inválida!\n");
        }
    }
}

void ler_pacientes(Lista *l) {
    FILE *arquivo = fopen("pacientes.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo para leitura!\n");
        return;
    }

    char nome[LEN], rg[LEN];
    int idade;
    Data entrada;

    // Ler dados dos pacientes
    while (fscanf(arquivo, "%99[^\n]\n", nome) == 1) {
        fscanf(arquivo, "%99[^\n]\n", rg);
        fscanf(arquivo, "%d\n", &idade);
        fscanf(arquivo, "%d %d %d\n", &entrada.dia, &entrada.mes, &entrada.ano);

        // Cadastrar paciente lido
        cadastrar_paciente(l, nome, rg, idade, &entrada);
    }

    fclose(arquivo);
}

// Função para mostrar todos os pacientes
void mostrar_dados(Lista *l) {
    if (l->qtde == 0) {
        printf("Não existem pacientes cadastrados!\n");
        return;
    }


    Celula *atual = l->primeiro;
    while (atual != NULL) {
        printf("\n==========================================\n");
        printf("NOME: %s\n", atual->nome);
        printf("RG: %s\n", atual->RG);
        printf("IDADE: %d anos\n", atual->idade);
        printf("DATA DE ENTRADA: %02d/%02d/%04d\n", atual->entrada->dia, atual->entrada->mes, atual->entrada->ano);
        printf("\n==========================================\n");
        atual = atual->proxima;
    }
    printf("\n");
}

Celula* retornar_paciente_arquivo(const char* nome_busca) {
    FILE *arquivo = fopen("pacientes.txt", "r"); // Abre o arquivo para leitura
    if (arquivo == NULL) { // Verifica se o arquivo existe 
        printf("Erro ao abrir arquivo para leitura!\n");
        return NULL;
    }

    char nome[LEN], rg[LEN];
    int idade;
    Data entrada;
    Celula* paciente_encontrado = NULL;

    // Percorre o arquivo linha por linha
    while (fscanf(arquivo, "%99[^\n]\n", nome) == 1) { // Le 99 caracteres do arquivo pulando a quebra de linha e armazenando no "nome"
        fscanf(arquivo, "%99[^\n]\n", rg);
        fscanf(arquivo, "%d\n", &idade);
        fscanf(arquivo, "%d %d %d\n", &entrada.dia, &entrada.mes, &entrada.ano);


        if (strcasecmp(nome, nome_busca) == 0) { // Compara com o nome buscado
            
            paciente_encontrado = inicializa_celula(); // Inicializa uma nova celula para armazenar os dados do paciente
            strcpy(paciente_encontrado->nome, nome); // Armazena o nome encontrado dentro do nome da celula "paciente_encontrado"
            strcpy(paciente_encontrado->RG, rg); // Armazena o Rg encontrado dentro do Rg da celula "paciente_encontrado"
            paciente_encontrado->idade = idade; // Armazena a idade encontrada dentro da idade da celula "paciente_encontrado"
            paciente_encontrado->entrada->dia = entrada.dia; // Faz a mesma coisa para os valores da data de entrada no hospital 
            paciente_encontrado->entrada->mes = entrada.mes;
            paciente_encontrado->entrada->ano = entrada.ano;
            break;
        }
    }

    fclose(arquivo);
    
    if (paciente_encontrado == NULL) {
        printf("Paciente não encontrado no arquivo!\n");
    }
    
    return paciente_encontrado;
}



void consulta_paciente(Lista *L) {
    char nome[LEN];

    printf("Digite o nome do paciente que deseja atualizar: ");
    fgets(nome, LEN, stdin); // Pega a respota do usuário

    limpar_espacos(nome); // Limpa espaço vazia que pode ser deixado pelo o usuário

    Celula *atual = buscar_paciente(L, nome);
    if (atual == NULL) {
        printf("Paciente não encontrado!\n");
        return;
    }

    if (atual != NULL) {
        printf("\n==========================================\n");
        printf("NOME: %s\n", atual->nome);
        printf("RG: %s\n", atual->RG);
        printf("IDADE: %d anos\n", atual->idade);
        printf("DATA DE ENTRADA: %02d/%02d/%04d\n", atual->entrada->dia, atual->entrada->mes, atual->entrada->ano);
        printf("\n==========================================\n");
    }
    printf("\n");
}

// Função para liberar toda a lista
void liberar_lista(Lista *l) {
    Celula *atual = l->primeiro;
    while (atual != NULL) {
        Celula *temp = atual;
        atual = atual->proxima;
        free(temp->entrada);
        free(temp);
    }
    free(l);
}

// Função do menu principal
int menu_cadastro(Lista *lista) {
    char ch, buffer[256];
    char nome[LEN], rg[LEN];
    int idade;
    Data entrada;

    while (1) {
        printf("\n==========================================\n");
        printf("             MENU DO CADASTRO");
        printf("\n==========================================\n");
        printf("1 - Cadastrar Paciente\n");
        printf("2 - Mostrar Pacientes\n");
        printf("3 - Remover Paciente\n");
        printf("4 - Atualizar Dados\n");
        printf("5 - Consultar Paciente\n");
        printf("0 - Voltar Para O Menu Do Sistema\n");
        printf("\n==========================================\n");
        printf("Escolha: ");
        fgets(buffer, sizeof(buffer), stdin);
        ch = buffer[0];

        switch (ch) {
            case '1':
                printf("Digite o nome do paciente: ");
                fgets(nome, LEN, stdin);
                limpar_espacos(nome);

                printf("Digite o RG do paciente: ");
                fgets(rg, LEN, stdin);
                limpar_espacos(rg);

                printf("Digite a idade do paciente: ");
                scanf("%d", &idade);

                printf("Digite o dia da entrada: ");
                scanf("%d", &entrada.dia);
                printf("Digite o mês da entrada: ");
                scanf("%d", &entrada.mes);
                printf("Digite o ano da entrada: ");
                scanf("%d", &entrada.ano);
                getchar(); // limpa '\n'

                cadastrar_paciente(lista, nome, rg, idade, &entrada);
                salvar_pacientes(lista);
    
                
                printf("Paciente cadastrado com sucesso!\n");
                break;

            case '2':
                mostrar_dados(lista);
                break;

            case '3':
                printf("Digite o nome completo do paciente a ser removido: ");
                fgets(nome, LEN, stdin);
                limpar_espacos(nome);
                remover_paciente(lista, nome);
                
                break;

            case '4':
                atualiza_dados(lista);
                break;

            case '5':
                consulta_paciente(lista);
                break;

            case '0':
                liberar_lista(lista);
                return 0;

            default:
                printf("Opção inválida!\n");
        }
    }
}


//Enfilera Um Paciente 
void enfilerar(Fila* fila, const char nome[]) {
    Celula* paciente = retornar_paciente_arquivo(nome); // Pega os dados do paciente salvo no arquivo "paciente.txt" através da fução "retorna_paciente_arquivo"
    if (paciente == NULL) {
        printf("Paciente não encontrado no arquivo!\n"); // Caso o paciente não for encontrado
        return;
    }

    Efila *novo = inicializa_efila(); // Cria uma nova celula para a fila

    // Copia os dados do paciente para a nova célula da fila
    strcpy(novo->Dados->nome, paciente->nome); // Passa o nome do paciente para a celula "novo"
    strcpy(novo->Dados->RG, paciente->RG); // Passa o Rg do paciente para a celula "novo"
    novo->Dados->idade = paciente->idade; // Passa a idade do paciente para a celula "novo"
    novo->Dados->entrada->dia = paciente->entrada->dia; // Passa o dia de entrada do paciente no hospital para a celula "novo"
    novo->Dados->entrada->mes = paciente->entrada->mes; // Passa o mes de entrada do paciente no hospital para a celula "novo"
    novo->Dados->entrada->ano = paciente->entrada->ano; // Passa o ano de entrada do paciente no hospital para a celula "novo"

    // Libera a memória do paciente retornado pela consulta
    free(paciente->entrada);
    free(paciente);

    if(fila->Qtde == 0) {
        fila->Head = novo; 
    } else { 
        fila->Tail->Proximo = novo; 
    }
    fila->Tail = novo; 
    fila->Qtde++; 
    printf("O paciente foi colocado na fila com sucesso!\n");
}

void remover_da_fila(Fila *fila){
    if (fila->Qtde == 0){ // Verifica se a fila esta vazia
        printf("Fila Vazia\n");
        return;
    }

    Efila *temp = fila->Head; // Salva a célula atual
    fila->Head = fila->Head->Proximo; // Faz com que o segundo da fila se torne o primeiro e o antigo primero seja excluido da fila

    if(fila->Head == NULL){ // Caso a fila fique vazia após a remoção
        fila->Tail = NULL;
    }

    free(temp->Dados->entrada); // Libera a entrada do hospital da memoria 
    free(temp->Dados); // Libera os dados do paciente da memoria
    free(temp); // Libera o espaço da memoria do computador
    fila->Qtde--;
    printf("Paciente removido da fila com sucesso!");
}


//Mostra os pacientes da fila 
void Mostra_Fila(Fila *fila){
    Efila *atual = fila->Head; // Cria o incio da fila 
    printf("Proximo paciente: ");
    while(atual!=NULL){ // Percore toda a lista
        printf("\n==========================================\n");
        printf("NOME: %s\n", atual->Dados->nome); // Imprime o "nome" da variavel "atual"
        printf("RG: %s\n", atual->Dados->RG); // Imprime o "RG" da variavel "atual"
        printf("IDADE: %d anos\n", atual->Dados->idade); // Imprime a "idade" da variavel "atual"
        printf("DATA DE ENTRADA: %02d/%02d/%04d\n", atual->Dados->entrada->dia, atual->Dados->entrada->mes, atual->Dados->entrada->ano); // Imprime a "Entrada" da variavel "atual"
        printf("\n==========================================\n");
        atual = atual->Proximo; // Vai para o proximo elemento da lista
    }
    printf("Final da Fila");
    printf("\n");
    }

    // Função para liberar a memoria da Fila, utilizada após a finaliza.
    void liberar_fila(Fila*fila){
        Efila *atual = fila->Head; 
        while(atual!=NULL){ 
        Efila *temp = atual; // Celula temporaria para a liberação de memoria da celula atual. 
        atual = atual->Proximo; // avança pela fila ate o final do WHILE.
        free(temp->Dados->entrada); // Libera os valores de entrada (dia, mes e ano). 
        free(temp->Dados); // Libera os dados (nome, idade etc..)
        free(temp); // Libera o espaço que a celula ocupa na memoria.

        }
        free(fila); // Retorna a lista vazia logo depois do termino das atividades do menu. 
    } 

    void trocar_dados(Celula **a, Celula **b) {
        Celula *temp = *a;
        *a = *b;
        *b = temp;
    }

    int filho_esquerda(int pai) {
        return (2 * pai + 1);
    }
    
    int filho_direita(int pai) {
        return (2 * pai + 2);
    }
    int indice_pai(int i){
        return (i-1)/2;
    }

    int ultimo_pai(FilaP *h) {
        return ((h->qtde / 2) - 1);
    }

    void peneirar_prioridade(FilaP *f, int pai) {
        int fe = filho_esquerda(pai);
        int fd = filho_direita(pai);
        int maior = pai;
    
        // Verifica se filho esquerdo existe e é mais velho que o pai
        if (fe < f->qtde && f->heap[fe]->idade > f->heap[maior]->idade) {
            maior = fe;
        }
    
        // Verifica se filho direito existe e é mais velho que o atual maior
        if (fd < f->qtde&& f->heap[fd]->idade > f->heap[maior]->idade) {
            maior = fd;
        }
    
        // Se algum filho é mais velho ele faz a troca e continua
        if (maior != pai) {
            trocar_dados(&f->heap[pai], &f->heap[maior]);
            peneirar_prioridade(f, maior);
        }
    }

    // Organiza a fila apartir do ultimo pai
    void construir_heap_prioridade(FilaP* f) {
        for (int i = ultimo_pai(f); i >= 0; i--) {
            peneirar_prioridade(f, i);
        }
    }

    void adicionar_na_heap(FilaP* f) {
        if (f->qtde >= MAX_PRIORITARIO) {
            printf("A fila prioritária já está cheia (máximo de %d pacientes).\n", MAX_PRIORITARIO);
            return;
        }
    
        char nome[LEN];
        printf("Digite o nome do paciente para adicionar à fila prioritária: ");
        fgets(nome, LEN, stdin);
        limpar_espacos(nome); // Tira o /n do console 
    
        Celula* paciente = retornar_paciente_arquivo(nome);
        if (!paciente) {
            printf("Paciente não encontrado no arquivo.\n");
            return;
        }
    
        // Insere o paciente no final do vetor heap
        f->heap[f->qtde] = paciente;
        f->qtde++;
    
        // Reconstrói o heap por completo
        construir_heap_prioridade(f);
    
        printf("Paciente %s (Idade: %d) foi adicionado à fila prioritária.\n", paciente->nome, paciente->idade);
    }

    void remover_maior_prioridade(FilaP* f) {
        if (f->qtde == 0) {
            printf("Fila prioritária vazia!\n");
            return;
        }
    
        Celula* paciente = f->heap[0];
        printf("Atendendo paciente prioritário: %s (Idade: %d)\n", paciente->nome, paciente->idade);
    
        // Substitui a raiz pelo último elemento
        f->heap[0] = f->heap[f->qtde - 1];
        f->qtde--;
    
        // Reorganiza o heap
        peneirar_prioridade(f, 0);
    
        free(paciente->entrada);
        free(paciente);
    }
    
    void mostrar_heap(FilaP* f) {
        if (f->qtde == 0) {
            printf("Fila prioritária vazia!\n");
            return;
        }
    
        printf("\n=== Fila Prioritária (Heap por idade) ===\n");
        for (int i = 0; i < f->qtde; i++) {
            Celula* c = f->heap[i];
            printf("Nome: %s | Idade: %d | RG: %s | Entrada: %02d/%02d/%04d\n",c->nome, c->idade, c->RG,c->entrada->dia, c->entrada->mes, c->entrada->ano);
        }
    }

    void Sobre(){
        printf("\n==========================================\n");
        printf("             DADOS DOS ALUNOS");
        printf("\n==========================================\n");
        printf("Nome: Matheus Marcondes Pereira Rufino\n");
        printf("Nome: Luana Nascimento Karpavicius\n");
        printf("Ciclo: 7\n");
        printf("Curso: Engenharia de Robos\n");
        printf("Disciplina: Estrutura de dados\n");
        printf("Data: 08/05/2025");
        printf("\n==========================================\n");
    }

    NO* inserir_arvore_ano(NO* raiz, Celula* paciente){
        if (raiz == NULL) {
            NO* novo = (NO*)malloc(sizeof(NO));
            novo->paciente = paciente;
            novo->esq = novo->dir = NULL;
            return novo;
        }
        
        if (paciente->entrada->ano < raiz->paciente->entrada->ano)
            raiz->esq = inserir_arvore_ano(raiz->esq, paciente);
        else
            raiz->dir = inserir_arvore_ano(raiz->dir, paciente);
    
        return raiz;
        }

    NO* inserir_arvore_mes(NO* raiz, Celula* paciente){
         if (raiz == NULL) {
            NO* novo = (NO*)malloc(sizeof(NO));
            novo->paciente = paciente;
            novo->esq = novo->dir = NULL;
            return novo;
        }
    
        if (paciente->entrada->mes < raiz->paciente->entrada->mes)
            raiz->esq = inserir_arvore_mes(raiz->esq, paciente);
        else
            raiz->dir = inserir_arvore_mes(raiz->dir, paciente);
    
        return raiz;
    }
    NO* inserir_arvore_dia(NO* raiz, Celula* paciente){
         if (raiz == NULL) {
            NO* novo = (NO*)malloc(sizeof(NO));
            novo->paciente = paciente;
            novo->esq = novo->dir = NULL;
            return novo;
        }
    
        if (paciente->entrada->dia < raiz->paciente->entrada->dia)
            raiz->esq = inserir_arvore_dia(raiz->esq, paciente);
        else
            raiz->dir = inserir_arvore_dia(raiz->dir, paciente);
    
        return raiz;
    }
    NO* inserir_arvore_idade(NO* raiz, Celula* paciente){
         if (raiz == NULL) {
            NO* novo = (NO*)malloc(sizeof(NO));
            novo->paciente = paciente;
            novo->esq = novo->dir = NULL;
            return novo;
        }
    
        if (paciente->idade < raiz->paciente->idade)
            raiz->esq = inserir_arvore_idade(raiz->esq, paciente);
        else
            raiz->dir = inserir_arvore_idade(raiz->dir, paciente);
    
        return raiz;
    }

void in_order(NO* raiz) {
    if (raiz != NULL) {
        in_order(raiz->esq);
        printf("%s - Idade: %d - Entrada: %02d/%02d/%04d\n", raiz->paciente->nome, raiz->paciente->idade, raiz->paciente->entrada->dia, raiz->paciente->entrada->mes, raiz->paciente->entrada->ano);
        in_order(raiz->dir);
    }
}


void inserir_todos_pacientes_na_arvore(Arvore* arvore) {
    FILE* arq = fopen("pacientes.txt", "r");
    if (!arq) {
        printf("Erro ao abrir pacientes.txt\n");
        return;
    }

    char nome[LEN], rg[LEN];
    int idade;
    Data entrada;

    while (fscanf(arq, " %99[^\n]\n", nome) == 1) {
        fscanf(arq, " %99[^\n]\n", rg);
        fscanf(arq, "%d\n", &idade);
        fscanf(arq, "%d %d %d\n", &entrada.dia, &entrada.mes, &entrada.ano);

        Celula* novo = inicializa_celula();
        strcpy(novo->nome, nome);
        strcpy(novo->RG, rg);
        novo->idade = idade;
        novo->entrada->dia = entrada.dia;
        novo->entrada->mes = entrada.mes;
        novo->entrada->ano = entrada.ano;

        arvore->raiz = inserir_arvore_ano(arvore->raiz, novo);
        arvore->qtde++;
    }

    fclose(arq);
}

void inserir_todos_pacientes_na_arvore_mes(Arvore* arvore) {
    FILE* arq = fopen("pacientes.txt", "r");
    if (!arq) {
        printf("Erro ao abrir pacientes.txt\n");
        return;
    }

    char nome[LEN], rg[LEN];
    int idade;
    Data entrada;

    while (fscanf(arq, " %99[^\n]\n", nome) == 1) {
        fscanf(arq, " %99[^\n]\n", rg);
        fscanf(arq, "%d\n", &idade);
        fscanf(arq, "%d %d %d\n", &entrada.dia, &entrada.mes, &entrada.ano);

        Celula* novo = inicializa_celula();
        strcpy(novo->nome, nome);
        strcpy(novo->RG, rg);
        novo->idade = idade;
        novo->entrada->dia = entrada.dia;
        novo->entrada->mes = entrada.mes;
        novo->entrada->ano = entrada.ano;

        arvore->raiz = inserir_arvore_mes(arvore->raiz, novo);
        arvore->qtde++;
    }

    fclose(arq);
}

void inserir_todos_pacientes_na_arvore_dia(Arvore* arvore) {
    FILE* arq = fopen("pacientes.txt", "r");
    if (!arq) {
        printf("Erro ao abrir pacientes.txt\n");
        return;
    }

    char nome[LEN], rg[LEN];
    int idade;
    Data entrada;

    while (fscanf(arq, " %99[^\n]\n", nome) == 1) {
        fscanf(arq, " %99[^\n]\n", rg);
        fscanf(arq, "%d\n", &idade);
        fscanf(arq, "%d %d %d\n", &entrada.dia, &entrada.mes, &entrada.ano);

        Celula* novo = inicializa_celula();
        strcpy(novo->nome, nome);
        strcpy(novo->RG, rg);
        novo->idade = idade;
        novo->entrada->dia = entrada.dia;
        novo->entrada->mes = entrada.mes;
        novo->entrada->ano = entrada.ano;

        arvore->raiz = inserir_arvore_dia(arvore->raiz, novo);
        arvore->qtde++;
    }

    fclose(arq);
}

void inserir_todos_pacientes_na_arvore_idade(Arvore* arvore) {
    FILE* arq = fopen("pacientes.txt", "r");
    if (!arq) {
        printf("Erro ao abrir pacientes.txt\n");
        return;
    }

    char nome[LEN], rg[LEN];
    int idade;
    Data entrada;

    while (fscanf(arq, " %99[^\n]\n", nome) == 1) {
        fscanf(arq, " %99[^\n]\n", rg);
        fscanf(arq, "%d\n", &idade);
        fscanf(arq, "%d %d %d\n", &entrada.dia, &entrada.mes, &entrada.ano);

        Celula* novo = inicializa_celula();
        strcpy(novo->nome, nome);
        strcpy(novo->RG, rg);
        novo->idade = idade;
        novo->entrada->dia = entrada.dia;
        novo->entrada->mes = entrada.mes;
        novo->entrada->ano = entrada.ano;

        arvore->raiz = inserir_arvore_idade(arvore->raiz, novo);
        arvore->qtde++;
    }

    fclose(arq);
}




// Menu de Pesquisa (exemplo de uso)
void menu_pesquisa() {
    Arvore arvoreAno;
    Arvore arvoreMes;
    Arvore arvoreDia;
    Arvore arvoreIdade;
    arvoreAno.raiz = NULL;
    arvoreAno.qtde = 0;
    arvoreMes.raiz = NULL;
    arvoreMes.qtde = 0;
    arvoreDia.raiz = NULL;
    arvoreDia.qtde = 0;
    arvoreIdade.raiz = NULL;
    arvoreIdade.qtde = 0;

    inserir_todos_pacientes_na_arvore(&arvoreAno);
    inserir_todos_pacientes_na_arvore_mes(&arvoreMes);
    inserir_todos_pacientes_na_arvore_dia(&arvoreDia);
    inserir_todos_pacientes_na_arvore_idade(&arvoreIdade);

    int op;
    do {
        printf("\n--- Menu Pesquisa ---\n");
        printf("1. Ordenado por ANO\n");
        printf("2. Ordenado por M\u00caS\n");
        printf("3. Ordenado por DIA\n");
        printf("4. Ordenado por IDADE\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &op);

        switch (op) {
            case 1: 
            in_order(arvoreAno.raiz);
            break;
            case 2: 
            in_order(arvoreMes.raiz);
            break;
            case 3: 
            in_order(arvoreDia.raiz);
            break;
            case 4: 
            in_order(arvoreIdade.raiz);
            break;
            case 0:
            break;
            default: 
            printf("Op\u00e7\u00e3o inv\u00e1lida.\n");
        }
    } while (op != 0);
}


int menu_fila(Fila *fila) {
    char ch, buffer[256];
    char nome[LEN];

    while (1) {
        printf("\n==========================================\n");
        printf("             MENU DA FILA");
        printf("\n==========================================\n");
        printf("1 - Enfilerar Paciente\n");
        printf("2 - Remover da Fila\n");
        printf("3 - Mostrar Fila\n");
        printf("0 - Voltar Para O Menu Do Sistema\n");
        printf("\n==========================================\n");
        printf("Escolha: ");
        fgets(buffer, sizeof(buffer), stdin);
        ch = buffer[0];

        switch (ch) {
            case '1':
                printf("Digite o nome completo do paciente: ");
                fgets(nome, LEN, stdin);
                limpar_espacos(nome);
                enfilerar(fila, nome);    
                break;

            case '2':
                remover_da_fila(fila);
                break;

            case '3':
                Mostra_Fila(fila);
                break;

            case '0':
                liberar_fila(fila);
             return 0;

            default:
                printf("Opção inválida!\n");
        }
    }
}

int menu_fila_prioritario(FilaP *f) {
    char ch, buffer[256];
    char nome[LEN];

    while (1) {
        printf("\n================================================\n");
        printf("             MENU DO ATENDIMENTO PRIORITARIO");
        printf("\n================================================\n");
        printf("1 - Adicionar paciente a fila\n");
        printf("2 - Atender paciente na fila\n");
        printf("3 - Mostrar Fila\n");
        printf("0 - Voltar Para O Menu Do Sistema\n");
        printf("\n================================================\n");
        printf("Escolha: ");
        fgets(buffer, sizeof(buffer), stdin);
        ch = buffer[0];

        switch (ch) {
            case '1':
                adicionar_na_heap(f);   
                break;

            case '2':
                remover_maior_prioridade(f);
                break;

            case '3':
                mostrar_heap(f);
                break;

            case '0':
             return 0;

            default:
                printf("Opção inválida!\n");
        }
    }
}

void menu(Lista* l, Fila* f, FilaP *h){
    char ch, buffer[256];

    while (1) {
        printf("\n==========================================\n");
        printf("             MENU DO SISTEMA");
        printf("\n==========================================\n");
        printf("1 - Cadastro\n");
        printf("2 - Fila De Atendimento\n");
        printf("3 - Fila De Atendimento Prioritario\n");
        printf("4 - Pesquisar\n");
        printf("5 - \n");
        printf("6 - \n");
        printf("7 - Sobre\n");
        printf("0 - Sair\n");
        printf("\n==========================================\n");
        printf("Escolha: ");
        fgets(buffer, sizeof(buffer), stdin);
        ch = buffer[0];

        switch (ch) {
            case '1':
                menu_cadastro(l);
                break;

            case '2':
                menu_fila(f);
                break;
            case '3': 
                menu_fila_prioritario(h);
                break; 
            case '4':
                menu_pesquisa();
                break;
            case '5': 
                break; 
            case '6':
                break;
            case '7':
                Sobre();
                break;

            case '0':
                printf("Adeus!\n");
                liberar_fila(f);
                liberar_lista(l);
                return;

            default:
                printf("Opção inválida!\n");
        }
    }
}

// Função principal
int main() {
    FilaP filap;
    filap.qtde = 0;
    Lista *lista = inicializa_lista();
    Fila *fila = inicializa_fila(); 
    ler_pacientes(lista);
    menu(lista, fila, &filap);
    return 0;
}


// Erro de logica na fila prioritaria (Alguns nomes nao sao ordenados quando sao inseridos na Heap, mas ao utilizar a funcao de remover da fila, eles sao ordenados, teoricamente ta funcionando )
// Erro de logica na fila prioritaria (A fila nao da prioridade a pessoa que chegou primeiro q tem a mesma idade, EX: Matheus tem 20 anos e chegou primeiro, Luana tem 20 anos e chegou depois, Luana eh atendida primeiro que o Matheus)