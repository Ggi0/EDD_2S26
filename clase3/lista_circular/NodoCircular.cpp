#include "NodoCircular.h"

NodoCircular::NodoCircular(const Cantante& valor) {
    dato = valor;
    siguiente = nullptr;
}