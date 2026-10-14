#ifndef CANTANTE_SERVICE_H
#define CANTANTE_SERVICE_H

#include "../estructuras/lista_circular/lista_circular.h"
#include "../estructuras/cantante/cantante.h"
#include "../estructuras/cancion/cancion.h"

class CantanteService
{
private:
    ListaCircular listaCantantes;

public:
    CantanteService();

    ListaCircular& obtenerLista();

    bool agregarCantante(const Cantante& cantante);

    bool eliminarCantante(int id);

    Cantante* obtenerCantante(int id);

    bool existeCantante(int id);

    bool agregarCancion(int idCantante, const Cancion& cancion);

    bool eliminarCancion(int idCantante, int idCancion);

    Cancion* obtenerCancion(int idCantante, int idCancion);
};

#endif