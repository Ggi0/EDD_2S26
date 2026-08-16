#ifndef NODOCABECERA_H
#define NODOCABECERA_H

#include <string>
#include "../nodoDato/NodoDato.h"


class NodoCabecera {
public:
    int indice; // indice numerico (0,1,2,...) de la fila o columna
    std::string etiqueta;  // nombre legible: "Christopher Nolan", "Accion", etc. asientoVip, AsientoDoble

    NodoCabecera* siguiente;
    NodoCabecera* anterior;

    NodoDato* acceso;      // primer nodo dato de esta fila/columna (o nullptr si esta vacia)

    NodoCabecera(int indice, const std::string& etiqueta);
};

#endif