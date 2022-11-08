#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXTO 20000
#define MAX_PALAVRA 50

char TEXTO[MAX_TEXTO];
int TAM_TEXTO;

typedef struct celula {
    int frequencia;
    char *palavra;
    struct celula *no_esquerdo;
    struct celula *no_direito;
} no;

typedef struct lista_ligada {
    no *no_arv;
    char *x;
    struct lista_ligada *proximo;
} lista_ligada;

typedef struct vetor_lista_ligada {
    lista_ligada *lista;
} vetor_lista_ligada;

/* FUNÇÕES DE ALTO NÍVEL */

void resolver();
void LerTexto(char nome_arquivo[]);

/* FUNÇÕES DE ÁRVORES */

void MontarArvore(no *raiz);
no * inserir_no(no *raiz, char *palavra);
void print_arv(no *raiz);

/* FUNÇÕES DE PALAVRAS */

int ordem(char a[], char b[]);
int iguais(char a[], char b[]);
int caractere_valido(char c);
char normalizado(char ch);

/* Listas Ligadas */

void inserir_lista(lista_ligada *l, char * elemento){
    lista_ligada *aux = malloc(sizeof(lista_ligada));
    aux->x = elemento;

    if(l == NULL){
        /* nó atual é nulo */
        aux->proximo = NULL;
        l = aux;
        return;
    }
    if(l->proximo == NULL){
        /* próximo no é nulo — inserir no fim da lista*/
        aux->proximo = NULL;
        l->proximo = aux;
        return;
    } else {
        /* próximo no existe */
        if(ordem(elemento, l->proximo->x)){
            /* no deve ser inserido entre o atual e o próximo*/
            aux->proximo = l->proximo;
            l->proximo = aux;
            return;
        } else {
            /* continuar procurando */
            inserir_lista(l->proximo, elemento);
        }
    }
}

void print_lista(lista_ligada *l){
    if(l != NULL){
        printf("%s -> ", l->x);
        print_lista(l->proximo);
    }
}

void l(){
    lista_ligada l;
    l.x = 0;
    l.proximo = NULL;
    inserir_lista(&l, "gato");
    print_lista(&l);
    printf("\n");
    inserir_lista(&l, "abacate");
    print_lista(&l);
    printf("\n");
    inserir_lista(&l, "beterraba");
    print_lista(&l);
    printf("\n");
}

int main(){
    l();
    return 0;
}

void resolver(){
    char nome_arquivo[] = "";
    no a;

    /* obtenção do texto */
    printf("Digite o nome do arquivo com terminacao .txt\n");
    scanf("%s", nome_arquivo);
    LerTexto(nome_arquivo);
    
    /* inicialização do primeiro nó */
    a.frequencia = 1;
    a.palavra = "";
    a.no_esquerdo = NULL;
    a.no_direito = NULL;

    /* inserção das palavras na árvore de busca binária */
    MontarArvore(&a);
    print_arv(&a);

    /* montagem da lista ligada */
}

/* faz a leitura do arquivo de nome indicado pelo parâmetro e o registra na string do texto */
void LerTexto(char nome_arquivo[]){
    FILE *arquivo = NULL;

    /* tentativa de abrir o arquivo .txt */
    arquivo = fopen(nome_arquivo, "r");
    if(arquivo == NULL){
        /* caso de erro */
        printf("Arquivo Nao Encontrado\n");
        return;
    } else {
        /* caso de sucesso */
        char ch;
        int i = 0;

        printf("lendo arquivo: %s\n", nome_arquivo);
        /* lê cada caractere e o registra na string principal */
        while ((ch = (char)fgetc(arquivo)) != EOF){

            /* tratamento de caracteres especiais */
            if(caractere_valido(ch)){
                TEXTO[i] = normalizado(ch);
                i++;
            }
            
            /* caso de overflow */
            if(i > MAX_TEXTO){
                printf("tamanho do arquivo excede a capacidade do programa.\n");
                break;
            }
        }
        TAM_TEXTO = i;

        /* fechamento do arquivo */
        fclose(arquivo);
    }
}

/* insere as palavras na árvore de busca binária */
void MontarArvore(no *raiz){
    char * palavra_atual;
    palavra_atual = strtok(TEXTO, " ");

    while(palavra_atual != NULL ) {
        inserir_no(raiz, palavra_atual);
        palavra_atual = strtok(NULL, " ");
    }
}

/* insere um no na árvore de busca binária */
no * inserir_no(no *raiz, char *palavra){
    /* se a raiz é nula, basta inserir neste exato no */
    if(raiz == NULL){
        no * aux = malloc(sizeof(no));
        aux->frequencia = 1;
        aux->no_esquerdo = NULL;
        aux->no_direito = NULL;
        aux->palavra = palavra;
        return aux;
    } 

    /* quando a palavra é igual, basta apenas incrementar a frequência */
    if(iguais(raiz->palavra, palavra)) {
        raiz->frequencia = raiz->frequencia + 1;
        return raiz;
    }

    /* caminhar para esquerda ou para direita e repetir o processo recursivamente */
    if(!ordem(raiz->palavra, palavra)){
        raiz->no_esquerdo = inserir_no(raiz->no_esquerdo, palavra);
    } else {
        raiz->no_direito = inserir_no(raiz->no_direito, palavra);
    }

    /* retorno padrão */
    return raiz;
}

/* imprime todos os elementos da árvore in ordem */
void print_arv(no *raiz){
    if(raiz != NULL){
        printf("%s(%d)\n", raiz ->palavra , raiz->frequencia);
        print_arv(raiz->no_esquerdo);
        print_arv(raiz->no_direito);
    }
}

/* verifica se duas palavras a e b estão em ordem alfabética */
int ordem(char a[], char b[]){
    int tamanho_a = 0;
    int tamanho_b = 0;
    int menor_tamanho = 0;
    int i = 0;

    /* obtenção tamanho de a */
    i = 0;
    while(a[i] != '\0')
        i++;
    tamanho_a = i;

    /* obtenção tamanho de b */
    i = 0;
    while(b[i] != '\0')
        i++;
    tamanho_b = i;

    /* menor tamanho de palavra */
    if(tamanho_a < tamanho_b)
        menor_tamanho = tamanho_a;
    else
        menor_tamanho = tamanho_b;

    /* verificação da ordem alfabética para cada caractere */
    for(i = 0; i < menor_tamanho; i++){
        if(a[i] > b[i])
            return 0;
        else if(a[i] < b[i])
            return 1;
    }

    /* casos em que somente a terminação é distinta */
    if(tamanho_a > tamanho_b)
        return 0;

    return 1;
}

/* verifica se duas palavras são iguais */
int iguais(char a[], char b[]){
    int i = 0;
    int tam_a, tam_b, tam_min;
    tam_a = tam_b = tam_min = 0;

    /* obtenção do tamanho de a*/
    i = 0;
    while (a[i] != '\0'){
        tam_a++;
        i++;
    }

    /* obtenção do tamanho de b*/
    i = 0;
    while (b[i] != '\0'){
        tam_b++;
        i++;
    }

    /* descarte de palavras de tamanhos diferentes */
    if(tam_a != tam_b)
        return 0;
    
    /* verificação caractere a caractere de cada palavra*/
    i = 0;
    while(i < tam_a){
        if(a[i] != b[i]){
            return 0;
        }
        i++;
    }
    
    /* sucesso em todos os testes */
    return 1;
}

/* verifica se o caractere é ASCII simples */
int caractere_valido(char c){
    if(c >= 'a' && c <= 'z'){
        return 1;
    } else if(c >= 'A' && c <= 'Z'){
        return 1;
    } else if(c == ' ' || c == '\n' || c == '\0'){
        return 1;
    }
    return 0;
}

/* pega um caracter especial e altera para um normal */
char normalizado(char ch){
    switch (ch){
    case '\n':
        return ' ';
        break;
    default:
        break;
    }
    return ch;
}