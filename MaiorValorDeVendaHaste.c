#include <stdio.h>
#include <stdlib.h>

int* MaiorValorDeVendaHaste(int p[], int n) {
    int* V = (int*)malloc((n + 1) * sizeof(int)); 
    int* C = (int*)malloc((n + 1) * sizeof(int)); 

    V[0] = 0;
    for (int i = 0; i <= n; i++) {
        C[i] = 0;
    }

    for (int i = 1; i <= n; i++) {
        int maior_valor = -1; 
        for (int j = 1; j <= i; j++) {
            int valor_atual = p[j] + V[i - j];
            if (valor_atual > maior_valor) {
                maior_valor = valor_atual;
                C[i] = j; 
            }
        }
        V[i] = maior_valor;
    }

    int* resultado = (int*)malloc(2 * sizeof(int)); 
    resultado[0] = V[n];
    resultado[1] = C[n];
    return resultado;
}

int main() {
    int p[] = {0, 1, 5, 8, 9, 10, 17, 17, 20}; 
    int n = sizeof(p) / sizeof(p[0]) - 1; 

    int* resultado = MaiorValorDeVendaHaste(p, n);

    printf("Maior valor de venda: %d\n", resultado[0]);
    printf("Ponto de corte otimo: %d\n", resultado[1]);
    free(resultado);

    return 0;
}