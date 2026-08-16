#ifndef NODODATO_H
#define NODODATO_H

#include "../../pelicula/pelicula.h"

class NodoDato {
    public:
        int fila;
        int columna;
        Pelicula* pelicula;   // dueño del recurso: NodoDato es responsable de liberarlo
     
        NodoDato* derecha;
        NodoDato* izquierda;
        NodoDato* arriba;
        NodoDato* abajo;
     
        NodoDato(int fila, int columna, Pelicula* pelicula);
        ~NodoDato(); // libera la Pelicula asociada
    };



#endif