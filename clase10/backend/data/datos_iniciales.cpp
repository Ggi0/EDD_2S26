#include "datos_iniciales.h"

void cargarDatosIniciales(
    CantanteService& service
)
{
    Cantante c1(
        1,
        "Bad Bunny",
        "Reggaeton"
    );

    service.agregarCantante(c1);


    Cantante c2(
        2,
        "Daft Punk",
        "Electronica"
    );

    c2.agregarCancion(
        Cancion(
            201,
            "One More Time",
            320
        )
    );

    c2.agregarCancion(
        Cancion(
            202,
            "Harder Better Faster Stronger",
            224
        )
    );

    c2.agregarCancion(
        Cancion(
            203,
            "Get Lucky",
            369
        )
    );

    service.agregarCantante(c2);


    Cantante c3(
        3,
        "Adele",
        "Pop/Soul"
    );

    c3.agregarCancion(
        Cancion(
            301,
            "Someone Like You",
            285
        )
    );

    c3.agregarCancion(
        Cancion(
            302,
            "Someone Like You",
            285
        )
    );

    c3.agregarCancion(
        Cancion(
            303,
            "Someone Like You",
            285
        )
    );

    c3.agregarCancion(
        Cancion(
            304,
            "Someone Like You",
            285
        )
    );

    c3.agregarCancion(
        Cancion(
            305,
            "Someone Like You",
            285
        )
    );

    service.agregarCantante(c3);


    Cantante c4(
        4,
        "Metallica",
        "Metal"
    );

    service.agregarCantante(c4);


    Cantante c5(
        5,
        "Cantante5",
        "Salsa"
    );

    service.agregarCantante(c5);
}