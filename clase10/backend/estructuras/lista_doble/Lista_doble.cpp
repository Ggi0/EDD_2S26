

#include "Lista_doble.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <utility> // std::swap
#include <filesystem>

using namespace std;
//namespace fs = std::filesystem;


// constructor
ListaDoble::ListaDoble() {
    cabeza = nullptr;
    cola = nullptr;
    tamanio = 0;
}

// destructor
ListaDoble::~ListaDoble() {
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        Nodo* siguienteNodo = actual->siguiente;
        delete actual;
        actual = siguienteNodo;
    }
    cabeza = nullptr;
    cola = nullptr;
}


ListaDoble::ListaDoble(const ListaDoble& otra) {
    cabeza = nullptr;
    cola = nullptr;
    tamanio = 0;
 
    // Recorremos "otra" y vamos insertando una copia de cada Cancion en
    // esta lista nueva. Como insertarAlFinal crea un Nodo* nuevo con
    // "new", cada lista termina con su propia memoria independiente.
    Nodo* actual = otra.cabeza;
    while (actual != nullptr) {
        insertarAlFinal(actual->dato);
        actual = actual->siguiente;
    }
}
 
ListaDoble& ListaDoble::operator=(const ListaDoble& otra) {
    if (this == &otra) {
        return *this; // proteccion contra auto-asignacion (a = a)
    }
 
    // Liberamos los nodos que esta lista ya tenia antes de copiar.
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        Nodo* siguienteNodo = actual->siguiente;
        delete actual;
        actual = siguienteNodo;
    }
    cabeza = nullptr;
    cola = nullptr;
    tamanio = 0;
 
    // Copiamos, en el mismo orden, los datos de "otra".
    actual = otra.cabeza;
    while (actual != nullptr) {
        insertarAlFinal(actual->dato);
        actual = actual->siguiente;
    }
 
    return *this;
}
 

// insertarAlFinal
void ListaDoble::insertarAlFinal(const Cancion& valor) {
    Nodo* nuevo = new Nodo(valor);

    if (cabeza == nullptr) {
        cabeza = nuevo;
        cola = nuevo;
    } else {
        cola->siguiente = nuevo;
        nuevo->anterior = cola;
        cola = nuevo;
    }
    tamanio++;

    cout<<"Se ha insertado la pelicula con ID: " << valor.id << " al final de la lista." << endl;
}

// insertarAlInicio
void ListaDoble::insertarAlInicio(const Cancion& valor) {
    Nodo* nuevo = new Nodo(valor);

    if (cabeza == nullptr) {
        cabeza = nuevo;
        cola = nuevo;
    } else {
        nuevo->siguiente = cabeza;
        cabeza->anterior = nuevo;
        cabeza = nuevo;
    }
    tamanio++;
}

// eliminar(id)
bool ListaDoble::eliminar(int id) {
    Nodo* actual = cabeza;

    while (actual != nullptr) {
        if (actual->dato.id == id) {

            if (actual->anterior != nullptr) {
                actual->anterior->siguiente = actual->siguiente;
            } else {
                cabeza = actual->siguiente;
            }

            if (actual->siguiente != nullptr) {
                actual->siguiente->anterior = actual->anterior;
            } else {
                cola = actual->anterior;
            }

            delete actual;
            tamanio--;
            return true;
        }
        actual = actual->siguiente;
    }

    return false;
}

// buscar
bool ListaDoble::buscar(int id) const {
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        if (actual->dato.id == id) return true;
        actual = actual->siguiente;
    }
    return false;
}

// obtenerPorId
Cancion* ListaDoble::obtenerPorId(int id) const {
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        if (actual->dato.id == id) return &(actual->dato);
        actual = actual->siguiente;
    }
    return nullptr;
}

int ListaDoble::obtenerTamanio() const {
    return tamanio;
}

bool ListaDoble::estaVacia() const {
    return cabeza == nullptr;
}

Nodo* ListaDoble::getCabeza() const {
    return cabeza;
}

Nodo* ListaDoble::getCola() const {
    return cola;
}

// imprimir 
void ListaDoble::imprimir() const {
    Nodo* actual = cabeza;
    cout << "cabeza -> ";
    while (actual != nullptr) {
        actual->dato.imprimir();
        cout << " -> ";
        actual = actual->siguiente;
    }
    cout << "nullptr" << endl;
}

void ListaDoble::imprimirReversa() const {
    Nodo* actual = cola;
    cout << "cola -> ";
    while (actual != nullptr) {
        actual->dato.imprimir();
        cout << " -> ";
        actual = actual->anterior;
    }
    cout << "nullptr" << endl;
}


// graficar
void ListaDoble::graficar(const string& nombreArchivo) const {

    // mucho ojo en donde ponen las rutas para graficar.
    // estas funcinan para QT Creator, pero si lo ejecutan desde consola,
    // puede que tengan que cambiar la ruta de salida.
    string rutaDot =
    "../../../../doubly_linked_list/reporte/" +
    nombreArchivo + ".dot";

    string rutaPng =
    "../../../../doubly_linked_list/reporte/" +
    nombreArchivo + ".png";


    //      PARA QUE FUNCIONE CON EL ARCHIVO clase2/ejemplo1.cpp
    // const string carpeta = "doubly_linked_list/reporte";
    // const string rutaDot = carpeta + "/" + nombreArchivo + ".dot";
    //const string rutaPng = carpeta + "/" + nombreArchivo + ".png";

    ofstream archivo(rutaDot);
    if (!archivo.is_open()) {
        cerr << "No se pudo crear el archivo: " << rutaDot << endl;
        return;
    }

    archivo << "digraph ListaDoble {\n";
    archivo << "    rankdir=LR;\n";
    archivo << "    node [shape=record, fontname=\"Helvetica\"];\n";
    archivo << "    edge [fontname=\"Helvetica\"];\n\n";

    if (cabeza == nullptr) {
        archivo << "    vacio [label=\"Lista vacia\", shape=plaintext];\n";
    } else {
        archivo << "    cabeza [shape=point];\n";
        archivo << "    cabeza -> nodo0;\n\n";

        Nodo* actual = cabeza;
        int indice = 0;

        while (actual != nullptr) {
            archivo << "    nodo" << indice
                    << " [label=\"{ <ant> * | ID " << actual->dato.id
                    << "\\n" << actual->dato.titulo
                    << " | <sig> * }\"];\n";

            if (actual->siguiente != nullptr) {
                archivo << "    nodo" << indice << ":sig -> nodo"
                        << (indice + 1) << ":ant;\n";
            } else {
                archivo << "    nullSig" << indice
                        << " [label=\"NULL\", shape=plaintext];\n";
                archivo << "    nodo" << indice
                        << ":sig -> nullSig" << indice << ";\n";
            }

            if (actual->anterior != nullptr) {
                archivo << "    nodo" << indice
                        << ":ant -> nodo" << (indice - 1)
                        << ":sig [color=blue, constraint=false];\n";
            } else {
                archivo << "    nullAnt" << indice
                        << " [label=\"NULL\", shape=plaintext];\n";
                archivo << "    nodo" << indice
                        << ":ant -> nullAnt" << indice
                        << " [color=blue];\n";
            }

            actual = actual->siguiente;
            indice++;
        }
    }

    archivo << "}\n";
    archivo.close();

    string comando = "/opt/local/bin/dot -Tpng \"" + rutaDot + "\" -o \"" + rutaPng + "\"";

    int resultado = system(comando.c_str());

    if (resultado == 0) {
        cout << "Imagen generada en: " << rutaPng << endl;
    } else {
        cerr << "Ocurrio un error al ejecutar Graphviz (dot)." << endl;
    }
}


void ListaDoble::graficarNodosEnFlujo(ofstream& archivo, const string& prefijo) const {
    if (cabeza == nullptr) {
        archivo << "    " << prefijo << "vacia "
                << "[label=\"(sin canciones)\", shape=plaintext, "
                << "fontname=\"Helvetica\"];\n";
        return;
    }

    archivo << "    subgraph cluster_" << prefijo << " {\n";
    archivo << "        style=invis;\n";

    Nodo* actual = cabeza;
    int indice = 0;

    while (actual != nullptr) {

        archivo << "        " << prefijo << indice
                << " [shape=record, "
                << "style=filled, "
                << "fillcolor=\"#FFE29A\", "
                << "fontname=\"Helvetica\", "
                << "label=\"ID "
                << actual->dato.id
                << "\\n"
                << actual->dato.titulo
                << "\"];\n";

        actual = actual->siguiente;
        indice++;
    }

    int total = indice;

    // Únicamente el NULL del final
    archivo << "        " << prefijo
            << "nullSig [label=\"NULL\", "
            << "shape=plaintext, "
            << "fontname=\"Helvetica\"];\n";

    // Enlaces entre canciones
    for (int i = 0; i < total - 1; i++) {

        archivo << "        "
                << prefijo << i
                << " -> "
                << prefijo << (i + 1)
                << " [dir=both, color=\"#B8860B\"];\n";
    }

    // Última canción -> NULL
    archivo << "        "
            << prefijo << (total - 1)
            << " -> "
            << prefijo << "nullSig"
            << " [color=blue];\n";

    archivo << "    }\n";
}