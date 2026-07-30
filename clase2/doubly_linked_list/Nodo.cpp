

#include "Nodo.h"


Nodo::Nodo(const Pelicula& valor){
   
    dato = valor;
    siguiente = nullptr;
    anterior = nullptr;
}