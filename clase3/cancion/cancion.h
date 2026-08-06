
#ifndef CANCION_H
#define CANCION_H

#include <string>

class Cancion {

    public:
        int id;
        std::string titulo;
        int duracion;

        Cancion();

        Cancion(
            int id, 
            const std::string& titulo,
            int duracion
            );

        void imprimir() const;
};

#endif