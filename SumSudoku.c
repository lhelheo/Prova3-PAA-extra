#include <stdio.h>
#include <stdbool.h>

#define N 9

// Verifica se um número pode ser colocado na célula [linha][coluna]
bool EhValido(int tabuleiro[N][N], int linha, int coluna, int numero) {
    for (int i = 0; i < N; i++) {
        if (tabuleiro[linha][i] == numero || tabuleiro[i][coluna] == numero) {
            return false;
        }
    }
    int inicioLinha = linha - linha % 3, inicioColuna = coluna - coluna % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tabuleiro[i + inicioLinha][j + inicioColuna] == numero) {
                return false;
            }
        }
    }
    return true;
}

bool EncontraProximaCelulaVazia(int tabuleiro[N][N], int *linha, int *coluna) {
    for (*linha = 0; *linha < N; (*linha)++) {
        for (*coluna = 0; *coluna < N; (*coluna)++) {
            if (tabuleiro[*linha][*coluna] == 0) {
                return true;
            }
        }
    }
    return false;
}

bool VerificaSoma(int tabuleiro[N][N], int dicas[N]) {
    for (int i = 0; i < N; i++) { // Itera sobre todas as linhas do tabuleiro
        int somaLinha = 0; // Inicializa a soma da linha atual
        for (int j = 0; j < N; j++) { // Itera sobre todas as colunas da linha atual
            somaLinha += tabuleiro[i][j]; // Soma os valores da linha
        }
        if (somaLinha != dicas[i]) { // Compara a soma da linha com a dica correspondente
            return false; // Se a soma da linha não respeitar a dica, retorna falso
        }
    }
    return true; // Se todas as linhas respeitarem as dicas, retorna verdadeiro
}

bool ResolveSudoku(int tabuleiro[N][N], int dicas[N]) {
    int linha, coluna;
    if (!EncontraProximaCelulaVazia(tabuleiro, &linha, &coluna)) {
        return VerificaSoma(tabuleiro, dicas); // Verifica se o estado final do tabuleiro respeita as dicas de soma
    }
    for (int num = 1; num <= N; num++) {
        if (EhValido(tabuleiro, linha, coluna, num)) {
            tabuleiro[linha][coluna] = num;
            if (ResolveSudoku(tabuleiro, dicas)) {
                return true;
            }
            tabuleiro[linha][coluna] = 0;
        }
    }
    return false;
}

int main() {
    int tabuleiro[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };
    int dicas[] = {20, 15, 25, 20, 30, 20, 15, 25, 20};

    if (ResolveSudoku(tabuleiro, dicas)) {
        // Imprime o tabuleiro resolvido
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", tabuleiro[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("Nao foi possivel resolver o Sudoku.\n");
    }
    return 0;
}
