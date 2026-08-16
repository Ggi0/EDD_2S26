#include "pelicula.h"
#include <sstream>

Pelicula::Pelicula(std::string titulo, std::string director, int duracion,
                     int anio, std::string genero) {
    this->titulo = titulo;
    this->director = director;
    this->duracion = duracion;
    this->anio = anio;
    this->genero = genero;
}

std::string Pelicula::getTitulo() const{ return titulo; }
std::string Pelicula::getDirector() const { return director; }
int Pelicula::getDuracion() const{return duracion; }
int Pelicula::getAnio() const {return anio; }
std::string Pelicula::getGenero() const{ return genero; }

std::string Pelicula::toString() const {
    std::ostringstream oss;
    oss << titulo << " (" << director << ", " << anio << ", "
        << duracion << " min, " << genero << ")";
    return oss.str();
}

std::string Pelicula::toGraphvizLabel() const {
    // \n queda literal en el string para que graphviz lo interprete como salto de linea
    std::ostringstream oss;
    oss << titulo << "\\n" << anio << " | " << duracion << "min";
    return oss.str();
}