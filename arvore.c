#include <stdio.h>
#include <stdlib.h>

typedef struct celula {
    int frequencia;
    struct celula *no_esquerdo;
    struct celula *no_direito;
} no;

void print_arv(no *raiz, char style);
int altura_arv(no *raiz);
int qtd_nos_arv(no *raiz);
no* inserir_no(no * raiz, int x);

void print_arv(no *raiz, char style){
    if(raiz != NULL){
        printf("%d ", raiz->frequencia);
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

no * inserir_no (no * raiz, int x){
  if (raiz == NULL){
    raiz = malloc(sizeof (no));
    raiz -> frequencia = x;
    raiz -> no_esquerdo = raiz -> no_direito = NULL;
    return raiz; 
  }
  if (raiz -> frequencia == x)
    return raiz; 
  if (raiz -> frequencia < x)
    raiz -> no_direito = inserir_no(raiz -> no_direito, x);
  else 
    raiz -> no_esquerdo = inserir_no(raiz -> no_esquerdo, x);
  return raiz; 
}

no * busca (no * raiz, int x){
  if (raiz == NULL) return NULL;
  if (raiz -> frequencia == x) return raiz; 
  if (raiz -> frequencia < x)
    return busca (raiz -> no_direito, x);
  return busca (raiz -> no_esquerdo, x);
}