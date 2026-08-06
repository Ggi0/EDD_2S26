#ifndef LISTA_CIRCULAR_H
#define LISTA_CIRCULAR_H

#include "NodoCircular.h"
#include "../cantante/cantante.h"
#include <string>


class ListaCircular {
private:
    NodoCircular* cabeza;
    NodoCircular* ultimo;   // ultimo->siguiente siempre es cabeza.
    int tamanio;

public:
    ListaCircular();
    ~ListaCircular();

    void insertar(const Cantante& valor);  // Inserta al final
    bool eliminar(int id);  // Elimina por id

    bool buscar(int id) const;
    Cantante* obtenerPorId(int id) const;
    int obtenerTamanio() const;
    bool estaVacia() const;

    NodoCircular* getCabeza() const;

    void imprimir() const;  // cabeza -> ... -> (vuelta a cabeza)

    void graficar(const std::string& nombreArchivo = "lista_circular") const;
};

#endif // LISTA_CIRCULAR_H