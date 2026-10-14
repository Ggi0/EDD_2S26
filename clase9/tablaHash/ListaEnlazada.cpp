#include "ListaEnlazada.h"
#include <iostream>
using namespace std;


ListaEnlazada::ListaEnlazada() : cabeza(nullptr), tamanio(0) {
}

ListaEnlazada::~ListaEnlazada() {
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        Nodo* siguienteTemp = actual->siguiente; 
        delete actual;         // liberamos el nodo actual
        actual = siguienteTemp;   
    }
    cabeza = nullptr;
}


// insertar(
void ListaEnlazada::insertar(const string& clave, const string& valor, int indexBucket) {
    // Si la cabeza NO es nullptr significa que el bucket ya tenía al menos un nodo antes de esta insercion
    // este nuevo nodo es consecuencia de una COLISION 
    bool esColision = (cabeza != nullptr);

    // Reservamos memoria dinamica para el nuevo nodo (por eso "new").
    Nodo* nuevo = new Nodo(clave, valor, indexBucket, esColision);

    nuevo->siguiente = cabeza;
    cabeza = nuevo;

    tamanio++;
}


// eliminar()
bool ListaEnlazada::eliminar(const string& clave) {
    Nodo* actual = cabeza;
    Nodo* anterior = nullptr;

    while (actual != nullptr) {
        if (actual->clave == clave) {
            // Caso 1: el nodo a eliminar ES la cabeza de la lista.
            if (anterior == nullptr) {
                cabeza = actual->siguiente;
            } else {
                // Caso 2: el nodo está en medio o al final de la lista. 
                // "saltamos" el nodo actual conectando anterior directo con lo que venía despues de actual.
                anterior->siguiente = actual->siguiente;
            }

            delete actual;  
            tamanio--;
            return true;
        }

        // Avanzamos un paso: el "actual" de ahora será el "anterior" de la siguiente vuelta.
        anterior = actual;
        actual = actual->siguiente;
    }

    return false;
}


// buscar()
bool ListaEnlazada::buscar(const string& clave, string& valorEncontrado) const {
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        if (actual->clave == clave) {
            valorEncontrado = actual->valor; // "devolvemos" el valor por referencia
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

int ListaEnlazada::obtenerTamanio() const {
    return tamanio;
}

bool ListaEnlazada::estaVacia() const {
    return cabeza == nullptr;
}

void ListaEnlazada::imprimir() const {
    Nodo* actual = cabeza;

    if (actual == nullptr) {
        cout << "(vacio)";
        return;
    }

    while (actual != nullptr) {
        cout << "[" << actual->clave << " -> " << actual->valor << "]";
        if (actual->siguiente != nullptr) {
            cout << " -> ";
        }
        actual = actual->siguiente;
    }
}

Nodo* ListaEnlazada::obtenerCabeza() const {
    return cabeza;
}
