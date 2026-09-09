#include "Nodo.h"

Nodo::Nodo(int valor) {
    dato = valor;

    // Un nodo recién creado es siempre una hoja: no tiene hijos,
    // así que su altura es 0 
    //                          "hoja = altura 0",
    //                          "árbol vacío = altura -1"
    altura = 0;

    izquierdo = nullptr;
    derecho = nullptr;
}