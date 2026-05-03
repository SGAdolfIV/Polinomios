//polinomio.c
#include "polinomio.h"
#include <math.h>
#include <stdio.h>

// --- GESTIÓN E INSERCIÓN ---

Polinomio* poli_crear() {
    return lista_crear();
}

// Implementa la regla fundamental: inserción ordenada y simplificación[cite: 1]
bool poli_insertar_termino(Polinomio *p, float coef, int exp) {
    if (p == NULL || coef == 0) return false;

    Termino nuevo_t = {coef, exp};
    
    if (lista_es_vacia(p)) {
        return lista_insertar_vacia(p, &nuevo_t, sizeof(Termino));
    }

    Nodo *actual = p->head;
    // Buscar posición para mantener orden descendente[cite: 1]
    while (actual != NULL && ((Termino*)actual->info)->exponente > exp) {
        actual = actual->sig;
    }

    // Caso: El exponente ya existe -> Simplificar[cite: 1]
    if (actual != NULL && ((Termino*)actual->info)->exponente == exp) {
        Termino *t_existente = (Termino*)actual->info;
        t_existente->coeficiente += coef;

        // Si el coeficiente es 0, eliminar término[cite: 1]
        if (t_existente->coeficiente == 0) {
            if (actual->ant) actual->ant->sig = actual->sig;
            else p->head = actual->sig;

            if (actual->sig) actual->sig->ant = actual->ant;
            else p->tail = actual->ant;

            nodo_eliminar(actual);
        }
        return true;
    }

    // Caso: Insertar nuevo nodo en la posición encontrada[cite: 1]
    if (actual == p->head) return lista_insertar_inicio(p, &nuevo_t, sizeof(Termino));
    if (actual == NULL) return lista_insertar_fin(p, &nuevo_t, sizeof(Termino));

    // Inserción intermedia
    Nodo *nuevo = nodo_crear(&nuevo_t, sizeof(Termino));
    if (!nuevo) return false;
    nuevo->sig = actual;
    nuevo->ant = actual->ant;
    actual->ant->sig = nuevo;
    actual->ant = nuevo;
    return true;
}

// --- OPERACIONES ALGEBRAICAS ---

Polinomio* poli_sumar(Polinomio *p1, Polinomio *p2) {
    Polinomio *res = poli_crear();
    for (Nodo *n = p1->head; n; n = n->sig) 
        poli_insertar_termino(res, ((Termino*)n->info)->coeficiente, ((Termino*)n->info)->exponente);
    for (Nodo *n = p2->head; n; n = n->sig) 
        poli_insertar_termino(res, ((Termino*)n->info)->coeficiente, ((Termino*)n->info)->exponente);
    return res;
}

Polinomio* poli_restar(Polinomio *p1, Polinomio *p2) {
    Polinomio *res = poli_crear();
    for (Nodo *n = p1->head; n; n = n->sig) 
        poli_insertar_termino(res, ((Termino*)n->info)->coeficiente, ((Termino*)n->info)->exponente);
    for (Nodo *n = p2->head; n; n = n->sig) 
        // Se inserta el coeficiente con signo opuesto[cite: 1]
        poli_insertar_termino(res, -((Termino*)n->info)->coeficiente, ((Termino*)n->info)->exponente);
    return res;
}

Polinomio* poli_multiplicar(Polinomio *p1, Polinomio *p2) {
    Polinomio *res = poli_crear();
    for (Nodo *n1 = p1->head; n1; n1 = n1->sig) {
        for (Nodo *n2 = p2->head; n2; n2 = n2->sig) {
            float c = ((Termino*)n1->info)->coeficiente * ((Termino*)n2->info)->coeficiente;
            int e = ((Termino*)n1->info)->exponente + ((Termino*)n2->info)->exponente;
            poli_insertar_termino(res, c, e);
        }
    }
    return res;
}

// --- SALIDA Y LIMPIEZA ---

void poli_mostrar(Polinomio *p) {
    if (!p || lista_es_vacia(p)) { printf("0\n"); return; }
    Nodo *n = p->head;
    bool primero = true;
    while (n) {
        Termino *t = (Termino*)n->info;
        if (!primero && t->coeficiente > 0) printf("+");
        if (t->coeficiente == -1 && t->exponente != 0) printf("-");
        else if (t->coeficiente != 1 || t->exponente == 0) printf("%g", t->coeficiente);
        if (t->exponente > 1) printf("x^%d", t->exponente);
        else if (t->exponente == 1) printf("x");
        primero = false;
        n = n->sig;
    }
    printf("\n");
}

void poli_destruir(Polinomio *p) {
    if (!p) return;
    Nodo *act = p->head;
    while (act) {
        Nodo *sig = act->sig;
        nodo_eliminar(act);
        act = sig;
    }
    free(p);
}