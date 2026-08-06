#ifndef CANTANTE_H
#define CANTANTE_H

#include <string>
#include "../lista_doble/Lista_doble.h"
#include "../cancion/cancion.h"

class Cantante {
    public:
        int id;
        std::string nombre;
        std::string genero;

        ListaDoble listaCanciones;  // lista doblmente enlazada de canciones

        Cantante();
        Cantante(int id, const std::string& nombre, const std::string& genero);

        // para no tener que escribir "listaCanciones.insertarAlFinal(...)" desde afuera cada vez.
        void agregarCancion(const Cancion& cancion);

        void imprimir() const;
};

#endif