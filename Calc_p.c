#include <stdio.h>
#include <stdlib.h>
#include "polinomio.h"

void menu() {
    printf("\n--- CALCULADORA DE POLINOMIOS ---\n");
    printf("1. Insertar termino en P1\n");
    printf("2. Insertar termino en P2\n");
    printf("3. Mostrar polinomios\n");
    printf("4. Sumar (P1 + P2)\n");
    printf("5. Multiplicar (P1 * P2)\n");
    printf("6. Evaluar P1 en un valor x\n");
    printf("7. Salir\n");
    printf("Seleccione una opcion: ");
}

int main() {
    Polinomio *p1 = poli_crear();
    Polinomio *p2 = poli_crear();
    int opcion, exp;
    float coef, x;

    do {
        menu();
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Ingrese coeficiente y exponente (ej: 3 2 para 3x^2): ");
                scanf("%f %d", &coef, &exp);
                poli_insertar_termino(p1, coef, exp);
                break;

            case 2:
                printf("Ingrese coeficiente y exponente: ");
                scanf("%f %d", &coef, &exp);
                poli_insertar_termino(p2, coef, exp);
                break;

            case 3:
                printf("\nP1: "); poli_mostrar(p1);
                printf("P2: "); poli_mostrar(p2);
                break;

            case 4:
                printf("\nResultado Suma: ");
                Polinomio *suma = poli_sumar(p1, p2);
                poli_mostrar(suma);
                poli_destruir(suma); // Liberar memoria temporal
                break;

            case 5:
                printf("\nResultado Multiplicacion: ");
                Polinomio *multi = poli_multiplicar(p1, p2);
                poli_mostrar(multi);
                poli_destruir(multi);
                break;

            case 6:
                printf("Ingrese valor de x: ");
                scanf("%f", &x);
                printf("Resultado de evaluar P1 en %g: %g\n", x, poli_evaluar(p1, x));
                break;

            case 7:
                printf("Saliendo...\n");
                break;

            default:
                printf("Opcion no valida.\n");
        }
    } while (opcion != 7);

    // Limpieza final de memoria
    poli_destruir(p1);
    poli_destruir(p2);

    return 0;
}