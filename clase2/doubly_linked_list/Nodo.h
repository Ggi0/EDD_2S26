#ifndef NODO_H
#define NODO_H


#include "../pelicula/pelicula.h"

class Nodo {
    public:
        Pelicula dato;
        Nodo* siguiente;
        Nodo* anterior;

        Nodo(const Pelicula& valor);
};



#endif