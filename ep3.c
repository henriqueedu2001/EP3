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
    struct lista_ligada *proximo;
} lista_ligada;

typedef struct vetor_lista_ligada {
    lista_ligada *lista;
    struct vetor_lista_ligada *proximo;
} vetor_lista_ligada;

void LerTexto(char nome_arquivo[]);
void MontarArvore(no *raiz);
int caractere_valido(char c);
int ordem(char a[], char b[]);

void print_arv(no *raiz);
no * inserir_no(no *raiz, char *palavra);

int resolver(){
    char nome_arquivo[] = "";

    /* obtenção do texto */
    printf("Digite o nome do arquivo com terminacao .txt\n");
    scanf("%s", nome_arquivo);
    LerTexto(nome_arquivo);

    return 0;
}

int main(){

    resolver();

    no a;
    a.frequencia = 1;
    a.palavra = "";
    a.no_esquerdo = NULL;
    a.no_direito = NULL;
    MontarArvore(&a);
    print_arv(&a);
    return 0;
}

int iguais(char a[], char b[]){
    int i = 0;
    int tam_a, tam_b, tam_min;
    tam_a = tam_b = tam_min = 0;

    printf("COMPARANDO: %s e %s\n", a, b);

    i = 0;
    while (a[i] != '\0'){
        tam_a++;
        i++;
    }

    i = 0;
    while (b[i] != '\0'){
        tam_b++;
        i++;
    }

    if(tam_a != tam_b)
        return 0;
    
    i = 0;
    while(i < tam_a){
        if(a[i] != b[i]){
            return 0;
        }
        i++;
    }
    
    
    
    return 1;
}

no * inserir_no(no *raiz, char *palavra){
    if(raiz == NULL){
        no * aux = malloc(sizeof(no));
        aux->frequencia = 1;
        aux->no_esquerdo = NULL;
        aux->no_direito = NULL;
        aux->palavra = palavra;
        return aux;
    } 
    printf("-%s%s- %d\n", raiz->palavra, palavra, iguais(raiz->palavra, palavra));
    if(iguais(raiz->palavra, palavra)) {
        printf("iguais\n");

        raiz->frequencia = raiz->frequencia + 1;
        return raiz;
    }
    if(!ordem(raiz->palavra, palavra)){
        raiz->no_esquerdo = inserir_no(raiz->no_esquerdo, palavra);
    } else {
        raiz->no_direito = inserir_no(raiz->no_direito, palavra);
    }
    return raiz;
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

void print_arv(no *raiz){
    if(raiz != NULL){
        printf("%s(%d)\n", raiz ->palavra , raiz->frequencia);
        print_arv(raiz->no_esquerdo);
        print_arv(raiz->no_direito);
    }
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
                TEXTO[i] = ch;
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