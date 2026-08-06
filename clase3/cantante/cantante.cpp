#include "cantante.h"
#include <iostream>

Cantante::Cantante() {
    id = 0;
    nombre = "";
    genero = "";
    // listaCanciones se construye vacia automaticamente 
    // (su propio constructor por defecto ya deja cabeza = cola = nullptr).
}

Cantante::Cantante(int id, const std::string& nombre, const std::string& genero) {
    this->id = id;
    this->nombre = nombre;
    this->genero = genero;
}

void Cantante::agregarCancion(const Cancion& cancion) {
    listaCanciones.insertarAlFinal(cancion);
}

void Cantante::imprimir() const {
    std::cout << "[ID:" << id << " | " << nombre
              << " - " << genero
              << " | " << listaCanciones.obtenerTamanio() << " cancion(es)]";
}