#include <iostream>
#include "avl/avl.h"
using namespace std;

int main() {
    AVL arbol;


    int valores[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 65, 5, 15, 90, 85, 95};
    int n = sizeof(valores) / sizeof(valores[0]);
    for (int i = 0; i < n; i++) {
        arbol.insertar(valores[i]);
    }

    // Intentar insertar un duplicado a propósito
    arbol.insertar(30);

    // recorridos
    arbol.inOrden();    
    arbol.preOrden();
    arbol.postOrden();

    // imprimir por niveles
    arbol.imprimirPorNiveles();

    // datos del arbol
    cout << "Altura:        " << arbol.altura() << endl;
    cout << "Total nodos:   " << arbol.contarNodos() << endl;
    cout << "Total hojas:   " << arbol.contarHojas() << endl;

    cout << "\n  Busquaar \n";
    int aBuscar[] = {40, 99};
    for (int v : aBuscar) {
        cout << "¿Existe " << v << "? "
             << (arbol.buscar(v) ? "Sí" : "No") << endl;
    }

    // Graficamos el árbol ya balanceado con todas las inserciones.
    arbol.graficar("avl_ejemplo_1_insertado");

    // Eliminar 10 (nodo hoja, sin hijos)
    arbol.eliminar(10);
    arbol.inOrden();

    // Eliminar 20 (nodo con un solo hijo)
    arbol.eliminar(20);
    arbol.inOrden();

    // Eliminar 30 (nodo con dos hijos)
    arbol.eliminar(30);
    arbol.inOrden();

    // datos que no existen eliminar
    arbol.eliminar(999);

    // despue2s de eliminar
    arbol.imprimirPorNiveles();

    // Segunda gráfica, ya después de las eliminaciones/rebalanceos.
    arbol.graficar("avl_ejemplo_2_final");

    return 0;
}