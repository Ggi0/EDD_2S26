

#include "nodo.h"

Nodo::Nodo(int valor){
    dato = valor;
    siguiente = nullptr;
}


void Nodo::imprimir(){
    std::cout << "Dato: " << dato << std::endl;

    if (siguiente != nullptr){
        std::cout << "si tiene siguiente" << std::endl;

    }else{
        std::cout << "no tiene siguiente" << std::endl;
    }
}