#include <stdio.h>
#include <stdlib.h>

// Função para calcular o maior valor de venda de uma haste
int* MaiorValorDeVendaHaste(int p[], int n) {
    // Aloca memória para as tabelas V e C
    int* V = (int*)malloc((n + 1) * sizeof(int)); // Correção: Casting do retorno de malloc
    int* C = (int*)malloc((n + 1) * sizeof(int)); // Correção: Casting do retorno de malloc

    // Inicializa a tabela V para uma haste de tamanho zero
    V[0] = 0;

    // Inicializa a tabela de cortes C
    for (int i = 0; i <= n; i++) {
        C[i] = 0;
    }

    // Calcula o maior valor de venda para cada tamanho de haste
    for (int i = 1; i <= n; i++) {
        int maior_valor = -1; // Correção: Usar INT_MIN ao invés de um valor arbitrário
        for (int j = 1; j <= i; j++) {
            int valor_atual = p[j] + V[i - j];
            if (valor_atual > maior_valor) {
                maior_valor = valor_atual;
                C[i] = j; // Atualiza o ponto de corte ótimo para uma haste de tamanho i
            }
        }
        V[i] = maior_valor;
    }

    // Cria um array para armazenar o resultado final
    int* resultado = (int*)malloc(2 * sizeof(int)); // Correção: Casting do retorno de malloc
    resultado[0] = V[n];
    resultado[1] = C[n];

    // Libera a memória alocada para as tabelas V e C
    // Comentário: Não deve liberar a memória de V e C aqui, pois precisamos deles no resultado

    return resultado;
}

int main() {
    int p[] = {0, 1, 5, 8, 9, 10, 17, 17, 20}; // Preços dos pedaços de haste
    int n = sizeof(p) / sizeof(p[0]) - 1; // Tamanho da haste

    // Chama a função para calcular o maior valor de venda e o ponto de corte ótimo
    int* resultado = MaiorValorDeVendaHaste(p, n);

    // Imprime o resultado
    printf("Maior valor de venda: %d\n", resultado[0]);
    printf("Ponto de corte otimo: %d\n", resultado[1]);

    // Libera a memória alocada para o resultado
    free(resultado);

    return 0;
}