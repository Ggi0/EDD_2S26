#ifndef LINKED_LIST_H
#define LINKED_LIST_H


#include "nodo.h"
#include <string>

class ListaEnlazada {

    private:
        Nodo* cabeza; //  Puntero al primer nodo de la lista
        int tamanio;

    public:
        ListaEnlazada(); // crear una lista vacia
        ~ListaEnlazada(); // liberar memoria de la lista --> destructor

        void insertar(int valor); // insertar un nodo al final de la lsita
        bool eliminar(int valor); // eliminar un nodo con el valor especificado

        bool buscar(int valor); // buscar un nodo con el valor especificado
        int obtenerTamanio(); // obtener el tamaño de la lista
        bool estaVacia(); // verificar si la lista está vacía
        void imprimir(); // imprimir los elementos de la lista
    
        void graficar(const std::string& nombreArchivo = "lista") const;
};

#endif // LINKED_LIST_H