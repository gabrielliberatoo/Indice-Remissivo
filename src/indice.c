#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXPALAVRA 10

typedef struct paginas {
    int pagina;
    struct paginas* esquerda;
    struct paginas* direita;
    int altura;  // Adicionado campo 'altura'
} paginas_t;

typedef struct indentr {
    char palavra[MAXPALAVRA];
    paginas_t* paginas;
    struct indentr* esquerda;
    struct indentr* direita;
    int altura;  // Adicionado campo 'altura'
} indentr_t;

typedef struct indrem {
    indentr_t* raiz;
} indrem_t;

// Função para obter a altura de um nó
int altura_node(indentr_t* node) {
    if (node == NULL) return 0;
    int altura_esquerda = altura_node(node->esquerda);
    int altura_direita = altura_node(node->direita);
    return 1 + ((altura_esquerda > altura_direita) ? altura_esquerda : altura_direita);
}

// Função para obter a altura de uma página
int altura_paginas(paginas_t* node) {
    if (node == NULL) return 0;
    int altura_esquerda = altura_paginas(node->esquerda);
    int altura_direita = altura_paginas(node->direita);
    return 1 + ((altura_esquerda > altura_direita) ? altura_esquerda : altura_direita);
}

// Função para obter o fator de balanceamento de um nó
int get_balance(paginas_t* node) {
    if (node == NULL) return 0;
    return altura_paginas(node->esquerda) - altura_paginas(node->direita);
}

// Funções para árvore AVL de páginas
paginas_t* nova_pagina(int pagina) {
    paginas_t* node = (paginas_t*)malloc(sizeof(paginas_t));
    node->pagina = pagina;
    node->esquerda = NULL;
    node->direita = NULL;
    node->altura = 1;
    return node;
}

paginas_t* rotacao_direita_paginas(paginas_t* y) {
    paginas_t* x = y->esquerda;
    paginas_t* T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    // Atualizar altura após rotação
    y->altura = altura_paginas(y);
    x->altura = altura_paginas(x);

    return x;
}

paginas_t* rotacao_esquerda_paginas(paginas_t* x) {
    paginas_t* y = x->direita;
    paginas_t* T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    // Atualizar altura após rotação
    x->altura = altura_paginas(x);
    y->altura = altura_paginas(y);

    return y;
}

paginas_t* inserir_pagina(paginas_t* node, int pagina) {
    if (node == NULL) return nova_pagina(pagina);

    if (pagina < node->pagina)
        node->esquerda = inserir_pagina(node->esquerda, pagina);
    else if (pagina > node->pagina)
        node->direita = inserir_pagina(node->direita, pagina);

    // Atualizar a altura do nó
    node->altura = altura_paginas(node);

    // Balancear a árvore
    int balance = get_balance(node);

    // Casos de desbalanceamento
    if (balance > 1 && pagina < node->esquerda->pagina)
        return rotacao_direita_paginas(node);

    if (balance < -1 && pagina > node->direita->pagina)
        return rotacao_esquerda_paginas(node);

    if (balance > 1 && pagina > node->esquerda->pagina) {
        node->esquerda = rotacao_esquerda_paginas(node->esquerda);
        return rotacao_direita_paginas(node);
    }

    if (balance < -1 && pagina < node->direita->pagina) {
        node->direita = rotacao_direita_paginas(node->direita);
        return rotacao_esquerda_paginas(node);
    }

    return node;
}

void imprimir_paginas(paginas_t* node) {
    if (node != NULL) {
        imprimir_paginas(node->esquerda);
        printf(" %d", node->pagina);
        imprimir_paginas(node->direita);
    }
}

// Funções para árvore AVL de palavras
indentr_t* nova_palavra(char* palavra, int pagina) {
    indentr_t* node = (indentr_t*)malloc(sizeof(indentr_t));
    strcpy(node->palavra, palavra);
    node->paginas = nova_pagina(pagina);
    node->esquerda = NULL;
    node->direita = NULL;
    node->altura = 1;
    return node;
}

indentr_t* rotacao_direita_palavras(indentr_t* y) {
    indentr_t* x = y->esquerda;
    indentr_t* T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    // Atualizar altura após rotação
    y->altura = altura_node(y);
    x->altura = altura_node(x);

    return x;
}

indentr_t* rotacao_esquerda_palavras(indentr_t* x) {
    indentr_t* y = x->direita;
    indentr_t* T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    // Atualizar altura após rotação
    x->altura = altura_node(x);
    y->altura = altura_node(y);

    return y;
}

indentr_t* inserir_palavra(indentr_t* node, char* palavra, int pagina) {
    if (node == NULL) return nova_palavra(palavra, pagina);

    int cmp_result = strcmp(palavra, node->palavra);

    if (cmp_result < 0)
        node->esquerda = inserir_palavra(node->esquerda, palavra, pagina);
    else if (cmp_result > 0)
        node->direita = inserir_palavra(node->direita, palavra, pagina);
    else
        node->paginas = inserir_pagina(node->paginas, pagina);

    // Atualizar a altura do nó
    node->altura = altura_node(node);

    // Balancear a árvore
    int balance = altura_node(node->esquerda) - altura_node(node->direita);

    // Casos de desbalanceamento
    if (balance > 1 && cmp_result < 0)
        return rotacao_direita_palavras(node);

    if (balance < -1 && cmp_result > 0)
        return rotacao_esquerda_palavras(node);

    if (balance > 1 && cmp_result > 0) {
        node->esquerda = rotacao_esquerda_palavras(node->esquerda);
        return rotacao_direita_palavras(node);
    }

    if (balance < -1 && cmp_result < 0) {
        node->direita = rotacao_direita_palavras(node->direita);
        return rotacao_esquerda_palavras(node);
    }

    return node;
}

void imprimir_palavras(indentr_t* node) {
    if (node != NULL) {
        imprimir_palavras(node->esquerda);
        printf("%s:", node->palavra);
        imprimir_paginas(node->paginas);
        printf("\n");
        imprimir_palavras(node->direita);
    }
}

// Função principal
int main() {
    char palavra[MAXPALAVRA];
    int pagina;
    indrem_t meuind;

    meuind.raiz = NULL;

    while (scanf("%s %d", palavra, &pagina) != EOF) {
        meuind.raiz = inserir_palavra(meuind.raiz, palavra, pagina);
    }

    imprimir_palavras(meuind.raiz);

    return 0;
}
