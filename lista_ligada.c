//lista_ligada.c
#include "lista_ligada.h"

DLista* lista_crear() {
    DLista* l = (DLista*)malloc(sizeof(DLista));
    if (l != NULL) {
        l->head = NULL;
        l->tail = NULL;
    }
    return l;
}

bool lista_es_vacia(DLista *l) {
    if (l == NULL || l->head == NULL) {
        return true;
    }
    return false;
}

bool lista_insertar_vacia(DLista *l, void *info, size_t size) {
    if (l == NULL || !lista_es_vacia(l)) return false;

    Nodo *nuevo = nodo_crear(info, size);
    if (nuevo == NULL) return false;

    // En una lista de un solo elemento, head y tail apuntan al mismo nodo
    l->head = nuevo;
    l->tail = nuevo;
    return true;
}

bool lista_insertar_inicio(DLista *l, void *info, size_t size) {
    if (l == NULL) return false;
    if (lista_es_vacia(l)) return lista_insertar_vacia(l, info, size);

    Nodo *nuevo = nodo_crear(info, size);
    if (nuevo == NULL) return false;

    // Conectamos el nuevo nodo al principio
    nuevo->sig = l->head;
    l->head->ant = nuevo;
    
    // Actualizamos la cabeza de la lista
    l->head = nuevo;
    
    return true;
}

bool lista_insertar_fin(DLista *l, void *info, size_t size) {
    if (l == NULL) return false;
    if (lista_es_vacia(l)) return lista_insertar_vacia(l, info, size);

    Nodo *nuevo = nodo_crear(info, size);
    if (nuevo == NULL) return false;

    // Conectamos el nuevo nodo al final
    nuevo->ant = l->tail;
    l->tail->sig = nuevo;
    
    // Actualizamos la cola de la lista
    l->tail = nuevo;

    return true;
}

bool lista_insertar_x_pos(DLista *l, int pos, void *info, size_t size) {
    if (l == NULL || pos < 0) return false;

    // Si la posición es 0, usamos la función de inicio
    if (pos == 0) return lista_insertar_inicio(l, info, size);

    Nodo *tmp = l->head;
    int i = 0;

    // Recorremos hasta encontrar la posición o el final de la lista
    while (tmp != NULL && i < pos) {
        tmp = tmp->sig;
        i++;
    }

    // Si tmp es NULL, verificamos si queremos insertar justo al final
    if (tmp == NULL) {
        if (i == pos) return lista_insertar_fin(l, info, size);
        return false; // Posición fuera de rango
    }

    // CORRECCIÓN: nombre de función corregido a nodo_crear
    Nodo *nuevo = nodo_crear(info, size);
    if (nuevo == NULL) return false;

    // Reconfiguración de punteros para insertar entre nodos
    nuevo->sig = tmp;
    nuevo->ant = tmp->ant;

    if (tmp->ant != NULL) {
        tmp->ant->sig = nuevo;
    }
    
    tmp->ant = nuevo;

    return true;
}

int lista_num_nodos(DLista *l) {
    if (l == NULL) return 0;
    int i = 0;
    // Recorrido lineal para contar elementos
    for (Nodo *tmp = l->head; tmp != NULL; tmp = tmp->sig, i++);
    return i;
}