#include <stdio.h>
#include <stdlib.h>

#define MAX_TEXTO 20000
#define MAX_PALAVRA 50


typedef struct celula {
    int frequencia;
    char palavra[MAX_PALAVRA];
    struct celula *no_esquerdo;
    struct celula *no_direito;
} no;

char TEXTO[MAX_TEXTO];
int TAM_TEXTO;

no raiz;

void LerTexto(char nome_arquivo[]);
void MontarArvore();
int caractere_valido(char c);

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
    resolver();
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