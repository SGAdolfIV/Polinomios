//lista_ligada.h
//lista_ligada.h
#ifndef __LISTA_LIGADA_H__
#define __LISTA_LIGADA_H__

#include "nodo.h"

typedef struct DLista DLista;

struct DLista{
    Nodo* head;
    Nodo* tail;
};

DLista* lista_crear();
bool lista_es_vacia(DLista *l);

bool lista_insertar_vacia(DLista *l, void *info, size_t size);
bool lista_insertar_inicio(DLista *l, void *info, size_t size);
bool lista_insertar_fin(DLista *l, void *info, size_t size);
bool lista_insertar_x_pos(DLista *l,int pos, void *info, size_t size);

int lista_num_nodos(DLista *l);
#endif