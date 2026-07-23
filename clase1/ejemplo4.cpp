


#include <iostream>

// #include "linked_list/nodo.h"

#include "linked_list/linked_list.h"

int main() {

    // aqui vamos a hacer uso del TDA array list --> lista simplemente enlazada
    
    // de donde sacamos la lista???

    //Nodo nodo1(10);
    //Nodo nodo2(20);

    // &nodo2 obtiene la dirección en memoria de ese objeto.
    //nodo1.siguiente = &nodo2;

    // ACLARACION
    // &variable: obtiene la dirección de la variable (puntero).
    // *puntero:  accede al contenido de la dirección a la que apunta el puntero (desreferenciación).

    //nodo1.imprimir();
    //nodo2.imprimir();

    // lista1.agregar(10);

    //std::cout<< nodo1.dato << " --> " << nodo1.siguiente->dato << std::endl;


    ListaEnlazada lista1;

    lista1.estaVacia();

    lista1.insertar(10);
    lista1.insertar(20);
    lista1.insertar(30);
    lista1.insertar(40);
    lista1.insertar(50);

    lista1.imprimir();
    lista1.graficar("lista1_original");

    lista1.eliminar(30);
    lista1.imprimir();

    lista1.buscar(50);

    int tamanio_lista = lista1.obtenerTamanio();

    std::cout << "El tamaño de la lista es: " << tamanio_lista << std::endl;

    lista1.estaVacia();

    lista1.graficar("lista2_modificada");




    return 0;
}



