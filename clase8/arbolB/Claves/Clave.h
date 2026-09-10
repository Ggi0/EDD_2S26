#ifndef CLAVE_H
#define CLAVE_H


class Clave {
    public:
        int valor;          // El dato almacenado (el int)
        Clave* siguiente;   // Puntero a la siguiente clave dentro del mismo nodo
    
        Clave(int valor);
        ~Clave();
    };



#endif