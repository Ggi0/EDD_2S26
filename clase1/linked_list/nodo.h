

#ifndef NODO_H
#define NODO_H

#include <iostream>

class Nodo {

    public:
        // atributos
        int dato;
        Nodo* siguiente;

        // constructor
        Nodo(int valor);

        void imprimir();
};



#endif // NODO_H