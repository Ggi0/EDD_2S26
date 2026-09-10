#include <iostream>
#include "arbolB/ArbolB.h"

using namespace std;

int main() {
    ArbolB arbol(4);

    // Insertamos algunos valores
    int valores[] = {40, 10, 20, 30, 50, 60, 70, 80, 90, 100, 15, 25};
    for (int v : valores) {
        arbol.insertar(v);
    }

    cout << "Arbol grado 4 tras insertar:" << endl;
    arbol.imprimirPorNiveles();
    arbol.graficar("ejemplo2_insertado.dot");

    // Buscamos un par de valores
    cout << "Buscar 60: " << (arbol.buscar(60) ? "ENCONTRADO" : "NO ENCONTRADO") << endl;
    cout << "Buscar 200: " << (arbol.buscar(200) ? "ENCONTRADO" : "NO ENCONTRADO") << endl;

    // Eliminamos algunos valores
    arbol.eliminar(100);
    arbol.eliminar(10);
    arbol.eliminar(40);

    cout << "\nArbol grado 4 tras eliminar:" << endl;
    arbol.imprimirPorNiveles();
    arbol.graficar("ejemplo2_eliminado.dot");

    return 0;
}
