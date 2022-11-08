#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXTO 20000
#define MAX_PALAVRA 50

char TEXTO[MAX_TEXTO];
int TAM_TEXTO;
int QTD_PALAVRAS;

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
int altura_arv(no *raiz);
int conta_nos_arvore(no *raiz);

/* LISTAS LIGADAS */

int conta_nos_lista(lista_ligada *l);
void inserir_lista(lista_ligada *l, no *raiz);
void print_lista(lista_ligada *l);
void MontarLista(no *raiz, vetor_lista_ligada *vl);
void Print();

/* FUNÇÕES DE PALAVRAS */

int ordem(char a[], char b[]);
int iguais(char a[], char b[]);
int caractere_valido(char c);
char normalizado(char ch);

int main(){
    resolver();
    return 0;
}

void resolver(){
    char nome_arquivo[] = "";
    int k;
    int i = 0;
    int tamanho_lista_ligada;
    int *vetor_zipfy;
    char acao;
    no a;
    vetor_lista_ligada vl;

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

    /* inicialização da lista ligada */
    tamanho_lista_ligada = QTD_PALAVRAS;
    vetor_zipfy = malloc((tamanho_lista_ligada + 6)*sizeof(int));
    vl.lista = malloc((tamanho_lista_ligada + 6)*sizeof(lista_ligada));

    /* inicializa o vetor de listas ligadas */
    for(i = 0; i < tamanho_lista_ligada; i++){
        vl.lista[i].proximo = NULL;
        vl.lista[i].x = 0;
    }

    /* montagem da lista ligada */
    MontarLista(&a, &vl);

    /* recebe o inteiro k do usuário */
    printf("Digite um inteiro k > 0 para ver a lista de palavras de frequencia f_i = k\n");
    scanf(" %d", &k);
    printf("Imprimindo palavras de frequencia f_i = %d\n", k);
    print_lista(&vl.lista[k]);

    /* exibição de estatísticas */
    printf("Pronto!\nDeseja ver estatisticas?\n[a] Sim\n[b] Nao\n");
    scanf(" %c", &acao);

    if(acao == 'a'){
        /* mostra quantidade de nós utilizados */
        printf("quantidade de nos da arvore: %d\n", conta_nos_arvore(&a));
        printf("altura da arvore: %d\n", altura_arv(&a));
        printf("quantidade de nos na lista ligada: %d\n", conta_nos_lista(&vl.lista[k]));
        
        /* monta o vetor de zipfy */
        printf("Exibindo distribuicao das palavras em ordem crescente de frequencia (vetor zipfy)\n", QTD_PALAVRAS);
        for(i = 1; i < tamanho_lista_ligada; i++){
            vetor_zipfy[i] = conta_nos_lista(&vl.lista[i]) - 1;
            printf("%d ", vetor_zipfy[i]);
        }
    } else {
        Print();
    }
    
}

/* faz a leitura do arquivo de nome indicado pelo parâmetro e o registra na string do texto */
void LerTexto(char nome_arquivo[]){
    FILE *arquivo = NULL;
    int overflow = 0;

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
                overflow = 1;
                printf("tamanho do arquivo excede a capacidade do programa.\n");
                break;
            }
        }
        TAM_TEXTO = i;
        if(!overflow)
            printf("Texto lido com sucesso\n");
        /* fechamento do arquivo */
        fclose(arquivo);
    }
    
}

/* ----------------FUNÇÕES DE ÁRVORES---------------- */

/* insere as palavras na árvore de busca binária */
void MontarArvore(no *raiz){
    char * palavra_atual;
    palavra_atual = strtok(TEXTO, " ");

    QTD_PALAVRAS = 0;
    while(palavra_atual != NULL ) {
        inserir_no(raiz, palavra_atual);
        palavra_atual = strtok(NULL, " ");
        QTD_PALAVRAS++;
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

/* devolve a altura de uma árvore */
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

/* conta a quantidade de nós presentes na árvore de busca binária*/
int conta_nos_arvore(no *raiz){
    int qtd_esq;
    int qtd_dir;
    if(raiz == NULL)
        return 0;
    else{
        qtd_esq = conta_nos_arvore(raiz->no_esquerdo);
        qtd_dir = conta_nos_arvore(raiz->no_direito);
    }
    return 1 + qtd_esq + qtd_dir;
}

/* ----------------FUNÇÕES DE CARACTERES---------------- */

/* conta a quantidade de nós presentes na lista ligada */
int conta_nos_lista(lista_ligada *l){
    if(l != NULL)
        return 1 + conta_nos_lista(l->proximo);
    return 0;
}

/* insere um nó da árvore binária na lista ligada */
void inserir_lista(lista_ligada *l, no *raiz){
    char * elemento = raiz->palavra;
    lista_ligada *aux = malloc(sizeof(lista_ligada));
    aux->x = elemento;
    aux->no_arv = raiz;

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
            inserir_lista(l->proximo, raiz);
        }
    }
}

/* printa as palavras de uma lista ligada */
void print_lista(lista_ligada *l){
    char *palavra_nula = "";
    if(l != NULL){
        if(l->x != 0 && l->x != palavra_nula){
            printf("%s\n", l->x);
        }
        print_lista(l->proximo);
    }
}

/* insere os nós da árvore de busca binária no vetor de listas */
void MontarLista(no *raiz, vetor_lista_ligada *vl){
    if(raiz != NULL){
        inserir_lista(&vl->lista[raiz->frequencia], raiz);
        MontarLista(raiz->no_esquerdo, vl);
        MontarLista(raiz->no_direito, vl);
    }
}

/* ----------------FUNÇÕES DE LISTAS---------------- */

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

/* faz a exibição das estatísticas */
void Print(){
    /* parabéns, você achou um easter egg! xD*/
    printf("bobao cara de pudim vou invadir o capitolio! xD\n");
    /* jamais traduza a palavra abaixo para binário */
    /* 01101000 01110100 01110100 01110000 01110011 00111010 00101111 00101111 01110111 01110111 01110111 00101110 01111001 01101111 01110101 01110100 01110101 01100010 01100101 00101110 01100011 01101111 01101101 00101111 01110111 01100001 01110100 01100011 01101000 00111111 01110110 00111101 01100100 01010001 01110111 00110100 01110111 00111001 01010111 01100111 01011000 01100011 01010001  */
}