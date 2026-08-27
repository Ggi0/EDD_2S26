#include "bst.h"
#include <iostream>

#include <cstdlib>

using namespace std;

// Constructor / Destructor
BST::BST() {
    raiz = nullptr; 
}

BST::~BST() {
    liberarArbol(raiz); // recorremos post-orden liberando memoria
    raiz = nullptr;
}

// Libera recursivamente todos los nodos del árbol 
void BST::liberarArbol(Nodo* nodo) {
    if (nodo == nullptr) return;
    liberarArbol(nodo->izquierdo);
    liberarArbol(nodo->derecho);
    delete nodo;
}

bool BST::estaVacio() {
    return raiz == nullptr;
}

/*

    INSERTAR

    La función devuelve el puntero que el nivel superior debe
    guardar: así "reconectamos" el árbol en cada retorno de la
    recursión sin necesitar punteros dobles ni variables globales.

*/ 
void BST::insertar(int valor) {
    raiz = insertarRec(raiz, valor);
}

Nodo* BST::insertarRec(Nodo* nodo, int valor) {
    // primer caso: encontramos el lugar vacío -> creamos el nodo
    if (nodo == nullptr) {
        return new Nodo(valor);
    }

    if (valor < nodo->dato) {
        nodo->izquierdo = insertarRec(nodo->izquierdo, valor);
    } else if (valor > nodo->dato) {
        nodo->derecho = insertarRec(nodo->derecho, valor);
    } else {
        // valor == nodo->dato -> no se permiten duplicados,
        // simplemente no hacemos nada y devolvemos el nodo tal cual.
        cout << " El valor " << valor << " ya existe, no se inserta duplicado.\n";
    }

    return nodo;
}

// BUSCAR
bool BST::buscar(int valor) {
    return buscarRec(raiz, valor) != nullptr;
}

Nodo* BST::buscarRec(Nodo* nodo, int valor) {
    // Caso base: árbol vacío o encontramos el valor
    if (nodo == nullptr || nodo->dato == valor) {
        return nodo;
    }

    if (valor < nodo->dato) {
        return buscarRec(nodo->izquierdo, valor);
    } else {
        return buscarRec(nodo->derecho, valor);
    }
}

// ELIMINAR
void BST::eliminar(int valor) {
    raiz = eliminarRec(raiz, valor);
}

Nodo* BST::eliminarRec(Nodo* nodo, int valor) {
    if (nodo == nullptr) {
        cout << "[info] El valor " << valor << " no existe en el árbol.\n";
        return nodo;
    }

    if (valor < nodo->dato) {
        nodo->izquierdo = eliminarRec(nodo->izquierdo, valor);
    } else if (valor > nodo->dato) {
        nodo->derecho = eliminarRec(nodo->derecho, valor);
    } else {
        // Encontramos el nodo a eliminar

        // Caso 1: sin hijos (hoja)
        if (nodo->izquierdo == nullptr && nodo->derecho == nullptr) {
            delete nodo;
            return nullptr;
        }

        // Caso 2: un solo hijo -> el hijo ocupa el lugar del nodo
        if (nodo->izquierdo == nullptr) {
            Nodo* temp = nodo->derecho;
            delete nodo;
            return temp;
        }
        if (nodo->derecho == nullptr) {
            Nodo* temp = nodo->izquierdo;
            delete nodo;
            return temp;
        }

        // Caso 3: dos hijos -> buscamos el sucesor inorden
        // (el nodo más pequeño del subárbol derecho)
        Nodo* sucesor = encontrarMinimo(nodo->derecho);

        // Copiamos el dato del sucesor en el nodo actual
        nodo->dato = sucesor->dato;

        // Eliminamos el sucesor de su posición original dentro
        // del subarbol derecho (ahí tendrá a lo sumo hijo derecho,
        // porque por definición no tiene hijo izquierdo)
        nodo->derecho = eliminarRec(nodo->derecho, sucesor->dato);
    }

    return nodo;
}

// Retorna el nodo con el valor minimo de un subarbol:
Nodo* BST::encontrarMinimo(Nodo* nodo) {
    while (nodo->izquierdo != nullptr) {
        nodo = nodo->izquierdo;
    }
    return nodo;
}

// RECORRIDOS
// InOrden
void BST::inOrden() {
    cout << "InOrden:   ";
    inOrdenRec(raiz);
    cout << endl;
}

void BST::inOrdenRec(Nodo* nodo) {
    if (nodo == nullptr) return;
    inOrdenRec(nodo->izquierdo);
    cout << nodo->dato << " ";
    inOrdenRec(nodo->derecho);
}

// PreOrden: 
void BST::preOrden() {
    cout << "PreOrden:  ";
    preOrdenRec(raiz);
    cout << endl;
}

void BST::preOrdenRec(Nodo* nodo) {
    if (nodo == nullptr) return;
    cout << nodo->dato << " ";
    preOrdenRec(nodo->izquierdo);
    preOrdenRec(nodo->derecho);
}

// PostOrden: 
void BST::postOrden() {
    cout << "PostOrden: ";
    postOrdenRec(raiz);
    cout << endl;
}

void BST::postOrdenRec(Nodo* nodo) {
    if (nodo == nullptr) return;
    postOrdenRec(nodo->izquierdo);
    postOrdenRec(nodo->derecho);
    cout << nodo->dato << " ";
}

// ALTURA / CONTEOS
// Convención usada: un arbol vacío tiene altura -1, 
// un nodo hoja (sin hijos) tiene altura 0. 
// Cada nivel adicional suma 1.
int BST::altura() {
    return alturaRec(raiz);
}

int BST::alturaRec(Nodo* nodo) {
    if (nodo == nullptr) return -1;

    int alturaIzq = alturaRec(nodo->izquierdo);
    int alturaDer = alturaRec(nodo->derecho);

    // la altura del nodo es 1 + la mayor altura de sus subárboles
    return 1 + max(alturaIzq, alturaDer);
}

int BST::contarNodos() {
    return contarNodosRec(raiz);
}

int BST::contarNodosRec(Nodo* nodo) {
    if (nodo == nullptr) return 0;
    return 1 + contarNodosRec(nodo->izquierdo) + contarNodosRec(nodo->derecho);
}

int BST::contarHojas() {
    return contarHojasRec(raiz);
}

int BST::contarHojasRec(Nodo* nodo) {
    if (nodo == nullptr) return 0;
    if (nodo->izquierdo == nullptr && nodo->derecho == nullptr) return 1;
    return contarHojasRec(nodo->izquierdo) + contarHojasRec(nodo->derecho);
}

// IMPRESIoN POR NIVELES
void BST::imprimirPorNiveles() {
    int h = altura();
    if (h == -1) {
        cout << "(árbol vacío)" << endl;
        return;
    }

    for (int nivel = 0; nivel <= h; nivel++) {
        cout << "Nivel " << nivel << ": ";
        imprimirNivelRec(raiz, nivel, 0);
        cout << endl;
    }
}

void BST::imprimirNivelRec(Nodo* nodo, int nivelObjetivo, int nivelActual) {
    if (nodo == nullptr) return;

    if (nivelActual == nivelObjetivo) {
        cout << nodo->dato << " ";
        return;
    }

    imprimirNivelRec(nodo->izquierdo, nivelObjetivo, nivelActual + 1);
    imprimirNivelRec(nodo->derecho, nivelObjetivo, nivelActual + 1);
}



// GRAFICAR (Graphviz)
void BST::graficar(const string& nombreArchivo) const {
    const string carpeta = "bst/reporte";
    const string rutaDot = carpeta + "/" + nombreArchivo + ".dot";
    const string rutaPng = carpeta + "/" + nombreArchivo + ".png";
 
    ofstream archivo(rutaDot);
    if (!archivo.is_open()) {
        cerr << "No se pudo crear el archivo: " << rutaDot << endl;
        return;
    }
 
    archivo << "digraph BST {\n";
    archivo << "    rankdir=TB;\n";
    archivo << "    node [fontname=\"Helvetica\"];\n";
    archivo << "    edge [fontname=\"Helvetica\"];\n\n";
 
    if (raiz == nullptr) {
        archivo << "    vacio [label=\"Arbol vacio\", shape=plaintext];\n";
        archivo << "}\n";
        archivo.close();
        string comandoVacio = "dot -Tpng \"" + rutaDot + "\" -o \"" + rutaPng + "\"";
        system(comandoVacio.c_str());
        return;
    }
 
    // Recorremos el árbol (pre-orden) escribiendo cada nodo y sus
    // flechas hacia sus hijos. graficarRec va asignando ids únicos
    // (nodo0, nodo1, ...) a medida que visita nodos.
    int contador = 0;
    string idRaiz = graficarRec(raiz, archivo, contador);
 
    // Puntero de entrada, igual que "cabezaPtr" en la lista circular.
    archivo << "\n    raizPtr [shape=point];\n";
    archivo << "    raizPtr -> " << idRaiz << ";\n";
 
    archivo << "}\n";
    archivo.close();
 
    string comando = "dot -Tpng \"" + rutaDot + "\" -o \"" + rutaPng + "\"";
    int resultado = system(comando.c_str());
 
    if (resultado == 0) {
        cout << "Imagen generada en: " << rutaPng << endl;
    } else {
        cerr << "Ocurrio un error al ejecutar Graphviz (dot). yanosale:(" << endl;
    }
}

string BST::graficarRec(Nodo* nodo, ofstream& archivo, int& contador) const {
    if (nodo == nullptr) return "";
 
    string idActual = "nodo" + to_string(contador++);
 
    archivo << "    " << idActual
            << " [shape=circle, style=\"filled\", fillcolor=\"#A8E6B0\", "
            << "label=\"" << nodo->dato << "\"];\n";
 
    string idIzq = graficarRec(nodo->izquierdo, archivo, contador);
    if (!idIzq.empty()) {
        archivo << "    " << idActual << " -> " << idIzq
                << " [color=\"#2E8B57\", label=\"I\"];\n";
    }
 
    string idDer = graficarRec(nodo->derecho, archivo, contador);
    if (!idDer.empty()) {
        archivo << "    " << idActual << " -> " << idDer
                << " [color=\"#2E8B57\", label=\"D\"];\n";
    }
 
    return idActual;
}
 
