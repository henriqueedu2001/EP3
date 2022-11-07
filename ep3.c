#include <stdio.h>
#include <stdlib.h>
#include "arvore.c"

#define MAX_TEXTO 20000
#define MAX_PALAVRA 50

char TEXTO[MAX_TEXTO];
int TAM_TEXTO;

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

int resolver(){
    char nome_arquivo[] = "";
    no raiz;

    raiz.frequencia = 0;
    raiz.no_esquerdo = NULL;
    raiz.no_direito = NULL;
    raiz.palavra = "";

    inserir_no(&raiz, "um");
    inserir_no(&raiz, "gato");
    inserir_no(&raiz, "comeu");
    inserir_no(&raiz, "o");
    inserir_no(&raiz, "passarinho");
    inserir_no(&raiz, "que");
    inserir_no(&raiz, "costumava");
    inserir_no(&raiz, "ficar");
    inserir_no(&raiz, "em");
    inserir_no(&raiz, "cima");
    inserir_no(&raiz, "da");
    inserir_no(&raiz, "cerca");
    inserir_no(&raiz, "mas");
    inserir_no(&raiz, "uma");
    inserir_no(&raiz, "vez");
    inserir_no(&raiz, "sinha");
    inserir_no(&raiz, "vitoria");
    inserir_no(&raiz, "pegou");
    inserir_no(&raiz, "o");
    inserir_no(&raiz, "gato");
    inserir_no(&raiz, "no");
    inserir_no(&raiz, "flagra");
    inserir_no(&raiz, "comendo");
    inserir_no(&raiz, "o");
    inserir_no(&raiz, "passarinho");

    print_arv(&raiz, 'p');
    busca_freq(&raiz, 2);

    /* obtenção do texto */
    printf("Digite o nome do arquivo com terminacao .txt\n");
    scanf("%s", nome_arquivo);
    LerTexto(nome_arquivo);

    /* obtenção das palavras do texto */
    MontarArvore(&raiz);
    print_arv(&raiz, 'p');
    return 0;
}

void print_lista_ligada(lista_ligada *l){
    if(l == NULL){
        return;
    } else {
        printf("%s\n", l->no_arv->palavra);
        print_lista_ligada(l->proximo);
    }
}

int main(){
    /*resolver();*/
    char nome_arquivo[] = "";
    no raiz;

    raiz.frequencia = 0;
    raiz.no_esquerdo = NULL;
    raiz.no_direito = NULL;
    raiz.palavra = "";

    inserir_no(&raiz, "um");
    inserir_no(&raiz, "gato");
    inserir_no(&raiz, "comeu");
    inserir_no(&raiz, "o");
    inserir_no(&raiz, "passarinho");
    inserir_no(&raiz, "que");
    inserir_no(&raiz, "costumava");
    inserir_no(&raiz, "ficar");
    inserir_no(&raiz, "em");
    inserir_no(&raiz, "cima");
    inserir_no(&raiz, "da");
    inserir_no(&raiz, "cerca");
    inserir_no(&raiz, "mas");
    inserir_no(&raiz, "uma");
    inserir_no(&raiz, "vez");
    inserir_no(&raiz, "sinha");
    inserir_no(&raiz, "vitoria");
    inserir_no(&raiz, "pegou");
    inserir_no(&raiz, "o");
    inserir_no(&raiz, "gato");
    inserir_no(&raiz, "no");
    inserir_no(&raiz, "flagra");
    inserir_no(&raiz, "comendo");
    inserir_no(&raiz, "o");
    inserir_no(&raiz, "passarinho");

    print_arv(&raiz, 'p');

    printf("%s\n", raiz.palavra);
    printf("%s\n", (raiz.no_esquerdo)->palavra);
    printf("%s\n", (raiz.no_direito)->palavra);
    
    return 0;
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
    int i = 0; /* índice no texto*/
    int j = 0; /* índice na palavra*/
    int qtd = 0; /* quantidade de palavras */

    no aux;

    aux.frequencia = 0;
    aux.no_esquerdo = NULL;
    aux.no_direito = NULL;
    aux.palavra = "";
    char palavra_atual[MAX_PALAVRA] = "";

    while(i < TAM_TEXTO){
        /* registrar na palavra enquanto não encontrar espaços ou quebras de linha */
        if(TEXTO[i] != ' ' && TEXTO[i] != '\n'){
            palavra_atual[j] = TEXTO[i];
            j++;
        } else {
            /* insere na árvore binária */
            printf("%s\n", palavra_atual);

            /* deleção da palavra */
            for(j = 0; j < MAX_PALAVRA; j++)
                palavra_atual[j] = '\0';
            j = 0;
            qtd++;
        }
        i++;
    }
    print_arv(&aux, 'p');
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