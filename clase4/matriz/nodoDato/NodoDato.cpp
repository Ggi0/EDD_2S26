#include "NodoDato.h"

NodoDato::NodoDato(int fila, int columna, Pelicula* pelicula) {
    this->fila = fila;
    this->columna = columna;
    this->pelicula = pelicula;

    // Al nacer, un nodo no esta enlazado con nadie todavia.
    // MatrizDispersa::insertar() se encarga de acomodar estos punteros.
    derecha = izquierda = arriba = abajo = nullptr;
}

NodoDato::~NodoDato() {
    // El NodoDato es el "dueño" de la pelicula que contiene, 
    // asi que al destruirse tambien libera esa memoria.
    delete pelicula;
}