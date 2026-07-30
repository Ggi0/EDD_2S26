

#include "doubly_linked_list.h"
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

// insertarAlFinal
void ListaDoble::insertarAlFinal(const Pelicula& valor) {
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
void ListaDoble::insertarAlInicio(const Pelicula& valor) {
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
Pelicula* ListaDoble::obtenerPorId(int id) const {
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

Nodo* ListaDoble::obtenerCabeza() const {
    return cabeza;
}

Nodo* ListaDoble::obtenerCola() const {
    return cola;
}

// imprimir 
void ListaDoble::imprimir() const {
    Nodo* actual = cabeza;
    cout << "cabeza -> ";
    while (actual != nullptr) {
        actual->dato.mostrarInformacion();
        cout << " -> ";
        actual = actual->siguiente;
    }
    cout << "nullptr" << endl;
}

void ListaDoble::imprimirReversa() const {
    Nodo* actual = cola;
    cout << "cola -> ";
    while (actual != nullptr) {
        actual->dato.mostrarInformacion();
        cout << " -> ";
        actual = actual->anterior;
    }
    cout << "nullptr" << endl;
}

//                  ORDENAMIENTO
// 1) Burbuja. Compara pares de nodos adyacentes 
// y los intercambia si estan desordenados, "burbujeando" 
// el mayor hacia el final en cada pasada.
void ListaDoble::ordenarBurbuja() {
    if (cabeza == nullptr) return;

    bool huboIntercambio = true;
    while (huboIntercambio) {
        huboIntercambio = false;
        Nodo* actual = cabeza;
        while (actual != nullptr && actual->siguiente != nullptr) {
            if (actual->dato.id > actual->siguiente->dato.id) {
                swap(actual->dato, actual->siguiente->dato);
                huboIntercambio = true;
            }
            actual = actual->siguiente;
        }
    }
}

// 2) Insercion. Recorre la lista tomando cada nodo y lo "inserta" 
//   (moviendo datos hacia adelante) en su posicion correcta dentro de la 
//   porcion ya ordenada [cabeza..actual-1].
void ListaDoble::ordenarInsercion() {
    if (cabeza == nullptr) return;

    Nodo* actual = cabeza->siguiente;
    while (actual != nullptr) {
        Pelicula claveActual = actual->dato;
        Nodo* comparar = actual->anterior;

        // Recorremos hacia atras corriendo los datos mayores una
        // posicion adelante, hasta encontrar donde encaja "claveActual".
        while (comparar != nullptr && comparar->dato.id > claveActual.id) {
            comparar->siguiente->dato = comparar->dato;
            comparar = comparar->anterior;
        }

        if (comparar == nullptr) {
            cabeza->dato = claveActual;
        } else {
            comparar->siguiente->dato = claveActual;
        }

        actual = actual->siguiente;
    }
}

// 3) Seleccion. En cada pasada busca el nodo con el id
//    minimo dentro de [actual..cola] y lo intercambia con "actual".
void ListaDoble::ordenarSeleccion() {
    if (cabeza == nullptr) return;

    for (Nodo* actual = cabeza; actual != nullptr; actual = actual->siguiente) {
        Nodo* minimo = actual;
        for (Nodo* j = actual->siguiente; j != nullptr; j = j->siguiente) {
            if (j->dato.id < minimo->dato.id) {
                minimo = j;
            }
        }
        if (minimo != actual) {
            swap(actual->dato, minimo->dato);
        }
    }
}

// 4) QuickSort: Particion tipo Lomuto adaptada
//    a punteros de nodo en vez de indices de arreglo (tecnica
//  estandar para quicksort sobre listas doblemente enlazadas).
Nodo* ListaDoble::particion(Nodo* inicio, Nodo* fin) {
    Pelicula pivote = fin->dato;

    Nodo* i = inicio->anterior;
    for (Nodo* j = inicio; j != fin; j = j->siguiente) {
        if (j->dato.id <= pivote.id) {
            i = (i == nullptr) ? inicio : i->siguiente;
            swap(i->dato, j->dato);
        }
    }
    i = (i == nullptr) ? inicio : i->siguiente;
    swap(i->dato, fin->dato);
    return i;
}

void ListaDoble::quickSortAux(Nodo* inicio, Nodo* fin) {
    if (fin != nullptr && inicio != fin && inicio != fin->siguiente) {
        Nodo* pivote = particion(inicio, fin);
        quickSortAux(inicio, pivote->anterior);
        quickSortAux(pivote->siguiente, fin);
    }
}

void ListaDoble::ordenarQuickSort() {
    quickSortAux(cabeza, cola);
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