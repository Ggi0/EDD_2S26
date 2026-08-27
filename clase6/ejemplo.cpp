
#include <iostream>
#include "bst/bst.h"
using namespace std;

int main() {
    BST arbol;

    cout << " 1) Insertando valores \n";
    int valores[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 65};
    int n = sizeof(valores) / sizeof(valores[0]);

    for (int i = 0; i < n; i++) {
        arbol.insertar(valores[i]);
    }
    // Intentar insertar un duplicado a propósito
    arbol.insertar(30);

    cout << "\n 2) Recorridos \n";
    arbol.inOrden();    // debe salir ordenado de menor a mayor
    arbol.preOrden();
    arbol.postOrden();

    cout << "\n 3) Estructura por niveles \n";
    arbol.imprimirPorNiveles();

    cout << "\n 4) Datos del árbol \n";
    cout << "Altura:        " << arbol.altura() << endl;
    cout << "Total nodos:   " << arbol.contarNodos() << endl;
    cout << "Total hojas:   " << arbol.contarHojas() << endl;

    cout << "\n 5) Búsquedas \n";
    int aBuscar[] = {40, 99};
    for (int v : aBuscar) {
        cout << "¿Existe " << v << "? "
             << (arbol.buscar(v) ? "Sí" : "No") << endl;
    }

    cout << "\n 6) Eliminaciones (los 3 casos clásicos) \n";

    cout << "-> Eliminar 10 (nodo hoja, sin hijos)\n";
    arbol.eliminar(10);
    arbol.inOrden();

    cout << "-> Eliminar 20 (nodo con un solo hijo: 25)\n";
    arbol.eliminar(20);
    arbol.inOrden();

    cout << "-> Eliminar 30 (nodo con dos hijos: 25 y 40)\n";
    arbol.eliminar(30);
    arbol.inOrden();

    cout << "-> Eliminar 999 (no existe)\n";
    arbol.eliminar(999);

    cout << "\n 7) Estado final \n";
    arbol.imprimirPorNiveles();
    cout << "Altura final: " << arbol.altura() << endl;


    arbol.graficar("bst_ejemplo");


    // El destructor de BST se encarga de liberar toda la memoria
    // automáticamente cuando "arbol" sale de scope al terminar main().
    return 0;
}