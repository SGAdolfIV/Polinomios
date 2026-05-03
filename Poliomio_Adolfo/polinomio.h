//polinomio.h
#ifndef __POLINOMIO_H__
#define __POLINOMIO_H__

#include "lista_ligada.h"

// Definición del término según el diseño del TAD
typedef struct {
    float coeficiente;
    int exponente;
} Termino;

// Definición de tipo para mayor claridad
typedef DLista Polinomio;

// Operaciones de gestión
Polinomio* poli_crear();
bool poli_insertar_termino(Polinomio *p, float coef, int exp);
void poli_mostrar(Polinomio *p);
void poli_destruir(Polinomio *p);

// Operaciones algebraicas
Polinomio* poli_sumar(Polinomio *p1, Polinomio *p2);
Polinomio* poli_restar(Polinomio *p1, Polinomio *p2);
Polinomio* poli_multiplicar(Polinomio *p1, Polinomio *p2);
float poli_evaluar(Polinomio *p, float x);

#endif