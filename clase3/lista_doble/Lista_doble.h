#ifndef LISTA_DOBLE_H
#define LISTA_DOBLE_H


#include "Nodo.h"
#include "../cancion/cancion.h"

#include <string>
#include <fstream>


class ListaDoble {
    private:
        Nodo* cabeza;
        Nodo* cola;
        int tamanio;

    
    public:
        ListaDoble();
        ~ListaDoble();

        ListaDoble(const ListaDoble& otra);                // constructor de copia
        ListaDoble& operator=(const ListaDoble& otra);
    
    
        void insertarAlFinal(const Cancion& valor);  
        void insertarAlInicio(const Cancion& valor);  
        bool eliminar(int id);                       
    
    
        bool buscar(int id) const;  // Busqueda simple: solo dice si existe.
        Cancion* obtenerPorId(int id) const;   // Devuelve puntero al dato encontrado (o nullptr).
        int obtenerTamanio() const;
        bool estaVacia() const;
    
        // Getters usados por los algoritmos de ordenamiento/busqueda externos
        Nodo* getCabeza() const;
        Nodo* getCola() const;
    
        void imprimir() const;          // cabeza -> ... -> nullptr
        void imprimirReversa() const;   // cola -> ... -> nullptr
    
    
        void graficar(const std::string& nombreArchivo = "lista_doble") const;

        void graficarNodosEnFlujo(std::ofstream& archivo, const std::string& prefijo) const;

    };






#endif 