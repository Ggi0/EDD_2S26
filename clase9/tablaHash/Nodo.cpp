#include "Nodo.h"

Nodo::Nodo(const string& clave, const string& valor, int indexBucket, bool esColision)
    : clave(clave),
      valor(valor),
      indexBucket(indexBucket),
      esColision(esColision),
      siguiente(nullptr) {
}
