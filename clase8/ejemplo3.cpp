#include <iostream>
#include "arbolB/ArbolB.h"

using namespace std;

int main() {
    ArbolB arbol(5);

    // Insertamos algunos valores
    int valores[] = {50, 20, 70, 10, 30, 60, 80, 5, 15, 25,
                      35, 55, 65, 75, 85, 1, 3, 45, 90};
    for (int v : valores) {
        arbol.insertar(v);
    }

    cout << "Arbol grado 5 tras insertar:" << endl;
    arbol.imprimirPorNiveles();
    arbol.graficar("ejemplo3_insertado.dot");

    // Buscamos un par de valores
    cout << "Buscar 65: " << (arbol.buscar(65) ? "ENCONTRADO" : "NO ENCONTRADO") << endl;
    cout << "Buscar 500: " << (arbol.buscar(500) ? "ENCONTRADO" : "NO ENCONTRADO") << endl;

    // Eliminamos algunos valores
    arbol.eliminar(1);
    arbol.eliminar(3);
    arbol.eliminar(90);
    arbol.eliminar(85);

    cout << "\nArbol grado 5 tras eliminar:" << endl;
    arbol.imprimirPorNiveles();
    arbol.graficar("ejemplo3_eliminado.dot");

    return 0;
}
