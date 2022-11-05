#include <stdio.h>
#include <stdlib.h>

typedef struct celula {
    int frequencia;
    char *palavra;
    struct celula *no_esquerdo;
    struct celula *no_direito;
} no;

void print_arv(no *raiz, char style);
int altura_arv(no *raiz);
int qtd_nos_arv(no *raiz);
no* inserir_no(no * raiz, char x[]);
int ordem(char a[], char b[]);

void print_arv(no *raiz, char style){
    if(raiz != NULL){
        printf("%s(%d) ", raiz ->palavra , raiz->frequencia);
        print_arv(raiz->no_esquerdo, 'd');
        print_arv(raiz->no_direito, 'd');
    }
}

int altura_arv(no *raiz){
    if(raiz == NULL){
        return 0;
    } else {
        int altura_esquerda = altura_arv(raiz->no_esquerdo);
        int altura_direita = altura_arv(raiz->no_direito);
        if(altura_esquerda > altura_direita){
            return 1 + altura_esquerda;
        } else {
            return 1 + altura_direita;
        }
    }
    return 0;
}

int qtd_nos_arv(no *raiz){
    if(raiz == NULL){
        return 0;
    } else {
        int qtd_esq = qtd_nos_arv(raiz->no_esquerdo);
        int qtd_dir = qtd_nos_arv(raiz->no_direito);
        return 1 + qtd_esq + qtd_dir;
    }
}

no * inserir_no (no * raiz, char x[]){
    if (raiz == NULL){
        raiz = malloc(sizeof (no));
        raiz -> frequencia = 1;
        raiz -> palavra = x;
        raiz -> no_esquerdo = raiz -> no_direito = NULL;
        return raiz; 
    }
    if (raiz -> palavra == x){
        raiz -> frequencia += 1;
        return raiz; 
    }
    if (ordem(raiz -> palavra, x))
        raiz -> no_direito = inserir_no(raiz -> no_direito, x);
    else 
        raiz -> no_esquerdo = inserir_no(raiz -> no_esquerdo, x);
    return raiz; 
}

no * busca (no * raiz, char x[]){
  if (raiz == NULL) return NULL;
  if (raiz -> palavra == x) return raiz; 
  if (raiz -> palavra < x)
    return busca (raiz -> no_direito, x);
  return busca (raiz -> no_esquerdo, x);
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