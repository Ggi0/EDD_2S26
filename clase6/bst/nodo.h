#ifndef NODO_H
#define NODO_H

class Nodo {
public:
    int dato; // 1,2,34,
    Nodo* izquierdo;
    Nodo* derecho;

    // Constructor: crea un nodo hoja (sin hijos) con el valor dado
    Nodo(int valor);
};

#endif