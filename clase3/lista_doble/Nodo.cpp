

#include "Nodo.h"


Nodo::Nodo(const Cancion& valor) {
    dato = valor;
    siguiente = nullptr;
    anterior = nullptr;
}

