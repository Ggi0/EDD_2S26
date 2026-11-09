/**

 * Lista enlazada simple de aristas. Cada VERTICE tiene una: son sus "vecinos".

 cabeza --> [B,4] --> [C,2] --> [D,7] --> nullptr
 administrar UNICAMENTE los nodos Arista de UN vertice (agregar, buscar, eliminar)
 
 */
#ifndef LISTA_ARISTAS_H
#define LISTA_ARISTAS_H

#include "Arista.h"

class ListaAristas {
private:
    Arista* cabeza;  // Primer nodo de la lista (nullptr si esta vacia)
    int cantidad;    // Cantidad de aristas (es el "grado" del vertice)

public:
    ListaAristas();
    ~ListaAristas();  // Libera todos los nodos

    // Una lista enlazada con punteros NO se debe copiar a la ligera
    // dos listas apuntando a los mismos nodos => doble liberacion
    ListaAristas(const ListaAristas&) = delete;
    ListaAristas& operator=(const ListaAristas&) = delete;

    // Agrega una arista al FINAL de la lista.
    // Devuelve false si ya existia una arista hacia ese destino.
    bool agregar(Vertice* destino, int peso);

    // Busca la arista que llega a "destino". Devuelve nullptr si no existe.
    Arista* buscar(Vertice* destino) const;

    // Elimina la arista que llega a "destino". Devuelve false si no existia.
    bool eliminar(Vertice* destino);

    // Elimina todas las aristas.
    void vaciar();

    // Primer nodo, para poder recorrer la lista desde afuera:
    //   for (Arista* a = lista.primero(); a != nullptr; a = a->siguiente)
    Arista* primero() const;

    int obtenerCantidad() const;
    bool estaVacia() const;
};

#endif // LISTA_ARISTAS_H
