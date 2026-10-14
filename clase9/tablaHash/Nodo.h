#ifndef NODO_H
#define NODO_H

#include <string>
using namespace std;

class Nodo {
public:
    string clave;       
    string valor;   

    int indexBucket;     
    bool esColision;   

    Nodo* siguiente;  

    // Constructor: recibe la clave, el valor, el índice de su bucket y si es colisión.
    Nodo(const string& clave, const string& valor, int indexBucket, bool esColision = false);
};

#endif // NODO_H
