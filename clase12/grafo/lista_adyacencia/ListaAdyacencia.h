/**

ESTRUCTURA DE ALMACENAMIENTO del grafo.

 Es una lista enlazada de vertices, y cada vertice tiene a su vez una lista enlazada de aristas (sus vecinos). Es una "lista de listas".
 
  guardar y organizar los datos.
     Sabe agregar/buscar/eliminar vertices.
    Sabe agregar/buscar/eliminar UNA arista dirigida (origen -> destino).
    - NO decide si el grafo es dirigido o no dirigido, ni hace recorridos.
 
    */
#ifndef LISTA_ADYACENCIA_H
#define LISTA_ADYACENCIA_H

#include <string>
#include "Vertice.h"

class ListaAdyacencia {
private:
    Vertice* cabeza;      // Primer vertice de la lista principal
    int cantidadVertices;

public:
    ListaAdyacencia();
    ~ListaAdyacencia();

    ListaAdyacencia(const ListaAdyacencia&) = delete;
    ListaAdyacencia& operator=(const ListaAdyacencia&) = delete;

    //  Vertices 

    // Agrega un vertice al final. Devuelve false si el nombre ya existe.
    bool agregarVertice(const std::string& nombre);

    // Busca un vertice por nombre. Devuelve nullptr si no existe.
    Vertice* buscarVertice(const std::string& nombre) const;

    // Elimina un vertice Y todas las aristas que llegaban a el.
    bool eliminarVertice(const std::string& nombre);

    //  Aristas (dirigidas: origen -> destino) 

    bool agregarArista(const std::string& origen, const std::string& destino, int peso);
    bool eliminarArista(const std::string& origen, const std::string& destino);
    Arista* buscarArista(const std::string& origen, const std::string& destino) const;



    Vertice* primero() const; // Para recorrer los vertices desde afuera
    int obtenerCantidadVertices() const;
    bool estaVacia() const;

    // Pone visitado=false y nivel=-1 en todos los vertices (antes de un BFS).
    void reiniciarMarcas();

    // Imprime la lista en consola, ej:   A -> [B,4] -> [C,2] -> NULL
    void imprimir() const;

    // Genera el reporte .dot (Graphviz) que dibuja la lista de adyacencia
    bool generarDot(const std::string& rutaDot) const;
};

#endif // LISTA_ADYACENCIA_H
