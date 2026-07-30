


#include "pelicula.h"
#include <iostream>


Pelicula::Pelicula(){
    id = 0;
    titulo = "";
    anio =0;
    genero = "";
}


Pelicula::Pelicula(int id, const std::string& titulo, int anio, const std::string& genero) {
    this->id = id;
    this->titulo = titulo;
    this->anio = anio;
    this->genero = genero;
}


void Pelicula::mostrarInformacion() const {
    std::cout << "[ID:" << id <<" | " << titulo
              << " ( " << anio << ") - " << genero << "]";

}


