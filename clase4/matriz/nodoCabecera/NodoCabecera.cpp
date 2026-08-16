#include "NodoCabecera.h"

NodoCabecera::NodoCabecera(int indice, const std::string& etiqueta) {
    this->indice = indice;
    this->etiqueta = etiqueta;

    siguiente = nullptr;
    anterior = nullptr;
    acceso = nullptr; // fila/columna nace vacia
}