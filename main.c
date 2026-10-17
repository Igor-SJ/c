#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int id_cat;
    char nome_cat[50];
    char descricao_cat[200];
} Categoria;

typedef struct {
    int id;
    char nome[100];
    char descricao[300];
    float preco;
    int estoque;
    char marca[50];
    float peso;
    Categoria categoria;
} Produto;

int main() {
    Produto *produtos = NULL;

    int n;

    printf("Quantos produtos voce quer alocar?\n");
    scanf("%d", &n);

    Produto *temp = realloc(produtos, (n + 1) * sizeof(Produto) );

    printf("Alocacao feita com sucesso!\n");

    free(produtos);
    
    printf("Memoria liberada com sucesso.\n");
    return 0;
}