#ifndef AVL_H
#define AVL_H

#include <string>
#include <fstream>
#include "Nodo.h"

using namespace std;

/*
    La lógica de autobalanceo está explicada a detalle en avl.cpp,
    en las funciones factorBalance(), balancear() y en las 4 rotaciones.
*/
class AVL {
private:
    Nodo* raiz;

    //  Utilidades internas de balanceo 

    // Libera recursivamente todos los nodos (post-orden), usada por el destructor.
    void liberarArbol(Nodo* nodo);

    // Altura "segura" de un nodo: si es nullptr, devuelve -1 (árbol vacío).
    int alturaNodo(Nodo* nodo);

    // FB = altura(subarbol izquierdo) - altura(subarbol derecho).
    int factorBalance(Nodo* nodo);

    void actualizarAltura(Nodo* nodo);

    //  Rotaciones 
    Nodo* rotarDerecha(Nodo* y);   // rotacion simple derecha (caso LL)
    Nodo* rotarIzquierda(Nodo* x); // rotacion simple izquierda (caso RR)

    // Revisa el factor de balance de "nodo" y aplica la rotacion
    Nodo* balancear(Nodo* nodo);

    //  Recursivas de operaciones básicas 
    Nodo* insertarRec(Nodo* nodo, int valor);
    Nodo* eliminarRec(Nodo* nodo, int valor);
    Nodo* buscarRec(Nodo* nodo, int valor);
    Nodo* encontrarMinimo(Nodo* nodo);

    //  Recorridos 
    void inOrdenRec(Nodo* nodo);
    void preOrdenRec(Nodo* nodo);
    void postOrdenRec(Nodo* nodo);

    //  Conteos 
    int contarNodosRec(Nodo* nodo);
    int contarHojasRec(Nodo* nodo);

    //  Impresion por niveles 
    void imprimirNivelRec(Nodo* nodo, int nivelObjetivo, int nivelActual);

    string graficarRec(Nodo* nodo, ofstream& archivo, int& contador) const;

public:
    AVL();
    ~AVL();

    bool estaVacio();

    void insertar(int valor);
    void eliminar(int valor);
    bool buscar(int valor);

    void inOrden();
    void preOrden();
    void postOrden();

    int altura();

    int contarNodos();
    int contarHojas();

    void imprimirPorNiveles();

    void graficar(const string& nombreArchivo) const;
};

#endif