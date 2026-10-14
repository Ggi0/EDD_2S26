#ifndef JSON_UTILS_H
#define JSON_UTILS_H

#include "crow.h"
#include "../estructuras/cantante/cantante.h"
#include "../estructuras/cancion/cancion.h"

namespace JsonUtils
{
    inline crow::json::wvalue cancionToJson(
        const Cancion& cancion
    )
    {
        crow::json::wvalue json;

        json["id"] = cancion.id;
        json["titulo"] = cancion.titulo;
        json["duracion"] = cancion.duracion;

        return json;
    }

    inline crow::json::wvalue cantanteToJson(
        const Cantante& cantante
    )
    {
        crow::json::wvalue json;

        json["id"] = cantante.id;
        json["nombre"] = cantante.nombre;
        json["genero"] = cantante.genero;

        crow::json::wvalue canciones;

        Nodo* actual = cantante.listaCanciones.getCabeza();

        int posicion = 0;

        while (actual != nullptr)
        {
            canciones[posicion++] = cancionToJson(actual->dato);

            actual = actual->siguiente;
        }

        json["canciones"] = std::move(canciones);

        return json;
    }
}

#endif