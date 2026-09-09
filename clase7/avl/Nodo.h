#ifndef NODO_H
#define NODO_H


struct Nodo {
    int dato;
    int altura;     
    Nodo* izquierdo;
    Nodo* derecho;

    Nodo(int valor);
};

#endif