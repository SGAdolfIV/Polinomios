#include "nodo.h"
#include <string.h> // Necesario para memcpy

Nodo *nodo_crear(void *info, size_t size) {
    // 1. Reservamos memoria para la estructura del Nodo
    Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
    if (nuevo == NULL) return NULL;

    // 2. Reservamos memoria para la información genérica
    nuevo->info = malloc(size);
    if (nuevo->info == NULL) {
        free(nuevo); 
        return NULL;
    }

    // 3. Copiamos los datos al nuevo espacio de memoria
    memcpy(nuevo->info, info, size);

    // 4. Inicializamos los punteros de enlace a NULL
    nuevo->sig = NULL;
    nuevo->ant = NULL;

    return nuevo;
}

void nodo_eliminar(Nodo *nodo) {
    if (nodo != NULL) {
        if (nodo->info != NULL) {
            free(nodo->info); 
        }
        free(nodo); 
    }
}

bool nodo_actualizar(Nodo *nodo, void *info, size_t size) {
    if (nodo == NULL || info == NULL) return false;

    // Intentamos redimensionar la memoria del dato existente
    void *temp = realloc(nodo->info, size);
    
    if (temp == NULL) {
        return false; // Falló la asignación, el dato original sigue intacto
    }

    nodo->info = temp;
    memcpy(nodo->info, info, size);
    
    return true; // Retornamos true para indicar éxito
}