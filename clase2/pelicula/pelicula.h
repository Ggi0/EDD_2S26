


#ifndef PELICULA_H
#define PELICULA_H


#include <string>


class Pelicula {

    public:
        int id;
        std::string titulo;
        int anio;
        std::string genero;


        Pelicula();

        Pelicula(int id, const std::string& titulo, int anio, const std::string& genero);


        void mostrarInformacion() const;


};



#endif