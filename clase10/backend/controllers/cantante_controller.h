
#ifndef CANTANTE_CONTROLLER_H
#define CANTANTE_CONTROLLER_H

#include "crow.h"
#include "../services/cantante_service.h"

class CantanteController
{
public:

    static void registrarRutas(
        crow::SimpleApp& app,
        CantanteService& service
    );
};

#endif