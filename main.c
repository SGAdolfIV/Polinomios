#include <stdio.h>
#include <stdlib.h>
#include "polinomio.h"

int main() {
    printf("--- Pruebas del TAD Polinomio (Lista Doblemente Ligada) ---\n\n");

    // 1. Crear Polinomio 1: 3x^2 + 2x + 1
    Polinomio* p1 = crear_polinomio();
    insertar_termino(p1, 3.0, 2);
    insertar_termino(p1, 2.0, 1);
    insertar_termino(p1, 1.0, 0);
    printf("P1: ");
    mostrar_polinomio(p1);

    // 2. Crear Polinomio 2: x^2 + 4 (Usando inserción desordenada para probar el TAD)
    Polinomio* p2 = crear_polinomio();
    insertar_termino(p2, 4.0, 0); // Insertamos primero el grado menor
    insertar_termino(p2, 1.0, 2); // El TAD debe ordenarlo al inicio
    printf("P2: ");
    mostrar_polinomio(p2);

    // 3. Probar Simplificación: Insertar 5x^2 a P1 (Resultado esperado: 8x^2 + 2x + 1)
    printf("\nInsertando 5x^2 en P1 para simplificar...");
    insertar_termino(p1, 5.0, 2);
    printf("\nP1 simplificado: ");
    mostrar_polinomio(p1);

    // 4. Operación de Suma: P1 + P2
    printf("\n--- Operacion: Suma (P1 + P2) ---");
    Polinomio* suma = sumar_polinomios(p1, p2);
    printf("\nResultado Suma: ");
    mostrar_polinomio(suma);

    // 5. Operación de Multiplicacion (Ejemplo simple)
    printf("\n--- Operacion: Multiplicacion ---");
    Polinomio* p3 = crear_polinomio();
    insertar_termino(p3, 2.0, 1); // 2x
    Polinomio* p4 = crear_polinomio();
    insertar_termino(p4, 3.0, 1); // 3x
    insertar_termino(p4, 1.0, 0); // +1 -> (2x)(3x + 1) = 6x^2 + 2x
    
    Polinomio* prod = multiplicar_polinomios(p3, p4);
    printf("\n(2x^1) * (3x^1 + 1x^0) = ");
    mostrar_polinomio(prod);

    // 6. Evaluación: Evaluar P1 cuando x = 2
    float x_val = 2.0;
    float resultado_eval = evaluar_polinomio(p1, x_val);
    printf("\n--- Evaluacion ---");
    printf("\nEvaluar P1 en x = %.2f: %.2f\n", x_val, resultado_eval);

    // 7. Liberación de memoria
    eliminar_polinomio(p1);
    eliminar_polinomio(p2);
    eliminar_polinomio(p3);
    eliminar_polinomio(p4);
    eliminar_polinomio(suma);
    eliminar_polinomio(prod);

    printf("\nMemoria liberada. Programa finalizado con exito.\n");

    return 0;
}