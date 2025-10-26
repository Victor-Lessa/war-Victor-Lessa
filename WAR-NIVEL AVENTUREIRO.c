#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da estrutura Territorio
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para cadastrar os territórios
void cadastrarTerritorios(Territorio* mapa, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("Cadastro do território %d:\n", i + 1);
        printf("Nome: ");
        scanf(" %[^\n]", mapa[i].nome);
        printf("Cor do exército: ");
        scanf(" %s", mapa[i].cor);
        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
        printf("\n");
    }
}

// Função para exibir os dados dos territórios
void exibirTerritorios(Territorio* mapa, int quantidade) {
    printf("=== Territórios ===\n");
    for (int i = 0; i < quantidade; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
        printf("-------------------\n");
    }
}

// Função que simula o ataque entre dois territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Erro: não é permitido atacar um território da mesma cor.\n");
        return;
    }

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("Rolagem de dados:\n");
    printf("Atacante (%s): %d\n", atacante->nome, dadoAtacante);
    printf("Defensor (%s): %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("Resultado: atacante venceu!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
    } else {
        printf("Resultado: defensor resistiu ao ataque.\n");
        if (atacante->tropas > 0) {
            atacante->tropas -= 1;
        }
    }
}

// Função para liberar a memória alocada
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

int main() {
    srand(time(NULL)); // Inicializa a semente para números aleatórios

    int quantidade;
    printf("Digite o número de territórios a serem cadastrados: ");
    scanf("%d", &quantidade);

    // Alocação dinâmica de memória para os territórios
    Territorio* mapa = (Territorio*)calloc(quantidade, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    cadastrarTerritorios(mapa, quantidade);
    exibirTerritorios(mapa, quantidade);

    // Simulação de ataque
    int iAtacante, iDefensor;
    printf("Escolha o número do território atacante (1 a %d): ", quantidade);
    scanf("%d", &iAtacante);
    printf("Escolha o número do território defensor (1 a %d): ", quantidade);
    scanf("%d", &iDefensor);

    if (iAtacante < 1 || iAtacante > quantidade || iDefensor < 1 || iDefensor > quantidade) {
        printf("Erro: seleção inválida de territórios.\n");
    } else {
        atacar(&mapa[iAtacante - 1], &mapa[iDefensor - 1]);
        exibirTerritorios(mapa, quantidade);
    }

    liberarMemoria(mapa);
    return 0;
}
