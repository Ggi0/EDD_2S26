#include "lista_circular.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

// CONSTRUCTOR / DESTRUCTOR
ListaCircular::ListaCircular() {
    cabeza = nullptr;
    ultimo = nullptr;
    tamanio = 0;
}

ListaCircular::~ListaCircular() {
    if (cabeza == nullptr) return;

    // No podemos recorrer con "while (actual != nullptr)" como en una
    // lista normal, porque aqui nunca llega a nullptr (es circular).
    // Recorremos desde cabeza->siguiente hasta volver a toparnos con
    // cabeza, y al final borramos cabeza aparte.
    NodoCircular* actual = cabeza->siguiente;
    while (actual != cabeza) {
        NodoCircular* siguienteNodo = actual->siguiente;
        delete actual;
        actual = siguienteNodo;
    }
    delete cabeza;
    cabeza = nullptr;
    ultimo = nullptr;
}

// insertar (al final, antes de volver a cabeza)
void ListaCircular::insertar(const Cantante& valor) {
    NodoCircular* nuevo = new NodoCircular(valor);

    if (cabeza == nullptr) {
        // Lista vacia: el nuevo nodo se apunta a si mismo.
        cabeza = nuevo;
        nuevo->siguiente = nuevo;
    } else {
        nuevo->siguiente = cabeza; // el nuevo cierra el circulo hacia cabeza
        ultimo->siguiente = nuevo;// el viejo ultimo ahora apunta al nuevo
    }
    ultimo = nuevo;
    tamanio++;
}

// eliminar(id)
bool ListaCircular::eliminar(int id) {
    if (cabeza == nullptr) return false;

    NodoCircular* actual = cabeza;
    NodoCircular* anterior = ultimo; // "anterior" de cabeza, en una circular, es ultimo.

    do {
        if (actual->dato.id == id) {
            if (actual == cabeza && actual == ultimo) {
                // Era el unico nodo de la lista.
                cabeza = nullptr;
                ultimo = nullptr;
            } else {
                anterior->siguiente = actual->siguiente;
                if (actual == cabeza) {
                    cabeza = actual->siguiente;
                }
                if (actual == ultimo) {
                    ultimo = anterior;
                }
            }
            delete actual;
            tamanio--;
            return true;
        }
        anterior = actual;
        actual = actual->siguiente;
    } while (actual != cabeza);

    return false;
}

// buscar
bool ListaCircular::buscar(int id) const {
    if (cabeza == nullptr) return false;

    NodoCircular* actual = cabeza;
    do {
        if (actual->dato.id == id) return true;
        actual = actual->siguiente;
    } while (actual != cabeza);

    return false;
}

// obtener por id
Cantante* ListaCircular::obtenerPorId(int id) const {
    if (cabeza == nullptr) return nullptr;

    NodoCircular* actual = cabeza;
    do {
        if (actual->dato.id == id) return &(actual->dato);
        actual = actual->siguiente;
    } while (actual != cabeza);

    return nullptr;
}

int ListaCircular::obtenerTamanio() const {
    return tamanio;
}

bool ListaCircular::estaVacia() const {
    return cabeza == nullptr;
}

NodoCircular* ListaCircular::getCabeza() const {
    return cabeza;
}


// imprimir
void ListaCircular::imprimir() const {
    if (cabeza == nullptr) {
        cout << "(lista circular vacia)" << endl;
        return;
    }

    NodoCircular* actual = cabeza;
    cout << "cabeza -> ";
    do {
        cout << "[ID:" << actual->dato.id << " | " << actual->dato.nombre << "] -> ";
        actual = actual->siguiente;
    } while (actual != cabeza);
    cout << "(vuelta a cabeza)" << endl;
}

// graficar
void ListaCircular::graficar(const string& nombreArchivo) const {



    // TODO cambiar para ejemplo con interfaz.
    //const string rutaDot =
    //"../../../../../lista_circular/reporte/" +
    //nombreArchivo + ".dot";

    //const string rutaPng =
    //"../../../../../lista_circular/reporte/" +
    //nombreArchivo + ".png";


    const string carpeta = "lista_circular/reporte";
    const string rutaDot = carpeta + "/" + nombreArchivo + ".dot";
    const string rutaPng = carpeta + "/" + nombreArchivo + ".png";

    ofstream archivo(rutaDot);
    if (!archivo.is_open()) {
        cerr << "No se pudo crear el archivo: " << rutaDot << endl;
        return;
    }

    archivo << "digraph ListaCircular {\n";
    archivo << "    rankdir=TB;\n";
    archivo << "    node [fontname=\"Helvetica\"];\n";
    archivo << "    edge [fontname=\"Helvetica\"];\n\n";

    if (cabeza == nullptr) {
        archivo << "    vacio [label=\"Lista circular vacia\", shape=plaintext];\n";
        archivo << "}\n";
        archivo.close();
        string comandoVacio = "dot -Tpng \"" + rutaDot + "\" -o \"" + rutaPng + "\"";
        system(comandoVacio.c_str());
        return;
    }

    // 1) Fila horizontal de cantantes
    archivo << "    { rank=same;\n";
    NodoCircular* actual = cabeza;
    int indice = 0;
    do {
        archivo << "        cantante" << indice
                << " [shape=box, style=\"rounded,filled\", fillcolor=\"#A8E6B0\", "
                << "label=\"ID " << actual->dato.id << "\\n" << actual->dato.nombre << "\"];\n";
        actual = actual->siguiente;
        indice++;
    } while (actual != cabeza);
    archivo << "    }\n\n";

    int totalCantantes = indice;

    // Puntero de entrada, igual que "cabeza" en la lista doble.
    archivo << "    cabezaPtr [shape=point];\n";
    archivo << "    cabezaPtr -> cantante0;\n\n";

    // Flechas del anillo: cantanteI -> cantanteI+1, y la ultima "da la
    // vuelta" de regreso al primero.
    for (int i = 0; i < totalCantantes; i++) {
        int siguienteIndice = (i + 1) % totalCantantes;
        if (i == totalCantantes - 1) {
            archivo << "    cantante" << i << " -> cantante" << siguienteIndice
                    << " [color=\"#2E8B57\", penwidth=2, constraint=false];\n";
        } else {
            archivo << "    cantante" << i << " -> cantante" << siguienteIndice
                    << " [color=\"#2E8B57\", penwidth=2];\n";
        }
    }
    archivo << "\n";

    // 2) Lista de canciones de cada cantante
    actual = cabeza;
    indice = 0;
    do {
        string prefijo = "c" + to_string(indice) + "_cancion";

        string primerNodoCanciones = actual->dato.listaCanciones.estaVacia()
            ? (prefijo + "vacia")
            : (prefijo + "0:ant");

        archivo << "    cantante" << indice << " -> " << primerNodoCanciones
                << " [style=dashed, color=\"#555555\"];\n";

        // Nodos/flechas de la ListaDoble de canciones de este cantante,
        // incrustados dentro de este mismo archivo .dot.
        actual->dato.listaCanciones.graficarNodosEnFlujo(archivo, prefijo);

        actual = actual->siguiente;
        indice++;
    } while (actual != cabeza);

    archivo << "}\n";
    archivo.close();

    string comando = "/opt/local/bin/dot -Tpng \"" + rutaDot + "\" -o \"" + rutaPng + "\"";
    int resultado = system(comando.c_str());

    if (resultado == 0) {
        cout << "Imagen generada en: " << rutaPng << endl;
    } else {
        cerr << "Ocurrio un error al ejecutar Graphviz (dot). yanosale:(" << endl;
    }
}