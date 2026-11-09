
#include "ListaAdyacencia.h"
#include <fstream>
#include <iostream>

using std::string;


static string idDot(const string& nombre) {
    string id = nombre;
    for (size_t i = 0; i < id.size(); i++) {
        char c = id[i];
        bool valido = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
                      (c >= '0' && c <= '9') || c == '_';
        if (!valido) {
            id[i] = '_';
        }
    }
    return id;
}

ListaAdyacencia::ListaAdyacencia() : cabeza(nullptr), cantidadVertices(0) {}

ListaAdyacencia::~ListaAdyacencia() {
    // Al borrar cada Vertice, su ListaAristas se destruye sola (destructor).
    while (cabeza != nullptr) {
        Vertice* siguiente = cabeza->siguiente;
        delete cabeza;
        cabeza = siguiente;
    }
}

//  VERTICES 

bool ListaAdyacencia::agregarVertice(const string& nombre) {
    if (buscarVertice(nombre) != nullptr) {
        return false;  // Ya existe
    }

    Vertice* nuevo = new Vertice(nombre);

    if (cabeza == nullptr) {
        cabeza = nuevo;
    } else {
        Vertice* actual = cabeza;
        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }

    cantidadVertices++;
    return true;
}

Vertice* ListaAdyacencia::buscarVertice(const string& nombre) const {
    for (Vertice* actual = cabeza; actual != nullptr; actual = actual->siguiente) {
        if (actual->nombre == nombre) {
            return actual;
        }
    }
    return nullptr;
}

bool ListaAdyacencia::eliminarVertice(const string& nombre) {
    Vertice* objetivo = buscarVertice(nombre);
    if (objetivo == nullptr) {
        return false;
    }

    // PASO 1: quitar todas las aristas de OTROS vertices que apuntan al
    // vertice que vamos a borrar. 
    for (Vertice* v = cabeza; v != nullptr; v = v->siguiente) {
        v->vecinos.eliminar(objetivo);
    }

    // PASO 2: desenlazar el vertice de la lista principal.
    Vertice* anterior = nullptr;
    Vertice* actual = cabeza;
    while (actual != objetivo) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (anterior == nullptr) {
        cabeza = actual->siguiente;       // Era la cabeza
    } else {
        anterior->siguiente = actual->siguiente;
    }

    // PASO 3: liberar la memoria (tambien libera sus propias aristas).
    delete actual;
    cantidadVertices--;
    return true;
}

//  ARISTAS 

bool ListaAdyacencia::agregarArista(const string& origen, const string& destino, int peso) {
    Vertice* vOrigen = buscarVertice(origen);
    Vertice* vDestino = buscarVertice(destino);

    // Ambos vertices deben existir.
    if (vOrigen == nullptr || vDestino == nullptr) {
        return false;
    }
    return vOrigen->vecinos.agregar(vDestino, peso);
}

bool ListaAdyacencia::eliminarArista(const string& origen, const string& destino) {
    Vertice* vOrigen = buscarVertice(origen);
    Vertice* vDestino = buscarVertice(destino);

    if (vOrigen == nullptr || vDestino == nullptr) {
        return false;
    }
    return vOrigen->vecinos.eliminar(vDestino);
}

Arista* ListaAdyacencia::buscarArista(const string& origen, const string& destino) const {
    Vertice* vOrigen = buscarVertice(origen);
    Vertice* vDestino = buscarVertice(destino);

    if (vOrigen == nullptr || vDestino == nullptr) {
        return nullptr;
    }
    return vOrigen->vecinos.buscar(vDestino);
}


Vertice* ListaAdyacencia::primero() const {
    return cabeza;
}

int ListaAdyacencia::obtenerCantidadVertices() const {
    return cantidadVertices;
}

bool ListaAdyacencia::estaVacia() const {
    return cabeza == nullptr;
}

void ListaAdyacencia::reiniciarMarcas() {
    for (Vertice* v = cabeza; v != nullptr; v = v->siguiente) {
        v->visitado = false;
        v->nivel = -1;
    }
}

void ListaAdyacencia::imprimir() const {
    if (cabeza == nullptr) {
        std::cout << "(lista de adyacencia vacia)" << std::endl;
        return;
    }
    for (Vertice* v = cabeza; v != nullptr; v = v->siguiente) {
        std::cout << v->nombre << " -> ";
        for (Arista* a = v->vecinos.primero(); a != nullptr; a = a->siguiente) {
            std::cout << "[" << a->destino->nombre << "," << a->peso << "] -> ";
        }
        std::cout << "NULL" << std::endl;
    }
}

//  GRAPHVIZ DE LA LISTA 
bool ListaAdyacencia::generarDot(const string& rutaDot) const {
    std::ofstream out(rutaDot);
    if (!out.is_open()) {
        return false;
    }

    out << "digraph LISTA_ADYACENCIA {\n";
    out << "    rankdir=TB;\n";
    out << "    node [shape=box, style=filled, fillcolor=\"#B0C4DE\", fontname=\"Arial\"];\n";
    out << "    edge [color=\"#333333\", constraint=true];\n";

    Vertice* anterior = nullptr;  // Vertice de la fila anterior (para unir la columna)

    for (Vertice* v = cabeza; v != nullptr; v = v->siguiente) {
        string idV = "v_" + idDot(v->nombre);

        // Nodo del vertice (columna izquierda)
        out << "    " << idV << " [label=\"" << v->nombre
            << "\", fillcolor=\"#87CEFA\", group=\"col1\"];\n";

        // Union vertical con el vertice anterior (sin flecha)
        if (anterior != nullptr) {
            out << "    v_" << idDot(anterior->nombre) << " -> " << idV << " [dir=none];\n";
        }

        string idPrevio = idV;     // Ultimo nodo de la fila (para encadenar)
        string mismaFila = idV;    // Ids que van en { rank=same; ... }

        // Un nodo por cada vecino, enlazado al anterior
        for (Arista* a = v->vecinos.primero(); a != nullptr; a = a->siguiente) {
            string idN = "n_" + idDot(v->nombre) + "_" + idDot(a->destino->nombre);

            out << "    " << idN << " [label=\"" << a->destino->nombre
                << "\\n(peso " << a->peso << ")\"];\n";
            out << "    " << idPrevio << " -> " << idN << ";\n";

            idPrevio = idN;
            mismaFila += " " + idN;
        }

        // Cierre de la fila con NULL
        string idNull = "null_" + idDot(v->nombre);
        out << "    " << idNull << " [label=\"NULL\", shape=plaintext];\n";
        out << "    " << idPrevio << " -> " << idNull << ";\n";
        mismaFila += " " + idNull;

        out << "    { rank=same; " << mismaFila << " }\n\n";

        anterior = v;
    }

    out << "}\n";
    out.close();
    return true;
}
