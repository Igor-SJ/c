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
    char local[50];
    Categoria categoria;
} Produto;

int main() {
    Produto *produtos = NULL;

    int n, i, choice = 10;

    do {
        printf("BEM VINDO!\n==============================\nSelecione uma opcao.\n");
        printf("[1] - Catalogar produtos.\n");
        printf("[2] - Exibir informação de produtos.\n"); //dentro daqui, colocar opcao de filtros
        printf("[3] - Buscar produto.\n");
        printf("[4] - Alterar dados.\n");
        printf("[5] - Placeholder.\n");
        printf("[0] - Sair.\n\n");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Quantos produtos voce quer alocar?\n");
                scanf("%d", &n);

                Produto *temp = realloc(produtos, n * sizeof(Produto) );

                if (temp == NULL && n > 0) {
                    printf("Erro na alocacao de memoria.\n");
                    return 1;
                }

                if (n < 0) {
                    printf("Quantidade invalida.\n");
                    return 1;
                }

                produtos = temp;

                printf("Alocacao feita com sucesso!\n");

                for(i = 0; i < n; i++) {
                    printf("Categoria do produto %d: \n", i+1);
                    scanf(" %49s", produtos[i].categoria.nome_cat);
                    printf("Nome do produto %d: \n", i+1);
                    scanf(" %99s", produtos[i].nome);
                    printf("Descricao do produto %d: \n", i+1);
                    scanf(" %299s", produtos[i].descricao);
                    printf("Estoque total do produto %d: \n", i+1);
                    scanf(" %d", &produtos[i].estoque);
                    printf("Marca do produto %d: \n", i+1);
                    scanf(" %49s", produtos[i].marca);
                    printf("Peso do produto %d: \n", i+1);
                    scanf(" %f", &produtos[i].peso);
                }

        }

    } while(choice != 0);

    free(produtos);

    printf("Memoria liberada com sucesso.\n");

    printf("=======================\nAdeus!");
    
    return 0;
}