#ifndef BST_H
#define BST_H

#include "nodo.h"
#include <string>
#include <fstream>

class BST {
private:
    Nodo* raiz;

    //  funciones auxiliares recursivas (privadas) 
    // Reciben el nodo "actual" del recorrido y devuelven el nuevo
    // puntero que ese nivel del árbol debe tener 
    Nodo* insertarRec(Nodo* nodo, int valor);
    Nodo* eliminarRec(Nodo* nodo, int valor);
    Nodo* buscarRec(Nodo* nodo, int valor);
    Nodo* encontrarMinimo(Nodo* nodo);

    void inOrdenRec(Nodo* nodo);
    void preOrdenRec(Nodo* nodo);
    void postOrdenRec(Nodo* nodo);

    int alturaRec(Nodo* nodo);
    int contarNodosRec(Nodo* nodo);
    int contarHojasRec(Nodo* nodo);

    void liberarArbol(Nodo* nodo);
    void imprimirNivelRec(Nodo* nodo, int nivelObjetivo, int nivelActual);

    std::string graficarRec(Nodo* nodo, std::ofstream& archivo, int& contador) const;


public:
    BST();   // constructor: árbol vacío
    ~BST();  // destructor: libera todos los nodos

    void insertar(int valor);
    void eliminar(int valor);
    bool buscar(int valor);

    void inOrden();   
    void preOrden();   
    void postOrden(); 

    int altura(); // altura del árbol completo
    int contarNodos(); // cantidad total de nodos
    int contarHojas();  // cantidad de nodos sin hijos

    bool estaVacio();
    void imprimirPorNiveles(); // recorrido por niveles (BFS)

    void graficar(const std::string& nombreArchivo = "bst") const;

};

#endif