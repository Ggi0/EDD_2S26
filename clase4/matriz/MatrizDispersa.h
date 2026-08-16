#ifndef MATRIZDISPERSA_H
#define MATRIZDISPERSA_H


#include <string>
#include "nodoCabecera/NodoCabecera.h"
#include "nodoDato/NodoDato.h"
#include "../pelicula/pelicula.h"

#include <vector> // esto es solo para la interfaz.

class MatrizDispersa {
    private:
        NodoCabecera* cabFilas;  // primer nodo de la lista de cabeceras de FILA
        NodoCabecera* cabColumnas;  // primer nodo de la lista de cabeceras de COLUMNA
     
        // Busca una cabecera existente con ese indice (sin crearla).
        // Retorna nullptr si no existe.
        NodoCabecera* buscarCabecera(NodoCabecera* lista, int indice) const;
     
        // Busca la cabecera con 'indice' dentro de 'lista'. Si no existe,
        // la crea, la INSERTA ORDENADA (por indice ascendente) y la retorna.
        // 'lista' se pasa por referencia porque puede cambiar el primer nodo.
        NodoCabecera* obtenerOCrearCabecera(    NodoCabecera*& lista, 
                                                int indice,
                                                const std::string& etiqueta
                                            );
     
        // Quita una cabecera de su lista doblemente enlazada (cuando su
        // fila/columna se queda sin datos) y libera su memoria.
        void desenlazarCabecera(NodoCabecera*& lista, NodoCabecera* cab);
     
    public:
        MatrizDispersa();
        ~MatrizDispersa(); // libera TODOS los NodoDato y NodoCabecera (y las Peliculas)
     
        // Fija/actualiza el nombre legible de una fila o columna sin
        // necesidad de insertar un dato todavia. Si la cabecera no existe, la crea vacia.
        void definirEtiquetaFila(int indice, const std::string& etiqueta);
        void definirEtiquetaColumna(int indice, const std::string& etiqueta);
     
        // Inserta una pelicula en (fila, columna). Crea las cabeceras que
        // hagan falta. Si ya habia un dato ahi, se libera y se reemplaza.
        void insertar(int fila, int columna, Pelicula* p);
     
        // Busca el NodoDato en (fila, columna). Retorna nullptr si no existe.
        NodoDato* buscar(int fila, int columna) const;
     
        // Elimina el dato en (fila, columna), desenlazandolo de su fila y columna. 
        // Si la fila o columna queda vacia, tambien elimina su cabecera (la matriz se "encoge" dinamicamente). 
        // Retorna true si elimino algo, false si no habia nada en esa posicion.
        bool eliminar(int fila, int columna);
     
        bool esVacia() const;

        // esto es solo para la interfaz.
        std::vector<std::string> obtenerDirectores() const;
        std::vector<std::string> obtenerGeneros() const;
        std::string obtenerContenidoCelda(int fila, int columna) const;
     
        void mostrar() const; // imprime en consola
        std::string generarDOT() const;   // arma el texto DOT completo
        void exportarDOT(const std::string& archivoBase) const; // escribe .dot y corre 'dot' para el .png
    };
     


#endif