#include <stdlib.h>
#include <stdio.h>
#define MAX 50

struct produto {
    int id;
    int estoque;
    char nome[MAX];
    float preco;
};

struct usuario {
    char username[MAX];
    int senha;
};

int main() {

    printf("Hello, Giovanni!");

    return 0;
}