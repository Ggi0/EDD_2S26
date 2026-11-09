/**
 

Implementacion de la lista enlazada de aristas 


*/
#include "ListaAristas.h"

ListaAristas::ListaAristas() : cabeza(nullptr), cantidad(0) {}

ListaAristas::~ListaAristas() {
    vaciar();
}

bool ListaAristas::agregar(Vertice* destino, int peso) {
    // No permitimos aristas repetidas hacia el mismo destino.
    if (buscar(destino) != nullptr) {
        return false;
    }

    Arista* nueva = new Arista(destino, peso);

    if (cabeza == nullptr) {
        // Lista vacia: la nueva arista es la cabeza.
        cabeza = nueva;
    } else {
        // Recorremos hasta el ultimo nodo y enlazamos la nueva al final.
        Arista* actual = cabeza;
        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        actual->siguiente = nueva;
    }

    cantidad++;
    return true;
}

Arista* ListaAristas::buscar(Vertice* destino) const {
    // Recorrido lineal
    for (Arista* actual = cabeza; actual != nullptr; actual = actual->siguiente) {
        if (actual->destino == destino) {
            return actual;
        }
    }
    return nullptr;
}

bool ListaAristas::eliminar(Vertice* destino) {
    Arista* anterior = nullptr;
    Arista* actual = cabeza;

    // Buscamos el nodo, recordando cual es el anterior para poder "saltarlo".
    while (actual != nullptr && actual->destino != destino) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == nullptr) {
        return false;  // No existia
    }

    if (anterior == nullptr) {
        // Era la cabeza: la cabeza ahora es el siguiente.
        cabeza = actual->siguiente;
    } else {
        // Estaba en medio o al final: el anterior se salta al actual.
        anterior->siguiente = actual->siguiente;
    }

    delete actual;
    cantidad--;
    return true;
}

void ListaAristas::vaciar() {
    while (cabeza != nullptr) {
        Arista* siguiente = cabeza->siguiente;
        delete cabeza;
        cabeza = siguiente;
    }
    cantidad = 0;
}

Arista* ListaAristas::primero() const {
    return cabeza;
}

int ListaAristas::obtenerCantidad() const {
    return cantidad;
}

bool ListaAristas::estaVacia() const {
    return cabeza == nullptr;
}
