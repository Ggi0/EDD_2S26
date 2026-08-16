#ifndef PELICULA_H
#define PELICULA_H

#include <string>



class Pelicula {
    private:
        std::string titulo;
        std::string director;
        int duracion; // en minutos
        int anio;
        std::string genero;


    public:
        Pelicula(std::string titulo, 
                std::string director, 
                int duracion, 
                int anio, 
                std::string genero);

         // ---- Getters ----
        std::string getTitulo() const;
        std::string getDirector() const;
        int getDuracion() const;
        int getAnio() const;
        std::string getGenero() const;
    
        // Texto para mostrar() en consola
        std::string toString() const;
    
        // Texto para el label de graphviz
        std::string toGraphvizLabel() const;


};

#endif