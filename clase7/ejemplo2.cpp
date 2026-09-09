#include <iostream>
#include "avl/avl.h"
using namespace std;

int main() {
    AVL arbol;


        arbol.insertar(80);
        arbol.insertar(75);
        arbol.insertar(50);

    arbol.graficar("avl_ejemplo2");

    return 0;
}