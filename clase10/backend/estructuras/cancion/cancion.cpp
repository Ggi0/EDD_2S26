#include "cancion.h"
#include <iostream>

Cancion::Cancion() {
    id = 0;
    titulo = "";
    duracion = 0;
}

Cancion::Cancion(int id, 
            const std::string& titulo,
            int duracion)
    {
    this->id = id;
    this->titulo = titulo;
    this->duracion = duracion;
    }

void Cancion::imprimir() const {
    std::cout << "[ID:" << id << " | "
              << titulo << " - "
              << duracion << " seg]";
}