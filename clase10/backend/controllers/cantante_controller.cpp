#include "cantante_controller.h"
#include "../utils/json_utils.h"

void CantanteController::registrarRutas( crow::SimpleApp& app, CantanteService& service )
{
    
    // GET /api/cantantes
    // Obtener todos los cantantes
    
    CROW_ROUTE(app, "/api/cantantes")
    .methods(crow::HTTPMethod::GET)
    ([&service]()
    {
        crow::json::wvalue respuesta;

        crow::json::wvalue cantantes;

        NodoCircular* actual =
            service.obtenerLista().getCabeza();

        int posicion = 0;

        if (actual != nullptr)
        {
            NodoCircular* inicio = actual;

            do
            {
                cantantes[posicion++] =
                    JsonUtils::cantanteToJson(actual->dato);

                actual = actual->siguiente;

            } while (actual != inicio);
        }

        respuesta["cantantes"] = std::move(cantantes);
        respuesta["cantidad"] =
            service.obtenerLista().obtenerTamanio();

        return crow::response(200, respuesta);
    });


    
    // GET /api/cantantes/<id>
    // Obtener un cantante
    

    CROW_ROUTE(app, "/api/cantantes/<int>")
    .methods(crow::HTTPMethod::GET)
    ([&service](int id)
    {
        Cantante* cantante =
            service.obtenerCantante(id);

        if (cantante == nullptr)
        {
            crow::json::wvalue error;

            error["mensaje"] = "Cantante no encontrado";

            return crow::response(404, error);
        }

        return crow::response(
            200,
            JsonUtils::cantanteToJson(*cantante)
        );
    });


    
    // POST /api/cantantes
    // Crear cantante
    CROW_ROUTE(app, "/api/cantantes")
    .methods(crow::HTTPMethod::POST)
    ([&service](const crow::request& req)
    {
        auto body =
            crow::json::load(req.body);

        if (!body)
        {
            crow::json::wvalue error;

            error["mensaje"] =
                "JSON invalido";

            return crow::response(400, error);
        }

        if (!body.has("id") ||
            !body.has("nombre") ||
            !body.has("genero"))
        {
            crow::json::wvalue error;

            error["mensaje"] =
                "Faltan campos requeridos";

            return crow::response(400, error);
        }

        int id = body["id"].i();
        std::string nombre = body["nombre"].s();
        std::string genero = body["genero"].s();

        Cantante cantante(
            id,
            nombre,
            genero
        );

        if (!service.agregarCantante(cantante))
        {
            crow::json::wvalue error;

            error["mensaje"] =
                "Ya existe un cantante con ese ID";

            return crow::response(409, error);
        }

        crow::json::wvalue respuesta;

        respuesta["mensaje"] =
            "Cantante creado correctamente";

        respuesta["cantante"] =
            JsonUtils::cantanteToJson(cantante);

        return crow::response(201, respuesta);
    });


    
    // DELETE /api/cantantes/<id>
    // Eliminar cantante
    CROW_ROUTE(app, "/api/cantantes/<int>")
    .methods(crow::HTTPMethod::DELETE)
    ([&service](int id)
    {
        if (!service.eliminarCantante(id))
        {
            crow::json::wvalue error;

            error["mensaje"] =
                "Cantante no encontrado";

            return crow::response(404, error);
        }

        crow::json::wvalue respuesta;

        respuesta["mensaje"] =
            "Cantante eliminado correctamente";

        return crow::response(200, respuesta);
    });


    
    // POST /api/cantantes/<id>/canciones
    // Agregar canción a un cantante
    CROW_ROUTE(
        app,
        "/api/cantantes/<int>/canciones"
    )
    .methods(crow::HTTPMethod::POST)
    ([&service](const crow::request& req, int idCantante)
    {
        auto body =
            crow::json::load(req.body);

        if (!body)
        {
            crow::json::wvalue error;

            error["mensaje"] =
                "JSON invalido";

            return crow::response(400, error);
        }

        if (!body.has("id") ||
            !body.has("titulo") ||
            !body.has("duracion"))
        {
            crow::json::wvalue error;

            error["mensaje"] =
                "Faltan campos requeridos";

            return crow::response(400, error);
        }

        Cancion cancion(
            body["id"].i(),
            body["titulo"].s(),
            body["duracion"].i()
        );

        if (!service.agregarCancion(
                idCantante,
                cancion))
        {
            crow::json::wvalue error;

            error["mensaje"] =
                "No se pudo agregar la canción. "
                "Verifique que el cantante exista "
                "y que el ID de la canción no esté repetido.";

            return crow::response(409, error);
        }

        crow::json::wvalue respuesta;

        respuesta["mensaje"] =
            "Canción agregada correctamente";

        respuesta["cancion"] =
            JsonUtils::cancionToJson(cancion);

        return crow::response(201, respuesta);
    });


    
    // GET /api/cantantes/<id>/canciones
    // Obtener canciones de un cantante
    CROW_ROUTE(
        app,
        "/api/cantantes/<int>/canciones"
    )
    .methods(crow::HTTPMethod::GET)
    ([&service](int idCantante)
    {
        Cantante* cantante =
            service.obtenerCantante(idCantante);

        if (cantante == nullptr)
        {
            crow::json::wvalue error;

            error["mensaje"] =
                "Cantante no encontrado";

            return crow::response(404, error);
        }

        crow::json::wvalue respuesta;

        crow::json::wvalue canciones;

        Nodo* actual =
            cantante->listaCanciones.getCabeza();

        int posicion = 0;

        while (actual != nullptr)
        {
            canciones[posicion++] =
                JsonUtils::cancionToJson(actual->dato);

            actual = actual->siguiente;
        }

        respuesta["cantante_id"] =
            cantante->id;

        respuesta["cantante"] =
            cantante->nombre;

        respuesta["canciones"] =
            std::move(canciones);

        return crow::response(200, respuesta);
    });


    
    // DELETE /api/cantantes/<id>/canciones/<idCancion>
    // Eliminar canción
    CROW_ROUTE(
        app,
        "/api/cantantes/<int>/canciones/<int>"
    )
    .methods(crow::HTTPMethod::DELETE)
    ([&service](int idCantante, int idCancion)
    {
        if (!service.eliminarCancion(
                idCantante,
                idCancion))
        {
            crow::json::wvalue error;

            error["mensaje"] =
                "No se encontró el cantante "
                "o la canción";

            return crow::response(404, error);
        }

        crow::json::wvalue respuesta;

        respuesta["mensaje"] =
            "Canción eliminada correctamente";

        return crow::response(200, respuesta);
    });
}