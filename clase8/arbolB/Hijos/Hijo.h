#ifndef HIJO_H
#define HIJO_H

// Declaracion adelantada Hijo necesita apuntar a Nodo, pero Nodo tambien necesita usar Hijo (dependencia circular).
class Nodo;

/*

Representa UN puntero a un nodo hijo dentro de un nodo padre del arbol B.

 los hijos de un nodo se guardan como una LISTA ENLAZADA de objetos Hijo. 
 
 El puntero "siguiente" conecta un hijo con el siguiente hijo (de izquierda a derecha) DENTRO DEL MISMO nodo padre.


         Hijo(C0) -> Hijo(C1) -> Hijo(C2) -> ... -> Hijo(Ck) -> nullptr
 */
class Hijo {
public:
    Nodo* apuntador;   // Puntero real al nodo hijo (raiz de ese subarbol) o sea el nodo que esta abajo del actual.
    Hijo* siguiente;   // Puntero al siguiente hijo

    Hijo(Nodo* apuntador);
    ~Hijo();
};

#endif
