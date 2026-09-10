#include "Hijo.h"

Hijo::Hijo(Nodo* apuntador) {
    this->apuntador = apuntador;
    this->siguiente = nullptr;
}

/*

El objeto Hijo es solo un "envoltorio" dentro de la lista del padre;
el nodo real al que apunta pertenece al arbol y su ciclo de vida lo controla el algoritmo de ArbolB

Si aqui hicieramos "delete apuntador" podemos borrar un nodo que todavia esta en uso 
(por ejemplo durante una fusion, donde movemos hijos de un nodo a otro sin querer destruirlos).

*/
Hijo::~Hijo() {
}
