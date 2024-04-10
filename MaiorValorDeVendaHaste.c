#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) { return (a > b)? a : b;}

int MaiorValorDeVendaHaste(int p[], int n) {
    int V[n+1];
    V[0] = 0;

    for (int i = 1; i <= n; i++) {
        int maior_valor = -1; 

        if (i % 2 == 0) { // Se o tamanho é par, só podemos dividir no meio
            maior_valor = max(maior_valor, V[i/2] + V[i/2]);
        } else { // Se o tamanho é ímpar, podemos dividir em k e k+1
            int k = i / 2;
            maior_valor = max(maior_valor, p[k] + p[k + 1]);
        }

        V[i] = maior_valor;
    }

    return V[n];
}

int main() {
    int p[] = {0, 1, 5, 8, 9, 10, 17, 17, 20}; 
    int n = sizeof(p) / sizeof(p[0]) - 1; 

    printf("Maior valor de venda: %d\n", MaiorValorDeVendaHaste(p, n));

    return 0;
}
