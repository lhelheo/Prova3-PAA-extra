#include <stdio.h>
#include <stdbool.h>

#define N 9

typedef struct {
    int linha;
    int coluna;
} Posicao;

typedef struct {
    Posicao posicoes[3];
    int somaEsperada;
    int somaAtual;
} Dica;

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

bool VerificaSoma(int tabuleiro[N][N], Dica dicas[], int tamanhoDicas) {
    for (int d = 0; d < tamanhoDicas; d++) {
        int soma = 0;
        for (int p = 0; p < 3; p++) { 
            soma += tabuleiro[dicas[d].posicoes[p].linha][dicas[d].posicoes[p].coluna];
        }
        if (soma > dicas[d].somaEsperada) {
            return false; 
        }
    }
    return true; 
}


bool ResolveSudoku(int tabuleiro[N][N], Dica dicas[], int tamanhoDicas) {
    int linha, coluna;
    if (!EncontraProximaCelulaVazia(tabuleiro, &linha, &coluna)) {
        return VerificaSoma(tabuleiro, dicas, tamanhoDicas); 
    }
    for (int num = 1; num <= N; num++) {
        if (EhValido(tabuleiro, linha, coluna, num)) {
            tabuleiro[linha][coluna] = num;
            if (VerificaSoma(tabuleiro, dicas, tamanhoDicas)) {
                if (ResolveSudoku(tabuleiro, dicas, tamanhoDicas)) {
                    return true;
                }
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
   Dica dicas[] = {
    {{{0, 0}, {0, 1}, {1, 1}}, 18},
};

    if (ResolveSudoku(tabuleiro, dicas, sizeof(dicas)/sizeof(dicas[0]))) {
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