#ifndef NODO_CIRCULAR_H
#define NODO_CIRCULAR_H


#include "../cantante/cantante.h"

class NodoCircular {
public:
    Cantante dato;
    NodoCircular* siguiente;

    NodoCircular(const Cantante& valor);
};

#endif