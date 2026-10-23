#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    char categoria[50];
    float preco;
    int estoque;
    char local[50];
} Data_g;

typedef struct {
    char nome[100];
    char descricao[300];
    char marca[50];
} Data_ind;

typedef struct {
    Data_ind dados_produto;
    Data_g dados_loja;
} Produto;

void exibir_menu(int *choice_temp);
int alocar_memoria(Produto **produtos_temp, int *x, int **encontrar_filtro);
void alocar_produtos(Produto *produtos_aloc, int *j);
void mostrar_produtos(Produto *produtos_mostrar, int y);
int buscar_produto(Produto *produtos_buscar, int z, int *confirm_buscar);
int *filtrar_produtos(Produto *produtos_filtrar, int w, int *confirm_filtrar);
void alterar_produtos(Produto **produtos_alterar, int m);
void print_tudo(Produto *produtos_print, int p); //
void find_verificar(Produto *produto_verificar, int *confirm_verificar, int count_verificar);
void salvar(Produto *produto_salvar, int *s);
void recuperar(Produto **produto_recuperar, int *r);

int main() {
    Produto *produtos = NULL;

    int n = 0, i, choice = 10, choice_ind = 0, confirm = 0, find_main, *find_filtro = NULL, alocar_result;

    do {
        
        exibir_menu(&choice);
        
        switch(choice) {

            case 1:
                alocar_result = alocar_memoria(&produtos, &n, &find_filtro);

                if(alocar_result == 1) {
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
                    int find_main_print = find_main;
                        print_tudo(produtos, find_main_print); 
                }
                confirm = 0;
                break;
            case 4: 
                free(find_filtro);
                find_filtro = filtrar_produtos(produtos, n, &confirm);
                int find_filtro_print = *find_filtro;

                if(confirm == 0) {
                    for(i = 0; i < n; i++) {
                        if(find_filtro[i] != 0)
                            print_tudo(produtos, i); 
                    }       
                }
                confirm = 0;
                break;
            case 5:
                alterar_produtos(&produtos, n);
                break;
            case 6:
                salvar(produtos, &n);
                break;
            case 7:
                recuperar(&produtos, &n);
                break;
            default:
                printf("Opcao invalida.\n");
        }

    } while(choice != 0);

    free(produtos);
    free(find_filtro);

    printf("Memoria liberada com sucesso.\n");

    printf("=======================\nAdeus!");
    
    return 0;
}

void exibir_menu(int *choice_temp) {
    printf("\n\n\nBEM VINDO!\n\n\n==============================\nSelecione uma opcao.\n");
    printf("[1] - Catalogar produtos.\n");
    printf("[2] - Exibir informacao\n"); //dentro daqui, colocar opcao de filtros
    printf("[3] - Buscar.\n"); //eventualmente, posso juntar 1 com 2, e 3 com 4, ou mais
    printf("[4] - Filtrar.\n");
    printf("[5] - Alterar dados individuais.\n");
    printf("[6] - Salvar dados.\n");
    printf("[7] - Recuperar dados.\n");
    printf("[0] - Sair.\n");
    scanf(" %d", choice_temp);
    int c_main; //consumir o enter
    while ((c_main = getchar()) != '\n' && c_main != EOF) {}
}

int alocar_memoria(Produto **produtos_temp, int *x, int **encontrar_filtro) {

    printf("Quantos produtos voce quer alocar?\n");
    scanf(" %d", x);

    int c; //consumir o enter
    while ((c = getchar()) != '\n' && c != EOF) {}

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
        fgets(
            produtos_aloc[i].dados_loja.categoria, 
            sizeof(produtos_aloc[i].dados_loja.categoria), 
            stdin
        );
        produtos_aloc[i].dados_loja.categoria[strcspn(produtos_aloc[i].dados_loja.categoria, "\n")] = '\0';
        //gasta o enter

        printf("Nome do produto %d: \n", i+1);
        fgets(
            produtos_aloc[i].dados_produto.nome, 
            sizeof(produtos_aloc[i].dados_produto.nome), 
            stdin
        );
        produtos_aloc[i].dados_produto.nome[strcspn(produtos_aloc[i].dados_produto.nome, "\n")] = '\0';
    
        printf("Descricao do produto %d: \n", i+1);
        fgets(
            produtos_aloc[i].dados_produto.descricao, 
            sizeof(produtos_aloc[i].dados_produto.descricao), 
            stdin
        );
        produtos_aloc[i].dados_produto.descricao[strcspn(produtos_aloc[i].dados_produto.descricao, "\n")] = '\0';
        

        printf("Estoque total do produto %d: \n", i+1);
        scanf(" %d", &produtos_aloc[i].dados_loja.estoque);
        int c_produtos; //consumir o enter
        while ((c_produtos = getchar()) != '\n' && c_produtos != EOF) {}

        printf("Marca do produto %d: \n", i+1);
        fgets(
            produtos_aloc[i].dados_produto.marca, 
            sizeof(produtos_aloc[i].dados_produto.marca), 
            stdin
        );
        produtos_aloc[i].dados_produto.marca[strcspn(produtos_aloc[i].dados_produto.marca, "\n")] = '\0';

        printf("Local do produto %d: \n", i+1);
        fgets(
            produtos_aloc[i].dados_loja.local, 
            sizeof(produtos_aloc[i].dados_loja.local), 
            stdin
        );
        produtos_aloc[i].dados_loja.local[strcspn(produtos_aloc[i].dados_loja.local, "\n")] = '\0';
        
    }
}

void mostrar_produtos(Produto *produtos_mostrar, int y) {
    int escolha, i;

    printf("Qual informacoes devem ser mostradas, alem do nome?\n");
    printf("[1] - Categoria\n");
    printf("[2] - Descricao\n");
    printf("[3] - Estoque\n");
    printf("[4] - Marca\n");
    printf("[5] - Local\n");
    printf("[0] - Tudo\n");
    scanf(" %d", &escolha);

    int c_mostrar;
    while ((c_mostrar = getchar()) != '\n' && c_mostrar != EOF) {}

    switch(escolha) {
        case 1:
            for(i = 0; i < y; i++) {
                printf("Nome: %s.\n", (produtos_mostrar+i)->dados_produto.nome);
                printf("Categoria: %s.\n", (produtos_mostrar+i)->dados_loja.categoria);
            }
            break;
        case 2:
            for(i = 0; i < y; i++) {
                printf("Nome: %s.\n", (produtos_mostrar+i)->dados_produto.nome);
                printf("Descricao: %s.\n", (produtos_mostrar+i)->dados_produto.descricao);
            }
            break;  
        case 3:
            for(i = 0; i < y; i++) {
                printf("Nome: %s.\n", (produtos_mostrar+i)->dados_produto.nome);
                printf("Estoque: %d.\n", (produtos_mostrar+i)->dados_loja.estoque);
            }
            break;  
        case 4:
            for(i = 0; i < y; i++) {
                printf("Nome: %s.\n", (produtos_mostrar+i)->dados_produto.nome);
                printf("Marca: %s.\n", (produtos_mostrar+i)->dados_produto.marca);
            }
            break;
        case 5:
            for(i = 0; i < y; i++) {
                printf("Nome: %s.\n", (produtos_mostrar+i)->dados_produto.nome);
                printf("Local: %s.\n", (produtos_mostrar+i)->dados_loja.local);
            }
            break;     
        case 0:
            for(i = 0; i < y; i++) {
                print_tudo(produtos_mostrar, i); 
            }
            break;  
        default:
            printf("Opcao invalida!\n");
    }
}

int buscar_produto(Produto *produtos_buscar, int z, int *confirm_buscar) {
    char nome_buscar[50];
    int i, j, count = 0;
    int find_buscar;
    printf("Digite o nome do produto:\n");
    fgets(
        nome_buscar, 
        sizeof(nome_buscar),
        stdin
        );

        nome_buscar[strcspn(nome_buscar, "\n")] = '\0';

    for(i = 0; i < z; i++) {
        if(strcmp((produtos_buscar+i)->dados_produto.nome, nome_buscar) == 0) {
            count++;
            find_buscar = i;
        }
    }
    find_verificar(produtos_buscar, confirm_buscar, count);

    return find_buscar;
}

int *filtrar_produtos(Produto *produtos_filtrar, int w, int *confirm_filtrar) {
    char filtro_buscar[50];
    int i, choice_filtro = 0;

    *confirm_filtrar = 1;

    if (w <= 0 || produtos_filtrar == NULL) {
        printf("Nenhum produto cadastrado.\n");
        return NULL; //colocar mais coisas como essa em outras funções
    }

    int *find_filtrar = calloc((size_t)w, sizeof(int));

    if (find_filtrar == NULL) {
        printf("Erro na alocacao de memoria.\n");
        return NULL;
    }

    printf("Por qual fator voce deseja filtrar?\n");
    printf("[1] - Categoria\n");
    printf("[2] - Marca\n");
    printf("[3] - Local\n");

    if (scanf("%d", &choice_filtro) != 1 ||
        choice_filtro < 1 || choice_filtro > 3) {
        printf("Opcao invalida.\n");
        free(find_filtrar);
        return NULL;
    }

    int c_filtrar;
    while ((c_filtrar = getchar()) != '\n' && c_filtrar != EOF) {}

    switch (choice_filtro) {
        case 1:
            printf("Digite a categoria:\n");
            break;
        case 2:
            printf("Digite a marca:\n");
            break;
        case 3:
            printf("Digite o local:\n");
            break;//depois tenho que fazer esse negocio do switch duplo
    }

    fgets(
        filtro_buscar, 
        sizeof(filtro_buscar),
        stdin
        );

        filtro_buscar[strcspn(filtro_buscar, "\n")] = '\0';

    for (i = 0; i < w; i++) {
        int corresponde = 0;

        switch (choice_filtro) {
            case 1:
                corresponde = strcmp(produtos_filtrar[i].dados_loja.categoria, filtro_buscar) == 0;
                break;

            case 2:
                corresponde = strcmp(produtos_filtrar[i].dados_produto.marca, filtro_buscar) == 0;
                break;

            case 3:
                corresponde = strcmp(produtos_filtrar[i].dados_loja.local, filtro_buscar) == 0;
                break;
        }

        if (corresponde) {
            find_filtrar[i] = 1;
            *confirm_filtrar = 0;
        }
    }

    if (*confirm_filtrar == 0) 
        printf("Produtos encontrados.\n");
     else 
        printf("Nenhum produto encontrado.\n");

    return find_filtrar;
}

void alterar_produtos(Produto **produtos_alterar, int m) {
    int choice_alterar, confirm_alterar, i, count_alterar = 0, find_alterar;
    char buscar_alterar[50];
    printf("Qual dado você deseja alterar?\n");
    printf("[1] - Nome\n");
    printf("[2] - Categoria\n");
    printf("[3] - Descricao\n");
    printf("[4] - Estoque\n");
    printf("[5] - Marca\n");
    printf("[6] - Local\n");
    scanf(" %d", &choice_alterar);

    int c_alterar;
    while ((c_alterar = getchar()) != '\n' && c_alterar != EOF) {}

    switch(choice_alterar) {
       
        case 1:
            printf("De qual produto? (Digite o nome).\n");
            
            fgets(
                buscar_alterar, 
                sizeof(buscar_alterar),
                stdin
                );

            buscar_alterar[strcspn(buscar_alterar, "\n")] = '\0';
            

            for(i = 0; i < m; i++) {
                if(strcmp((*produtos_alterar+i)->dados_produto.nome, buscar_alterar) == 0) {
                    count_alterar++;
                    strcpy(buscar_alterar, (*produtos_alterar+i)->dados_produto.nome);
                    find_alterar = i;
                }
            }
            
            find_verificar(*produtos_alterar, &confirm_alterar, count_alterar);

            if(confirm_alterar == 0) {
                printf("Digite o novo nome do produto: \n");
                fgets(
                    (*produtos_alterar+find_alterar)->dados_produto.nome, 
                    sizeof(*produtos_alterar)->dados_produto.nome, 
                    stdin
                );
                (*produtos_alterar+find_alterar)->dados_produto.nome[strcspn((*produtos_alterar+find_alterar)->dados_produto.nome, "\n")] = '\0';
            }
            break;
        case 2:
            printf("De qual produto? (Digite o nome).\n");
            scanf(" %s", &buscar_alterar);
            while ((c_alterar = getchar()) != '\n' && c_alterar != EOF) {}

            for(i = 0; i < m; i++) {
                if(strcmp((*produtos_alterar+i)->dados_produto.nome, buscar_alterar) == 0) {
                    count_alterar++;
                    strcpy(buscar_alterar, (*produtos_alterar+i)->dados_produto.nome);
                    find_alterar = i;
                }
            }

            find_verificar(*produtos_alterar, &confirm_alterar, count_alterar);

            if(confirm_alterar == 0) {
                printf("Digite a nova categoria do produto: \n");
                fgets(
                    (*produtos_alterar+find_alterar)->dados_loja.categoria, 
                    sizeof(*produtos_alterar)->dados_loja.categoria, 
                    stdin
                );
                (*produtos_alterar+find_alterar)->dados_loja.categoria[strcspn((*produtos_alterar+find_alterar)->dados_loja.categoria, "\n")] = '\0';
            }
            break;
        case 3: 
            printf("De qual produto? (Digite o nome).\n");
            scanf(" %s", &buscar_alterar);
            while ((c_alterar = getchar()) != '\n' && c_alterar != EOF) {}

            for(i = 0; i < m; i++) {
                if(strcmp((*produtos_alterar+i)->dados_produto.nome, buscar_alterar) == 0) {
                    count_alterar++;
                    strcpy(buscar_alterar, (*produtos_alterar+i)->dados_produto.nome);
                    find_alterar = i;
                }
            }
            
            find_verificar(*produtos_alterar, &confirm_alterar, count_alterar);

            if(confirm_alterar == 0) {
                printf("Digite a nova descricao do produto: \n");
                fgets(
                    (*produtos_alterar+find_alterar)->dados_produto.descricao, 
                    sizeof(*produtos_alterar)->dados_produto.descricao, 
                    stdin
                );
                (*produtos_alterar+find_alterar)->dados_produto.descricao[strcspn((*produtos_alterar+find_alterar)->dados_produto.descricao, "\n")] = '\0';
            }
            break;
        case 4:
            printf("De qual produto? (Digite o nome).\n");
            scanf(" %s", &buscar_alterar);
            while ((c_alterar = getchar()) != '\n' && c_alterar != EOF) {}

            for(i = 0; i < m; i++) {
                if(strcmp((*produtos_alterar+i)->dados_produto.nome, buscar_alterar) == 0) {
                    count_alterar++;
                    strcpy(buscar_alterar, (*produtos_alterar+i)->dados_produto.nome);
                    find_alterar = i;
                }
            }

            find_verificar(*produtos_alterar, &confirm_alterar, count_alterar);

            if(confirm_alterar == 0) {
                printf("Digite o novo estoque do produto: \n");
                scanf(" %d", &(*produtos_alterar+find_alterar)->dados_loja);
                while ((c_alterar = getchar()) != '\n' && c_alterar != EOF) {}
            }
            break;
        case 5:
            printf("De qual produto? (Digite o nome).\n");
            scanf(" %s", &buscar_alterar);
            while ((c_alterar = getchar()) != '\n' && c_alterar != EOF) {}

            for(i = 0; i < m; i++) {
                if(strcmp((*produtos_alterar+i)->dados_produto.nome, buscar_alterar) == 0) {
                    count_alterar++;
                    strcpy(buscar_alterar, (*produtos_alterar+i)->dados_produto.nome);
                    find_alterar = i;
                }
            }

            find_verificar(*produtos_alterar, &confirm_alterar, count_alterar);

            if(confirm_alterar == 0) {
                printf("Digite a nova marca do produto: \n");
                fgets(
                    (*produtos_alterar+find_alterar)->dados_produto.marca, 
                    sizeof(*produtos_alterar)->dados_produto.marca, 
                    stdin
                );
                (*produtos_alterar+find_alterar)->dados_produto.marca[strcspn((*produtos_alterar+find_alterar)->dados_produto.marca, "\n")] = '\0';
            }
            break;
        case 6:
            printf("De qual produto? (Digite o nome).\n");
            scanf(" %s", &buscar_alterar);
            while ((c_alterar = getchar()) != '\n' && c_alterar != EOF) {}

            for(i = 0; i < m; i++) {
                if(strcmp((*produtos_alterar+i)->dados_produto.nome, buscar_alterar) == 0) {
                    count_alterar++;
                    strcpy(buscar_alterar, (*produtos_alterar+i)->dados_produto.nome);
                    find_alterar = i;
                }
            }

            find_verificar(*produtos_alterar, &confirm_alterar, count_alterar);

            if(confirm_alterar == 0) {
                printf("Digite o novo local do produto: \n");
                fgets(
                    (*produtos_alterar+find_alterar)->dados_loja.local, 
                    sizeof(*produtos_alterar)->dados_loja.local, 
                    stdin
                );
                (*produtos_alterar+find_alterar)->dados_loja.local[strcspn((*produtos_alterar+find_alterar)->dados_loja.local, "\n")] = '\0';
            }
            break;
            
        }
}

void print_tudo(Produto *produtos_print, int p) { 
        printf("Nome: %s.\n", (produtos_print+p)->dados_produto.nome);
        printf("Categoria: %s.\n", (produtos_print+p)->dados_loja.categoria);
        printf("Descricao: %s.\n", (produtos_print+p)->dados_produto.descricao);
        printf("Estoque: %d.\n", (produtos_print+p)->dados_loja.estoque);
        printf("Marca: %s.\n", (produtos_print+p)->dados_produto.marca);
        printf("Local: %s.\n", (produtos_print+p)->dados_loja.local);
}

void find_verificar(Produto *produto_verificar, int *confirm_verificar, int count_verificar) {
    if (count_verificar == 1) {
        printf("Produto encontrado.\n");
        *confirm_verificar = 0;
    }
    if(count_verificar > 1) {
        printf("Mais que um produto com este nome.\n");
        *confirm_verificar = 1;
    }
    if(count_verificar == 0) {
        printf("Nenhum produto encontrado.\n");
        *confirm_verificar = 1;
    }
}

void salvar(Produto *produto_salvar, int *s) {
    FILE *arquivo = fopen("arquivo.dat", "wb");
    if(arquivo == NULL) {
        printf("Falha.\n");
        return;
    }
    fseek(arquivo, 0, SEEK_SET);

    fwrite(s, sizeof(int), 1, arquivo);
    fwrite(produto_salvar, sizeof(Produto), *s, arquivo);

    printf("Salvamento realizado com sucesso.\n");
    fclose(arquivo);
}

void recuperar(Produto **produto_recuperar, int *r) {
    FILE *arquivo = fopen("arquivo.dat", "rb");
    if(arquivo == NULL) {
        printf("Falha.\n");
        return;    
    }
    fseek(arquivo, 0, SEEK_END);
    long tamanho_recuperar = ftell(arquivo);

    fseek(arquivo, 0, SEEK_SET);
    fread(r, sizeof(int), 1, arquivo);


    if(tamanho_recuperar != -1L) {
        printf("Foram detectados %ld bytes de memoria.\n", tamanho_recuperar);
        printf("Isso equivale a %d produtos.\n", tamanho_recuperar/sizeof(Produto));
    }


    Produto *temp_recuperar; 
    temp_recuperar = malloc((size_t) (*r) * sizeof(Produto));


    if (temp_recuperar == NULL && *r > 0) {
        printf("Erro na alocacao de memoria.\n");
        return;
    }

    *produto_recuperar = temp_recuperar;

    printf("Ta quase la...");

    fread(*produto_recuperar, sizeof(Produto), *r, arquivo);

    printf("Salvamento recuperado com sucesso.\n");
    fclose(arquivo);
}