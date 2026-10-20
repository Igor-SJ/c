#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
void alocar_produtos(Produto *produtos_aloc, int *j);
void mostrar_produtos(Produto *produtos_mostrar, int y);
int buscar_produto(Produto *produtos_buscar, int z, int *confirm_buscar);


int main() {
    Produto *produtos = NULL;

    int n = 0, i, choice = 10, choice_ind = 0, confirm = 0, find_main;

    do {
        
        exibir_menu(&choice);
        
        switch(choice) {

            case 1:

                alocar_memoria(&produtos, &n);
               
                alocar_produtos(produtos, &n);
                
                break;

            case 2:
                mostrar_produtos(produtos, n);
                break;

            case 3:
                find_main = buscar_produto(produtos, n, &confirm);
                if(confirm == 0) {
                    i = find_main;
                        printf("Nome: %s.\n", (produtos+i)->nome);
                        printf("Categoria: %s.\n", (produtos+i)->categoria.nome_cat);
                        printf("Descricao: %s.\n", (produtos+i)->descricao);
                        printf("Estoque: %d.\n", (produtos+i)->estoque);
                        printf("Marca: %s.\n", (produtos+i)->marca);
                        printf("Peso: %.2f.\n", (produtos+i)->peso);
                        printf("Local: %s.\n", (produtos+i)->local);
                }
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
    printf("[3] - Buscar.\n"); //eventualmente, posso juntar 1 com 2, e 3 com 4, ou mais
    printf("[4] - Filtrar.\n");
    printf("[5] - Alterar dados individuais.\n");
    printf("[6] - Exibir informacoes de local.\n");
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

void alocar_produtos(Produto *produtos_aloc, int *j) {
    int i;
    for(i = 0; i < *j; i++) {
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
                printf("Local: %s.\n", (produtos_mostrar+i)->local);
            }
            break;  
    }
}

int buscar_produto(Produto *produtos_buscar, int z, int *confirm_buscar) {
    char nome_buscar[50];
    int i, j, count = 0;
    int find_buscar;
    printf("Digite o nome do produto:\n");
    scanf(" %s", &nome_buscar);

    for(i = 0; i < z; i++) {
        if(strcmp((produtos_buscar+i)->nome, nome_buscar) == 0) {
            count++;
            find_buscar = i;
        }
    }
    if (count == 1) {
        printf("Produto encontrado.\n");
        *confirm_buscar = 0;
        return find_buscar;
    }
    if(count > 1) {
        printf("Mais que um produto com este nome. Tente novamente por filtragem.\n");
        *confirm_buscar = 1;
    }
    if(count == 0) {
        printf("Nenhum produto encontrado.\n");
        *confirm_buscar = 1;
    }
}


