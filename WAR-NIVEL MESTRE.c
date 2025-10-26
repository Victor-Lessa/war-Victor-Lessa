#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura que representa um território
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

// Função para exibir os territórios
void exibirMapa(Territorio* mapa, int quantidade) {
    printf("=== Territórios ===\n");
    for (int i = 0; i < quantidade; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
        printf("-------------------\n");
    }
}

// Função que simula um ataque entre dois territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Erro: não é permitido atacar um território da mesma cor.\n");
        return;
    }

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("Dados rolados - Atacante: %d | Defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("O atacante venceu!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
    } else {
        printf("O defensor resistiu ao ataque.\n");
        if (atacante->tropas > 0) atacante->tropas -= 1;
    }
}

// Função que atribui uma missão aleatória ao jogador
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]);
}

// Função que exibe a missão do jogador
void exibirMissao(char* missao) {
    printf("Sua missão: %s\n", missao);
}

// Função que verifica se a missão foi cumprida (lógica simplificada)
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    if (strcmp(missao, "Conquistar 3 territórios seguidos") == 0) {
        int cont = 0;
        for (int i = 1; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, mapa[i - 1].cor) == 0) {
                cont++;
                if (cont >= 2) return 1;
            } else {
                cont = 0;
            }
        }
    } else if (strcmp(missao, "Eliminar todas as tropas da cor vermelha") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelha") == 0 && mapa[i].tropas > 0) {
                return 0;
            }
        }
        return 1;
    }
    // Outras missões podem ser adicionadas aqui
    return 0;
}

// Função que libera memória alocada
void liberarMemoria(Territorio* mapa, char* missaoJogador) {
    free(mapa);
    free(missaoJogador);
}

int main() {
    srand(time(NULL));

    // Vetor de missões disponíveis
    char* missoes[] = {
        "Conquistar 3 territórios seguidos",
        "Eliminar todas as tropas da cor vermelha",
        "Controlar ao menos 4 territórios",
        "Ter mais de 20 tropas no total",
        "Conquistar um território com nome iniciado por 'A'"
    };
    int totalMissoes = 5;

    // Alocação de missão do jogador
    char* missaoJogador = (char*)malloc(100 * sizeof(char));
    atribuirMissao(missaoJogador, missoes, totalMissoes);
    exibirMissao(missaoJogador);

    // Cadastro de territórios
    int quantidade;
    printf("Digite o número de territórios: ");
    scanf("%d", &quantidade);

    Territorio* mapa = (Territorio*)calloc(quantidade, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória para o mapa.\n");
        free(missaoJogador);
        return 1;
    }

    cadastrarTerritorios(mapa, quantidade);
    exibirMapa(mapa, quantidade);

    // Simulação de ataque
    int iAtacante, iDefensor;
    printf("Escolha o número do território atacante (1 a %d): ", quantidade);
    scanf("%d", &iAtacante);
    printf("Escolha o número do território defensor (1 a %d): ", quantidade);
    scanf("%d", &iDefensor);

    if (iAtacante >= 1 && iAtacante <= quantidade && iDefensor >= 1 && iDefensor <= quantidade) {
        atacar(&mapa[iAtacante - 1], &mapa[iDefensor - 1]);
        exibirMapa(mapa, quantidade);

        // Verificação de missão
        if (verificarMissao(missaoJogador, mapa, quantidade)) {
            printf("Parabéns! Você cumpriu sua missão: %s\n", missaoJogador);
        } else {
            printf("Missão ainda não cumprida.\n");
        }
    } else {
        printf("Seleção inválida de territórios.\n");
    }

    liberarMemoria(mapa, missaoJogador);
    return 0;
}
