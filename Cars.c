#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar um carro com o tempo de início e fim de disponibilidade
typedef struct {
    int s; // Tempo de início de disponibilidade
    int f; // Tempo de fim de disponibilidade
} Carro;

// Função para comparar dois carros com base no tempo de término de disponibilidade
int CompararCarros(const void *a, const void *b) {
    Carro *carro1 = (Carro*)a;
    Carro *carro2 = (Carro*)b;
    return carro1->f - carro2->f;
}

// Função para ordenar os carros com base no tempo de término de disponibilidade
void OrdenarCarros(Carro carros[], int n) {
    qsort(carros, n, sizeof(Carro), CompararCarros);
}

// Função para alocar mecânicos para os carros
int AlocaMecanicos(int s[], int f[], int n) {
    // Criar um array de carros com os tempos de início e fim de disponibilidade
    Carro carros[n];
    for (int i = 0; i < n; i++) {
        carros[i].s = s[i];
        carros[i].f = f[i];
    }

    // Ordenar os carros com base no tempo de término de disponibilidade
    OrdenarCarros(carros, n);

    // Alocar mecânicos para os carros
    int mecanicos_utilizados = 1; // Inicialmente, pelo menos um mecânico é necessário
    int tempo_atual = carros[0].f; // Tempo atual é o fim da disponibilidade do primeiro carro

    for (int i = 1; i < n; i++) {
        if (carros[i].s >= tempo_atual) { // Verifica se o próximo carro não entra em conflito com o atual
            mecanicos_utilizados++; // Aumenta o número de mecânicos utilizados
            tempo_atual = carros[i].f; // Atualiza o tempo atual para o fim da disponibilidade do próximo carro
        }
    }

    return mecanicos_utilizados;
}

int main() {
    // Exemplo de disponibilidade de carros
    int s[] = {1, 3, 4, 6};
    int f[] = {5, 5, 7, 8};
    int n = sizeof(s) / sizeof(s[0]);

    // Chama a função para alocar mecânicos para os carros
    int mecanicos = AlocaMecanicos(s, f, n);

    // Imprime o número de mecânicos utilizados
    printf("Numero de mecanicos utilizados: %d\n", mecanicos);

    return 0;
}