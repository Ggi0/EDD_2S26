

#include "cantante/cantante.h"
#include "cancion/cancion.h"
#include "lista_circular/lista_circular.h"
#include <iostream>

using namespace std;

int main() {
    ListaCircular listaCantantes;

    //  Cantante 1 
    Cantante c1(1, "Bad Bunny", "Reggaeton");

    listaCantantes.insertar(c1);

    // Cantante 2 
    Cantante c2(2, "Daft Punk", "Electronica");
    c2.agregarCancion(Cancion(201, "One More Time", 320));
    c2.agregarCancion(Cancion(202, "Harder Better Faster Stronger", 224));
    c2.agregarCancion(Cancion(203, "Get Lucky", 369));

    listaCantantes.insertar(c2);

    //  Cantante 3 
    Cantante c3(3, "Adele", "Pop/Soul");
    c3.agregarCancion(Cancion(301, "Someone Like You", 285));
    c3.agregarCancion(Cancion(302, "Someone Like You", 285));
    c3.agregarCancion(Cancion(303, "Someone Like You", 285));
    c3.agregarCancion(Cancion(304, "Someone Like You", 285));
    c3.agregarCancion(Cancion(305, "Someone Like You", 285));

    listaCantantes.insertar(c3);

    //  Cantante 4 
    Cantante c4(4, "Metallica", "Metal");

    listaCantantes.insertar(c4);

    // cantate 5
    Cantante c5(5, "Cantante5", "salsa");
    listaCantantes.insertar(c5);



    // 4) Reporte grafico combinado =
    listaCantantes.graficar("lista_circular_cantantes");

    return 0;
}