#include <iostream>
#include "arbolB/ArbolB.h"

using namespace std;

int main() {
    ArbolB arbol(3);

    // Insertamos algunos valores
    int valores[] = {5, 10, 15, 20, 25, 30, 3, 7, 35};
    for (int v : valores) {
        arbol.insertar(v);
    }

    cout << "Arbol grado 3 tras insertar:" << endl;
    arbol.imprimirPorNiveles();
    arbol.graficar("ejemplo1_insertado.dot");

    // Buscamos un par de valores
    cout << "Buscar 15: " << (arbol.buscar(15) ? "ENCONTRADO" : "NO ENCONTRADO") << endl;
    cout << "Buscar 100: " << (arbol.buscar(100) ? "ENCONTRADO" : "NO ENCONTRADO") << endl;

    // Eliminamos algunos valores
    arbol.eliminar(35);
    arbol.eliminar(5);
    arbol.eliminar(10);

    cout << "\nArbol grado 3 tras eliminar:" << endl;
    arbol.imprimirPorNiveles();
    arbol.graficar("ejemplo1_eliminado.dot");

    return 0;
}
