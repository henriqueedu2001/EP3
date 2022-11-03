#include <stdio.h>
#include <stdlib.h>
#include "arvore.c"

#define MAX_TEXTO 20000
#define MAX_PALAVRA 50

char TEXTO[MAX_TEXTO];
int TAM_TEXTO;

void LerTexto(char nome_arquivo[]);
void MontarArvore();
int caractere_valido(char c);
int ordem(char a[], char b[]);

int resolver(){
    char nome_arquivo[] = "";

    /* obtenção do texto */
    printf("Digite o nome do arquivo com terminacao .txt\n");
    scanf("%s", nome_arquivo);
    LerTexto(nome_arquivo);
    printf("%s\n", TEXTO);

    /* obtenção das palavras do texto */
    MontarArvore();
    return 0;
}

int main(){
    /* resolver(); */
    int x = ordem("casa", "aexe");
    printf("%d\n", x);
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
void MontarArvore(){
    int i = 0; /* índice no texto*/
    int j = 0; /* índice na palavra*/
    int qtd = 0; /* quantidade de palavras */
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
                palavra_atual[j] = 0;
            j = 0;
            qtd++;
        }
        i++;
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