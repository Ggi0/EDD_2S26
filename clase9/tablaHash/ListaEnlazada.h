#ifndef LISTA_ENLAZADA_H
#define LISTA_ENLAZADA_H

#include "Nodo.h"
#include <string>
using namespace std;


class ListaEnlazada {
private:
    Nodo* cabeza;  // puntero al primer nodo de la lista (nullptr si la lista/bucket está vacío)
    int tamanio; // cantidad de nodos actualmente encadenados en este bucket

public:
    ListaEnlazada(); 
    ~ListaEnlazada();

    void insertar(const string& clave, const string& valor, int indexBucket);

    // Busca un nodo cuya "clave" coincida con la recibida 
    bool eliminar(const string& clave);

    // Busca un nodo por clave. Si existe, copia su valor en "valorEncontrado"
    bool buscar(const string& clave, string& valorEncontrado) const;

    int obtenerTamanio() const;   // nodos que hay encadenados en este bucket
    bool estaVacia() const;  

    void imprimir() const;

    Nodo* obtenerCabeza() const;
};

#endif // LISTA_ENLAZADA_H
