#ifndef NODO_H
#define NODO_H


#include "../cancion/cancion.h"

class Nodo {
    public:
        Cancion dato;
        Nodo* siguiente;
        Nodo* anterior;

        Nodo(const Cancion& valor);
};



#endif