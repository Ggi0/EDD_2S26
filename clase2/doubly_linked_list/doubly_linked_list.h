
#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include "Nodo.h"
#include "../pelicula/pelicula.h"
#include <string>

class ListaDoble {
private:
    Nodo* cabeza;
    Nodo* cola;
    int tamanio;

    // Helpers privados para QuickSort 
    // (version adaptada a lista enlazada: en vez de indices [bajo..alto] 
    // como en un arreglo, se usan punteros a nodo [inicio..fin]).
    Nodo* particion(Nodo* inicio, Nodo* fin);
    void quickSortAux(Nodo* inicio, Nodo* fin);

public:
    ListaDoble();
    ~ListaDoble();


    void insertarAlFinal(const Pelicula& valor);  
    void insertarAlInicio(const Pelicula& valor);  
    bool eliminar(int id);                       


    bool buscar(int id) const;  // Busqueda simple: solo dice si existe.
    Pelicula* obtenerPorId(int id) const;   // Devuelve puntero al dato encontrado (o nullptr).
    int obtenerTamanio() const;
    bool estaVacia() const;

    // Getters usados por los algoritmos de ordenamiento/busqueda externos
    Nodo* obtenerCabeza() const;
    Nodo* obtenerCola() const;

    void imprimir() const;          // cabeza -> ... -> nullptr
    void imprimirReversa() const;   // cola -> ... -> nullptr

    // ORDENAMIENTO (respecto a dato.id)
    void ordenarBurbuja();
    void ordenarInsercion();
    void ordenarSeleccion();
    void ordenarQuickSort();

    void graficar(const std::string& nombreArchivo = "lista_doble") const;
};

#endif // DOUBLY_LINKED_LIST_H