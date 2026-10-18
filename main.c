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

void exibir_menu(int *choice_temp);
int alocar_memoria(Produto **produtos_temp, int *x);
void alocar_produtos(Produto *produtos_aloc, int j);


int main() {
    Produto *produtos = NULL;

    int n, i, choice = 10;

    do {
        
        exibir_menu(&choice);
        
        switch(choice) {

            case 1:

                alocar_memoria(&produtos, &n);

            case 2:
                
                alocar_produtos(produtos, n);

        }

    } while(choice != 0);

    free(produtos);

    printf("Memoria liberada com sucesso.\n");

    printf("=======================\nAdeus!");
    
    return 0;
}

void exibir_menu(int *choice_temp) {
    printf("BEM VINDO!\n==============================\nSelecione uma opcao.\n");
    printf("[1] - Catalogar produtos.\n");
    printf("[2] - Exibir informacao de produtos.\n"); //dentro daqui, colocar opcao de filtros
    printf("[3] - Buscar produto.\n");
    printf("[4] - Alterar dados.\n");
    printf("[5] - Exibir informacoes de local.\n");
    printf("[0] - Sair.\n\n");
    scanf(" %d", choice_temp);
}

int alocar_memoria(Produto **produtos_temp, int *x) {

    printf("Quantos produtos voce quer alocar?\n");
    scanf(" %d", x);

    Produto *temp = realloc(*produtos_temp,(size_t) *x * sizeof(Produto));

    if (temp == NULL && *x > 0) {
        printf("Erro na alocacao de memoria.\n");
        return 1;
    }

    if (*x < 0) {
        printf("Quantidade invalida.\n");
        return 1;
    }

    *produtos_temp = temp;

    printf("Alocacao feita com sucesso!\n");

    return 0;
}

void alocar_produtos(Produto *produtos_aloc, int j) {
    int i;
    for(i = 0; i < j; i++) {
        printf("Categoria do produto %d: \n", i+1);
        scanf(" %49s", produtos_aloc[i].categoria.nome_cat);
        printf("Nome do produto %d: \n", i+1);
        scanf(" %99s", produtos_aloc[i].nome);
        printf("Descricao do produto %d: \n", i+1);
        scanf(" %299s", produtos_aloc[i].descricao);
        printf("Estoque total do produto %d: \n", i+1);
        scanf(" %d", &produtos_aloc[i].estoque);
        printf("Marca do produto %d: \n", i+1);
        scanf(" %49s", produtos_aloc[i].marca);
        printf("Peso do produto %d: \n", i+1);
        scanf(" %f", &produtos_aloc[i].peso);
    }
}