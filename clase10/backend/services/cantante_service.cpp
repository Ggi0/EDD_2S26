#include "cantante_service.h"

CantanteService::CantanteService()
{
}

ListaCircular& CantanteService::obtenerLista()
{
    return listaCantantes;
}

bool CantanteService::agregarCantante(const Cantante& cantante)
{
    // Evitar IDs repetidos
    if (listaCantantes.buscar(cantante.id))
    {
        return false;
    }

    listaCantantes.insertar(cantante);

    return true;
}

bool CantanteService::eliminarCantante(int id)
{
    return listaCantantes.eliminar(id);
}

Cantante* CantanteService::obtenerCantante(int id)
{
    return listaCantantes.obtenerPorId(id);
}

bool CantanteService::existeCantante(int id)
{
    return listaCantantes.buscar(id);
}

bool CantanteService::agregarCancion(
    int idCantante,
    const Cancion& cancion
)
{
    Cantante* cantante = listaCantantes.obtenerPorId(idCantante);

    if (cantante == nullptr)
    {
        return false;
    }

    // Evitar canciones con el mismo ID
    if (cantante->listaCanciones.buscar(cancion.id))
    {
        return false;
    }

    cantante->agregarCancion(cancion);

    return true;
}

bool CantanteService::eliminarCancion(int idCantante, int idCancion)
{
    Cantante* cantante = listaCantantes.obtenerPorId(idCantante);

    if (cantante == nullptr)
    {
        return false;
    }

    return cantante->listaCanciones.eliminar(idCancion);
}

Cancion* CantanteService::obtenerCancion(int idCantante, int idCancion)
{
    Cantante* cantante = listaCantantes.obtenerPorId(idCantante);

    if (cantante == nullptr)
    {
        return nullptr;
    }

    return cantante->listaCanciones.obtenerPorId(idCancion);
}