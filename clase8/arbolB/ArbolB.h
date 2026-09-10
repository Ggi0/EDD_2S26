#ifndef ARBOLB_H
#define ARBOLB_H

#include "Nodos/Nodo.h"
#include <string>
#include <fstream>


class ArbolB {
private:
    Nodo* raiz;

    int M;          // Grado del arbol
    int maxClaves;  // M - 1
    int maxHijos;   // M
    int minClaves;  // ceil(M/2) - 1   
    int minHijos;   // ceil(M/2)      

    // Contador auxiliar que solo se usa para asignar nombres unicos
    // (n0, n1, n2, ...) a los nodos cuando se genera el archivo .dot.
    int contadorGraficado;


    //  INSERCION

    // Inserta "valor" en el subarbol cuya raiz es "nodo".
    void insertarEnNodo(Nodo* nodo, int valor);

    // Divide un nodo que quedo con una clave de mas
    void dividirNodo(Nodo* nodo);

    //  BUSQUEDA 
    bool buscarRec(Nodo* nodo, int valor) const;

    //  ELIMINACION
    void eliminarRec(Nodo* nodo, int valor);

    // Devuelve el valor MAS GRANDE del subarbol, siguiendo siempre el
    // Se usa para obtener el PREDECESOR de una clave que se elimina de un nodo interno.
    int obtenerMaximo(Nodo* nodo) const;

    // Devuelve el valor MAS PEQUEÑO del subarbol, 
    // Se usa para obtener el SUCESOR de una clave que se elimina de un nodo interno.
    int obtenerMinimo(Nodo* nodo) const;

    
    void reestructurar(Nodo* nodo, int indice);

    // Rotacion simple: el hermano IZQUIERDO del hijo en "indice" le
    // "presta" una clave, pasando por el padre
    void rotarDerecha(Nodo* nodo, int indice);

    // Rotacion simple: el hermano DERECHO del hijo en "indice" le
    // "presta" una clave, pasando por el padre
    void rotarIzquierda(Nodo* nodo, int indice);

    // Fusiona el hijo "indice" y el hijo "indice+1" de "nodo" en un solo
    // nodo, bajando la clave "indice" del padre justo al medio
    void fusionar(Nodo* nodo, int indice);

    //  IMPRESION / GRAFICADO 
    
    int obtenerAltura(Nodo* nodo) const;
    
    void imprimirNivel(Nodo* nodo, int nivel) const;

    int contarClaves(Nodo* nodo) const;

    std::string generarDot(Nodo* nodo, std::ofstream &archivo);

public:

    ArbolB(int grado);
    ~ArbolB();

    //  OPERACIONES PUBLICAS 

    void insertar(int valor);
    bool buscar(int valor) const;
    void eliminar(int valor);


    void imprimirPorNiveles() const;
    void graficar(const std::string &rutaArchivoDot);

    bool estaVacio() const;
};

#endif
