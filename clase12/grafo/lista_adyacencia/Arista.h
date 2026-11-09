/**
 
Una ARISTA (arco) representa una conexion entre dos vertices.
 
 * En una lista de adyacencia, cada arista es un NODO de una lista enlazada simple. 
 
 Esa lista cuelga de un vertice (el vertice "origen") y cada nodo
 
 destino   : a que vertice llega la conexion
 peso      : el "costo" de la conexion (distancia, tiempo, precio...)
siguiente : puntero al siguiente nodo de la lista (nullptr si es el ultimo)

 */
#ifndef ARISTA_H
#define ARISTA_H

// Declaracion adelantada
class Vertice;

class Arista {
public:
    Vertice* destino; // Vertice al que apunta esta arista
    int peso;       
    Arista* siguiente;

    // Constructor: crea una arista aislada
    Arista(Vertice* destino, int peso)
        : destino(destino), peso(peso), siguiente(nullptr) {}
};

#endif // ARISTA_H
