#ifndef TABLA_HASH_H
#define TABLA_HASH_H

#include "ListaEnlazada.h"
#include <string>
using namespace std;


class TablaHash {
private:

    static const int NUM_BUCKETS = 10;

    // buckets[i] apunta a la lista enlazada que corresponde al indice de hash "i".
    ListaEnlazada* buckets[NUM_BUCKETS];

    // rango [0, NUM_BUCKETS - 1].
    int funcionHash(const string& clave) const;

public:
    TablaHash();  
    ~TablaHash();  

    // Inserta el par (clave, valor)
    void insertar(const string& clave, const string& valor);

    // Elimina la clave si existe
    bool eliminar(const string& clave);

    // Busca la clave. Si existe, copia su valor en "valorEncontrado"
    bool buscar(const string& clave, string& valorEncontrado) const;

    // Imprime en consola el contenido de cada bucket
    void imprimir() const;

    void graficar(const string& nombreArchivo) const;

    int obtenerNumBuckets() const;
};

#endif // TABLA_HASH_H
