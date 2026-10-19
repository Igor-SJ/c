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
void alocar_categorias(Produto *categoria_aloc);
void mostrar_produtos(Produto *produtos_mostrar, int y);


int main() {
    Produto *produtos = NULL;

    int n = 0, i, choice = 10, choice_ind = 0;

    do {
        
        exibir_menu(&choice);
        
        switch(choice) {

            case 1:

                alocar_memoria(&produtos, &n);
                if (alocar_memoria(&produtos, &n) != 0) {
                    break;
                }
                printf("Voce deseja fazer isso para: \n");
                printf("[1] - Produtos\n");
                printf("[2] - Categorias\n");
                scanf("%d", &choice_ind);

                if(choice_ind == 1)
                    alocar_produtos(produtos, n);
                else 
                    alocar_categorias(produtos.categoria);
                
                break;

            case 2:
                mostrar_produtos(produtos, n);
                break;
        
            case 3:

                
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
    printf("[2] - Exibir informacao\n"); //dentro daqui, colocar opcao de filtros
    printf("[3] - Busca por nome.\n"); //eventualmente, posso juntar 1 com 2, e 3 com 4, ou mais
    printf("[4] - Alterar dados individuais.\n");
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
        printf("Local do produto %d: \n", i+1);
        scanf(" %s", produtos_aloc[i].local);
    }
}

void alocar_categorias(Produto *categoria_aloc) {
    int i;
    printf("Nome da categoria %d: \n", i+1);
    scanf(" %49s", categoria_aloc[i].categoria.nome_cat);
    printf("ID da categoria %d: \n", i+1);
    scanf(" %49s", categoria_aloc[i].categoria.nome_cat);
    



}

void mostrar_produtos(Produto *produtos_mostrar, int y) {
    int escolha, i;

    printf("Qual informacoes devem ser mostradas, alem do nome?\n");
    printf("[1] - Categoria\n");
    printf("[2] - Descricao\n");
    printf("[3] - Estoque\n");
    printf("[4] - Marca\n");
    printf("[5] - Peso\n");
    printf("[6] - Local\n");
    printf("[0] - Tudo\n");
    scanf(" %d", &escolha);

    switch(escolha) {
        case 1:
            for(i = 0; i < y; i++) {
                printf("Nome: %s.\n", (produtos_mostrar+i)->nome);
                printf("Categoria: %s.\n", (produtos_mostrar+i)->categoria.nome_cat);
            }
            break;
        case 2:
            for(i = 0; i < y; i++) {
                printf("Nome: %s.\n", (produtos_mostrar+i)->nome);
                printf("Descricao: %s.\n", (produtos_mostrar+i)->descricao);
            }
            break;  
        case 3:
            for(i = 0; i < y; i++) {
                printf("Nome: %s.\n", (produtos_mostrar+i)->nome);
                printf("Estoque: %d.\n", (produtos_mostrar+i)->estoque);
            }
            break;  
        case 4:
            for(i = 0; i < y; i++) {
                printf("Nome: %s.\n", (produtos_mostrar+i)->nome);
                printf("Marca: %s.\n", (produtos_mostrar+i)->marca);
            }
            break;  
        case 5:
            for(i = 0; i < y; i++) {
                printf("Nome: %s.\n", (produtos_mostrar+i)->nome);
                printf("Peso: %.2f.\n", (produtos_mostrar+i)->peso);
            }
            break;  
        case 6:
            for(i = 0; i < y; i++) {
                printf("Nome: %s.\n", (produtos_mostrar+i)->nome);
                printf("Peso: %s.\n", (produtos_mostrar+i)->local);
            }
            break;     
        case 0:
            for(i = 0; i < y; i++) {
                printf("Nome: %s.\n", (produtos_mostrar+i)->nome);
                printf("Categoria: %s.\n", (produtos_mostrar+i)->categoria.nome_cat);
                printf("Descricao: %s.\n", (produtos_mostrar+i)->descricao);
                printf("Estoque: %d.\n", (produtos_mostrar+i)->estoque);
                printf("Marca: %s.\n", (produtos_mostrar+i)->marca);
                printf("Peso: %.2f.\n", (produtos_mostrar+i)->peso);
                printf("Peso: %s.\n", (produtos_mostrar+i)->local);
            }
            break;  
    }
}