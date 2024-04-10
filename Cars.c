#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int inicio; 
    int fim;    
} Disponibilidade;

int compararDisponibilidade(Disponibilidade dispA, Disponibilidade dispB) {
    if (dispA.fim != dispB.fim)
        return dispA.fim - dispB.fim;
    return dispA.inicio - dispB.inicio;
}

void ordenarPorInsercao(Disponibilidade disponibilidades[], int n) {
    int i, j;
    Disponibilidade chave;
    for (i = 1; i < n; i++) {
        chave = disponibilidades[i];
        j = i - 1;

        while (j >= 0 && compararDisponibilidade(disponibilidades[j], chave) > 0) {
            disponibilidades[j + 1] = disponibilidades[j];
            j = j - 1;
        }
        disponibilidades[j + 1] = chave;
    }
}

int alocarMecanicos(Disponibilidade disponibilidades[], int n) {
    ordenarPorInsercao(disponibilidades, n);

    int mecanicosNecessarios = n; 
    int considerado[n]; 

    for (int i = 0; i < n; i++) {
        considerado[i] = 0; 
    }

    for (int i = 0; i < n; i++) {
        if (!considerado[i]) { 
            for (int j = i + 1; j < n; j++) {
                if (disponibilidades[j].inicio >= disponibilidades[i].inicio && disponibilidades[j].fim <= disponibilidades[i].fim) {
                    mecanicosNecessarios--; 
                    considerado[j] = 1; 
                }
                else if (disponibilidades[j].inicio > disponibilidades[i].fim && disponibilidades[j].fim > disponibilidades[i].fim) {
                    break;
                }
            }
        }
    }

    return mecanicosNecessarios;
}

int main() {
    int s[] = {1, 2, 3, 6, 7}; 
    int f[] = {7, 8, 9, 8, 9}; 
    int n = sizeof(s) / sizeof(s[0]); 

    Disponibilidade disponibilidades[n];
    for (int i = 0; i < n; i++) {
        disponibilidades[i].inicio = s[i];
        disponibilidades[i].fim = f[i];
    }

    int mecanicos = alocarMecanicos(disponibilidades, n);
    printf("Numero de mecanicos necessarios: %d\n", mecanicos);

    return 0;
}
