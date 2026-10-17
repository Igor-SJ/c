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

    int n, i;

    printf("Quantos produtos voce quer alocar?\n");
    scanf("%d", &n);

    Produto *temp = realloc(produtos, (n + 1) * sizeof(Produto) );

    printf("Alocacao feita com sucesso!\n");

    for(i = 0; i < n; i++) {
        printf("Nome do produto %d: \n", i+1);
        scanf("%s", produtos[i].nome);
        printf("Descricao do produto %d: \n", i+1);
        scanf("%s", produtos[i].descricao);
        printf("Estoque total do produto %d: \n", i+1);
        scanf("%d", &produtos[i].estoque);
        printf("Marca do produto %d: \n", i+1);
        scanf("%s", produtos[i].marca);
        printf("Peso do produto %d: \n", i+1);
        scanf("%f", &produtos[i].peso);
    }

    free(produtos);

    printf("Memoria liberada com sucesso.\n");
    return 0;
}