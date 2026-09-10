#include "Nodo.h"
#include <iostream>

Nodo::Nodo(bool esHoja) {
    this->esHoja = esHoja;
    this->primeraClave = nullptr;
    this->primerHijo = nullptr;
    this->padre = nullptr;
    this->numClaves = 0;
    this->numHijos = 0;
}

/* Destructor de Nodo

Libera todo la memoria queesta usando el nodo posee:
   1) Su propia lista de Claves
   2) Su propia lista de Hijos, pero OJITOO: al liberar cada Hijo tambien se hace "delete hijoActual->apuntador", 
      es decir, se destruye el NODO HIJO completo. 
      Esto dispara de nuevo el destructor de Nodo sobre ese hijo, 
      que a su vez destruye a SUS hijos, y asi sucesivamente hasta llegar a las hojas.
*/
Nodo::~Nodo() {
    // Liberar la lista de claves de este nodo
    Clave* claveActual = primeraClave;
    while (claveActual != nullptr) {
        Clave* siguiente = claveActual->siguiente;
        delete claveActual;
        claveActual = siguiente;
    }

    //  Liberar la lista de hijos (y recursivamente los subarboles)
    Hijo* hijoActual = primerHijo;
    while (hijoActual != nullptr) {
        Hijo* siguiente = hijoActual->siguiente;
        delete hijoActual->apuntador; // RECURSIVO: llama a ~Nodo() del hijo
        delete hijoActual;            // libera el "envoltorio" Hijo
        hijoActual = siguiente;
    }
}

int Nodo::obtenerClave(int indice) const {
    Clave* actual = primeraClave;
    for (int i = 0; i < indice; i++) {
        actual = actual->siguiente;
    }
    return actual->valor;
}

void Nodo::insertarClaveEnPosicion(int valor, int posicion) {
    Clave* nueva = new Clave(valor);

    if (posicion == 0) {
        // Se inserta como nueva cabeza de la lista
        nueva->siguiente = primeraClave;
        primeraClave = nueva;
    } else {
        // Se avanza hasta el nodo justo anterior a la posicion deseada
        Clave* anterior = primeraClave;
        for (int i = 0; i < posicion - 1; i++) {
            anterior = anterior->siguiente;
        }
        nueva->siguiente = anterior->siguiente;
        anterior->siguiente = nueva;
    }

    numClaves++;
}

int Nodo::eliminarClaveEnPosicion(int posicion) {
    Clave* aEliminar;

    if (posicion == 0) {
        aEliminar = primeraClave;
        primeraClave = primeraClave->siguiente;
    } else {
        Clave* anterior = primeraClave;
        for (int i = 0; i < posicion - 1; i++) {
            anterior = anterior->siguiente;
        }
        aEliminar = anterior->siguiente;
        anterior->siguiente = aEliminar->siguiente;
    }

    int valor = aEliminar->valor;
    delete aEliminar;
    numClaves--;
    return valor;
}


/*

 Busca en QUE posicion (0-based) deberia ir "valor" dentro de las claves de este nodo

 Si el valor YA existe en este nodo, "encontrada" se pone en true y se devuelve la posicion exacta donde esta. 
 Si no existe "encontrada" queda en false y se devuelve la posicion de inserción
    (que tambien sirve como el indice del hijo por el cual descender cuando el nodo no es hoja).


*/
int Nodo::buscarPosicion(int valor, bool &encontrada) const {
    Clave* actual = primeraClave;
    int indice = 0;

    // Avanza mientras el valor buscado sea mayor que la clave actual
    while (actual != nullptr && valor > actual->valor) {
        actual = actual->siguiente;
        indice++;
    }

    encontrada = (actual != nullptr && actual->valor == valor);
    return indice;
}

Nodo* Nodo::obtenerHijo(int indice) const {
    Hijo* actual = primerHijo;
    for (int i = 0; i < indice; i++) {
        actual = actual->siguiente;
    }
    return actual->apuntador;
}

void Nodo::insertarHijoEnPosicion(Nodo* nodo, int posicion) {
    Hijo* nuevo = new Hijo(nodo);

    if (posicion == 0) {
        nuevo->siguiente = primerHijo;
        primerHijo = nuevo;
    } else {
        Hijo* anterior = primerHijo;
        for (int i = 0; i < posicion - 1; i++) {
            anterior = anterior->siguiente;
        }
        nuevo->siguiente = anterior->siguiente;
        anterior->siguiente = nuevo;
    }

    numHijos++;
}

Nodo* Nodo::eliminarHijoEnPosicion(int posicion) {
    Hijo* aEliminar;

    if (posicion == 0) {
        aEliminar = primerHijo;
        primerHijo = primerHijo->siguiente;
    } else {
        Hijo* anterior = primerHijo;
        for (int i = 0; i < posicion - 1; i++) {
            anterior = anterior->siguiente;
        }
        aEliminar = anterior->siguiente;
        anterior->siguiente = aEliminar->siguiente;
    }

    Nodo* nodo = aEliminar->apuntador;
    delete aEliminar; // solo se borra el "envoltorio" Hijo, nunca el nodo apuntado
    numHijos--;
    return nodo;
}

void Nodo::imprimirClaves() const {
    std::cout << "[";
    Clave* actual = primeraClave;
    while (actual != nullptr) {
        std::cout << actual->valor;
        if (actual->siguiente != nullptr) std::cout << ",";
        actual = actual->siguiente;
    }
    std::cout << "]";
}
