

#include "doubly_linked_list/doubly_linked_list.h"
#include "pelicula/pelicula.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>

using namespace std;

// BUSQUEDA Lineal (secuencial), de cabeza a cola.
Pelicula* busquedaLineal(const ListaDoble& lista, int id) {
    Nodo* actual = lista.obtenerCabeza();
    while (actual != nullptr) {
        if (actual->dato.id == id) return &(actual->dato);
        actual = actual->siguiente;
    }
    return nullptr;
}

// BUSQUEDA Lineal bidireccional.
Pelicula* busquedaLinealBidireccional(const ListaDoble& lista, int id) {
    Nodo* izquierda = lista.obtenerCabeza();
    Nodo* derecha = lista.obtenerCola();

    while (izquierda != nullptr && derecha != nullptr) {
        if (izquierda->dato.id == id) return &(izquierda->dato);
        if (derecha->dato.id == id) return &(derecha->dato);

        // Si ambos punteros se cruzaron o se encontraron, ya se
        // recorrio toda la lista sin encontrar el id.
        if (izquierda == derecha || izquierda->siguiente == derecha) break;

        izquierda = izquierda->siguiente;
        derecha = derecha->anterior;
    }
    return nullptr;
}

// BUSQUEDA Binaria
Pelicula* busquedaBinaria(const ListaDoble& lista, int id) {
    vector<Nodo*> nodos;
    for (Nodo* actual = lista.obtenerCabeza(); actual != nullptr; actual = actual->siguiente) {
        nodos.push_back(actual);
    }

    int bajo = 0;
    int alto = static_cast<int>(nodos.size()) - 1;

    while (bajo <= alto) {
        int medio = bajo + (alto - bajo) / 2;
        int idMedio = nodos[medio]->dato.id;

        if (idMedio == id) return &(nodos[medio]->dato);
        if (idMedio < id) bajo = medio + 1;
        else alto = medio - 1;
    }
    return nullptr;
}

// BUSQUEDA Por saltos
Pelicula* busquedaPorSaltos(const ListaDoble& lista, int id) {
    vector<Nodo*> nodos;
    for (Nodo* actual = lista.obtenerCabeza(); actual != nullptr; actual = actual->siguiente) {
        nodos.push_back(actual);
    }

    int n = static_cast<int>(nodos.size());
    if (n == 0) return nullptr;

    int tamanioSalto = static_cast<int>(sqrt(static_cast<double>(n)));
    if (tamanioSalto < 1) tamanioSalto = 1;

    int actualBloque = 0;
    int siguienteBloque = tamanioSalto;

    // Saltamos de bloque en bloque mientras el id buscado sea mayor
    // que el id al final del bloque actual.
    while (siguienteBloque < n && nodos[siguienteBloque - 1]->dato.id < id) {
        actualBloque = siguienteBloque;
        siguienteBloque += tamanioSalto;
    }

    int limite = (siguienteBloque < n) ? siguienteBloque : n;

    // Busqueda lineal dentro del bloque encontrado.
    for (int i = actualBloque; i < limite; i++) {
        if (nodos[i]->dato.id == id) return &(nodos[i]->dato);
    }
    return nullptr;
}


void mostrarResultado(const string& nombreAlgoritmo, Pelicula* resultado) {
    cout << nombreAlgoritmo << ": ";
    if (resultado != nullptr) {
        resultado->mostrarInformacion();
        cout << endl;
    } else {
        cout << "no encontrado" << endl;
    }
}

void cargarPeliculasDeEjemplo(ListaDoble& lista) {
    lista.insertarAlFinal(Pelicula(15, "Interstellar", 2014, "Ciencia ficcion"));
    lista.insertarAlFinal(Pelicula(3, "El Padrino", 1972, "Drama"));
    lista.insertarAlFinal(Pelicula(22, "Coco", 2017, "Animacion"));
    lista.insertarAlFinal(Pelicula(8, "Whiplash", 2014, "Drama"));
    lista.insertarAlFinal(Pelicula(1, "Matrix", 1999, "Ciencia ficcion"));
    lista.insertarAlFinal(Pelicula(19, "Parasite", 2019, "Thriller"));
    lista.insertarAlFinal(Pelicula(11, "Amelie", 2001, "Comedia"));
}

int main() {
    //                          ORDENAMIENTO
    cout << "\n\n Lista original " << endl;
    ListaDoble listaOriginal;
    cargarPeliculasDeEjemplo(listaOriginal);
    listaOriginal.imprimir();

    cout << "\n  ordenarBurbuja()" << endl;
    ListaDoble listaBurbuja;
    cargarPeliculasDeEjemplo(listaBurbuja);
    listaBurbuja.ordenarBurbuja();
    listaBurbuja.imprimir();

    cout << "\n ordenarInsercion() " << endl;
    ListaDoble listaInsercion;
    cargarPeliculasDeEjemplo(listaInsercion);
    listaInsercion.ordenarInsercion();
    listaInsercion.imprimir();

    cout << "\n ordenarSeleccion() " << endl;
    ListaDoble listaSeleccion;
    cargarPeliculasDeEjemplo(listaSeleccion);
    listaSeleccion.ordenarSeleccion();
    listaSeleccion.imprimir();

    cout << "\n ordenarQuickSort() " << endl;
    ListaDoble listaQuickSort;
    cargarPeliculasDeEjemplo(listaQuickSort);
    listaQuickSort.ordenarQuickSort();
    listaQuickSort.imprimir();

    //  BUSQUEDA

    int idBuscado = 19; // Parasite

    cout << "\n Busquedas del id " << idBuscado << " (sobre la lista ordenada) " << endl;
    mostrarResultado("Busqueda Lineal", busquedaLineal(listaQuickSort, idBuscado));
    mostrarResultado("Busqueda Lineal Bidireccional", busquedaLinealBidireccional(listaQuickSort, idBuscado));
    mostrarResultado("Busqueda Binaria", busquedaBinaria(listaQuickSort, idBuscado));
    mostrarResultado("Busqueda por Saltos", busquedaPorSaltos(listaQuickSort, idBuscado));

    int idInexistente = 99;
    cout << "\n Busquedas del id " << idInexistente << " (no existe) " << endl;
    mostrarResultado("Busqueda Lineal", busquedaLineal(listaQuickSort, idInexistente));
    mostrarResultado("Busqueda Binaria", busquedaBinaria(listaQuickSort, idInexistente));


    // RECORDATORIO DE CAMBIAR LA DIRECCION 
    // para que el reporte se haga de forma correrta
    // si se ejecuta desde QT usa la otra ruta
    // si se ejecuta este archivo usar las rutas simples
    listaOriginal.graficar("lista_doble_final");
    listaBurbuja.graficar("lista_doble_burbuja");

    return 0;
}