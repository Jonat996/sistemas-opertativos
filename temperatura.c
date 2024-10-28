#include <stdio.h>
#include <stdlib.h>

int main() {
    // Declaración de variables
    int num_temperaturas = 20;
    float *temperaturas;

    // Reserva de memoria dinámica
    temperaturas = (float *)malloc(num_temperaturas * sizeof(float));
    if (temperaturas == NULL) {
        printf("Error al asignar memoria.\n");
        return 1; // Finaliza si no hay suficiente memoria
    }

    // Solicitar al usuario que ingrese las temperaturas
    printf("Ingrese 20 temperaturas del día:\n");
    for (int i = 0; i < num_temperaturas; i++) {
        printf("Temperatura %d: ", i + 1);
        scanf("%f", &temperaturas[i]);
    }

    // Mostrar las temperaturas ingresadas
    printf("\nLas temperaturas ingresadas son:\n");
    for (int i = 0; i < num_temperaturas; i++) {
        printf("Temperatura %d: %.2f\n", i + 1, temperaturas[i]);
    }

    // Liberar la memoria asignada
    free(temperaturas);

    return 0;
}
