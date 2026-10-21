#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    char nome_cat[50];
    char descricao_cat[200];
    int quant_cat;
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
int alocar_memoria(Produto **produtos_temp, int *x, int **encontrar_filtro);
void alocar_produtos(Produto *produtos_aloc, int *j);
void mostrar_produtos(Produto *produtos_mostrar, int y);
//mostrar produto individual (a fazer);
int buscar_produto(Produto *produtos_buscar, int z, int *confirm_buscar);
int *filtrar_produtos(Produto *produtos_filtrar, int w, int *confirm_filtrar);
void alterar_produtos(Produto **produtos_alterar, int m);


int main() {
    Produto *produtos = NULL;

    int n = 0, i, choice = 10, choice_ind = 0, confirm = 0, find_main, *find_filtro, alocar_result;

    do {
        
        exibir_menu(&choice);
        
        switch(choice) {

            case 1:
            alocar_result = alocar_memoria(&produtos, &n, &find_filtro);

            if(alocar_result == 1) {
                printf("Entrou aqui");
                return 1;
            }
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
                confirm = 0;
                break;
            case 4: 
                find_filtro = filtrar_produtos(produtos, n, &confirm);

                if(confirm == 0) {
                    for(i = 0; i < n; i++) {
                        if(find_filtro[i] != 0) {
                            printf("Nome: %s.\n", (produtos+i)->nome);
                            printf("Categoria: %s.\n", (produtos+i)->categoria.nome_cat);
                            printf("Descricao: %s.\n", (produtos+i)->descricao);
                            printf("Estoque: %d.\n", (produtos+i)->estoque);
                            printf("Marca: %s.\n", (produtos+i)->marca);
                            printf("Peso: %.2f.\n", (produtos+i)->peso);
                            printf("Local: %s.\n", (produtos+i)->local);
                        }
                    }
                }
                confirm = 0;
                break;
            case 5:
                alterar_produtos(&produtos, n);

        }

    } while(choice != 0);

    free(produtos);
    free(find_filtro);

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

int alocar_memoria(Produto **produtos_temp, int *x, int **encontrar_filtro) {

    printf("Quantos produtos voce quer alocar?\n");
    scanf(" %d", x);

    Produto *temp = realloc(*produtos_temp,(size_t) *x * sizeof(Produto));
    int *temp2 = realloc(*encontrar_filtro,(size_t) *x * sizeof(int));

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
        scanf(" %49s", produtos_aloc[i].local);
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
                printf("Local: %s.\n", (produtos_mostrar+i)->local);
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

int *filtrar_produtos(Produto *produtos_filtrar, int w, int *confirm_filtrar) {
    char filtro_buscar[50];
    int i, count = 0;
    int *find_filtrar, choice_filtro = 0;

    printf("Por qual fator você deseja filtrar?\n");
    printf("[1] - Categoria\n");
    printf("[2] - Marca\n");
    printf("[3] - Local\n");

    scanf(" %d", &choice_filtro);

    switch(choice_filtro) {
        case 1:
            printf("Digite a categoria:\n");
            scanf(" %s", &filtro_buscar);

            for(i = 0; i < w; i++) {
                if(strcmp((produtos_filtrar+i)->categoria.nome_cat, filtro_buscar) == 0) {
                    count++;
                    *(find_filtrar+i) = i;
                }
            }
            if (count >= 1) {
                printf("Produtos encontrados.\n");
                *confirm_filtrar = 0;
                return find_filtrar;
            }
            if(count == 0) {
                printf("Nenhum produto encontrado.\n");
                *confirm_filtrar = 1;
            }
            break;
        case 2:
            printf("Digite a marca:\n");
            scanf(" %s", &filtro_buscar);

            for(i = 0; i < w; i++) {
                if(strcmp((produtos_filtrar+i)->marca, filtro_buscar) == 0) {
                    count++;
                    find_filtrar = i;
                }
            }
            if (count > 1) {
                printf("Produtos encontrados.\n");
                *confirm_filtrar = 0;
                return find_filtrar;
            }
            if(count == 0) {
                printf("Nenhum produto encontrado.\n");
                *confirm_filtrar = 1;
            }
            break;
        case 3:
            printf("Digite o local:\n");
            scanf(" %s", &filtro_buscar);

            for(i = 0; i < w; i++) {
                if(strcmp((produtos_filtrar+i)->local, filtro_buscar) == 0) {
                    count++;
                    find_filtrar = i;
                }
            }
            if (count > 1) {
                printf("Produtos encontrados.\n");
                *confirm_filtrar = 0;
                return find_filtrar;
            }
            if(count == 0) {
                printf("Nenhum produto encontrado.\n");
                *confirm_filtrar = 1;
            }
            break;
    }
}

void alterar_produtos(Produto **produtos_alterar, int m) {
    int choice_alterar, j, confirm, i;
    printf("Qual dado você deseja alterar?\n");
    printf("[1] - Nome\n");
    printf("[2] - Categoria\n");
    printf("[3] - Descricao\n");
    printf("[4] - Estoque\n"); //falta finalizar esta parte
    printf("[5] - Marca\n");
    printf("[6] - Peso\n");
    printf("[7] - Local\n");
    scanf(" %d", &choice_alterar);

    printf("De qual produto? (Digite o nome).\n");
    scanf(" %s", &j);

    i = buscar_produto(*produtos_alterar, m, &confirm);

    printf("Digite o novo nome do produto %d: \n", i);
    scanf(" %99s", (*produtos_alterar)[i].nome);

}


