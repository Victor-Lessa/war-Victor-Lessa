#include <stdio.h>
#include <string.h>

// Definição da estrutura Territorio
// Esta struct agrupa os dados relacionados a um território: nome, cor do exército e número de tropas
struct Territorio {
    char nome[30];   // Nome do território
    char cor[10];    // Cor do exército
    int tropas;      // Quantidade de tropas
};

int main() {
    // Declaração de um vetor de 5 elementos do tipo Territorio
    struct Territorio territorios[5];

    // Laço para entrada de dados dos 5 territórios
    for (int i = 0; i < 5; i++) {
        printf("Cadastro do território %d:\n", i + 1);

        // Entrada do nome do território
        printf("Digite o nome do território: ");
        scanf(" %[^\n]", territorios[i].nome); // Lê até a quebra de linha, permitindo nomes com espaços

        // Entrada da cor do exército
        printf("Digite a cor do exército: ");
        scanf(" %s", territorios[i].cor); // Lê uma palavra (sem espaços)

        // Entrada da quantidade de tropas
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("\n"); // Espaço entre cadastros
    }

    // Exibição dos dados cadastrados
    printf("=== Dados dos Territórios Cadastrados ===\n");
    for (int i = 0; i < 5; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exército: %s\n", territorios[i].cor);
        printf("Quantidade de Tropas: %d\n", territorios[i].tropas);
        printf("-----------------------------\n");
    }

    return 0;
}
