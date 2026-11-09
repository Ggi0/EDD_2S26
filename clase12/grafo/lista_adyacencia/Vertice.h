/**

 Un VERTICE es una "cosa" del grafo: una ciudad, una persona, una computadora, etc. 

 
 * En la lista de adyacencia, los vertices forman la lista PRINCIPAL 
   y cada uno tiene su propia ListaAristas
 
    [A] --> [B,4] --> [C,2]
     |
    [B] --> [A,4] --> [C,1]
     |
    [C] --> [A,2] --> [B,1]

 */
#ifndef VERTICE_H
#define VERTICE_H

#include <string>
#include "ListaAristas.h"

class Vertice {
public:
    std::string nombre; 
    ListaAristas vecinos; // Aristas que SALEN de este vertice
    Vertice* siguiente;     // Siguiente vertice en la lista principal

    // Datos auxiliares para los recorridos (BFS). No son parte "logica" del grafo,
    //  solo marcas de trabajo del algoritmo.
    bool visitado;
    int nivel; // Distancia (en saltos) desde el vertice inicial

    explicit Vertice(const std::string& nombre)
        : nombre(nombre), siguiente(nullptr), visitado(false), nivel(-1) {}
};

#endif // VERTICE_H
