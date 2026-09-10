#ifndef NODO_H
#define NODO_H

#include "../Claves/Clave.h"
#include "../Hijos/Hijo.h"

/*

   - Una lista enlazada de Claves  K1 -> K2 -> ... -> Kk
   - Una lista enlazada de Hijos   C0 -> C1 -> ... -> Ck  [si no es hoja]
 

       C0     K1      C1       K2     C2      K3     C3
     (hijo) (clave) (hijo)  (clave) (hijo) (clave) (hijo)
 
  El hijo en la posicion i (0-based) contiene TODAS las claves menores
  que la clave en la posicion i (0-based tambien) 

  y mayores que la clave en la posicion i-1. Dicho de otro modo: 
   el hijo i queda "entre" la clave i-1 y la clave i.
 
 */
class Nodo {
public:
    Clave* primeraClave;   // Cabeza de la lista enlazada de claves
    Hijo*  primerHijo;     // Cabeza de la lista enlazada de hijos
    Nodo*  padre;          // Puntero al nodo padre (nullptr si es la raiz)
    bool   esHoja;         // true si el nodo no tiene hijos
    int    numClaves;      // Cuantas claves tiene actualmente el nodo
    int    numHijos;       // Cuantos hijos tiene actualmente el nodo

    Nodo(bool esHoja);
    ~Nodo();

    // para las CLAVES 

    // Devuelve el valor de la clave en la posicion "indice" (0-based)
    int obtenerClave(int indice) const;

    // Inserta una nueva clave con el valor indicado en la posicion dada, enlazandola en el lugar correcto de la lista
    void insertarClaveEnPosicion(int valor, int posicion);

    // Elimina la clave en la posicion indicada
    int eliminarClaveEnPosicion(int posicion);


    int buscarPosicion(int valor, bool &encontrada) const;

    // para los HIJOS 

    Nodo* obtenerHijo(int indice) const;
    void insertarHijoEnPosicion(Nodo* nodo, int posicion);
    Nodo* eliminarHijoEnPosicion(int posicion);

    void imprimirClaves() const;
};

#endif
