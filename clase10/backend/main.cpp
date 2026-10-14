#include "crow.h"

#include "controllers/cantante_controller.h"
#include "services/cantante_service.h"
#include "data/datos_iniciales.h"

int main()
{
    crow::SimpleApp app;

    CantanteService cantanteService;

    // Cargar información inicial
    //cargarDatosIniciales(cantanteService);

    // Registrar endpoints
    CantanteController::registrarRutas(
        app,
        cantanteService
    );

    app.port(18080)
       .multithreaded()
       .run();

    return 0;
}

