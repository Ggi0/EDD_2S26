// ============================================================================
// linked_list.cpp
// ----------------------------------------------------------------------------
// Implementación de la clase ListaEnlazada declarada en linked_list.h.
// Aquí está el "cómo" de cada método: la lógica real de la lista.
// ============================================================================

#include "linked_list.h"
#include <iostream>
#include <fstream>   // Para escribir el archivo .dot a disco
#include <cstdlib>   // Para system(), que nos permite ejecutar el comando
                     // "dot" de Graphviz desde C++

    using namespace std;

    ListaEnlazada::ListaEnlazada() {
        cabeza = nullptr;
        tamanio = 0;
    }
    
    
    ListaEnlazada::~ListaEnlazada(){
        Nodo* actual = cabeza;
    
        while (actual != nullptr){
            Nodo* siguienteNodo = actual->siguiente;
    
            delete actual;
            actual = siguienteNodo;
        }
        cabeza = nullptr;
    }
    
    
    void ListaEnlazada::insertar(int valor){
        Nodo* nuevo = new Nodo(valor);
        nuevo->siguiente = cabeza; // El nuevo nodo apunta a lo que antes era la cabeza (aunque sea nullptr si la lista estaba vacía).
        
        cabeza = nuevo;  // El nuevo nodo pasa a ser la cabeza.           
        tamanio++;
    }
    
    
    void ListaEnlazada::imprimir(){
        Nodo* actual = cabeza;
    
        while (actual != nullptr){
            cout << actual->dato << " --> ";
            actual = actual->siguiente;
        }
        cout << "nullptr\n" << endl;
    }
    
    
    bool ListaEnlazada::eliminar(int valor){
    
        if (cabeza == nullptr){
            return false; // La lista está vacía, no hay nada que eliminar.
        }
    
        if (cabeza->dato == valor){
            Nodo* temp = cabeza;
            cabeza = cabeza->siguiente; 
            delete temp;
            return true;
        }
    
        Nodo* anterior = cabeza;
        Nodo* actual = cabeza->siguiente;
    
        while (actual != nullptr) {
            if(actual->dato == valor){
                anterior->siguiente = actual->siguiente; 
                delete actual;
                tamanio--;
                return true;
            }
    
            anterior = actual;
            actual = actual->siguiente;
        }
    
        return false; // No se encontró el valor en la lista.
    }
    
    
    bool ListaEnlazada::buscar(int valor) {
        Nodo* actual = cabeza;
    
        while (actual != nullptr){
            if (actual->dato == valor){
                cout<< "valor encontrado!" << endl;
                return true;
            }
            actual = actual->siguiente;
        }
    
        return false;
    }
    
    int ListaEnlazada::obtenerTamanio(){
        return tamanio;
    }
    
    
    bool ListaEnlazada::estaVacia(){
        cout << "tamaño de la lista: " << tamanio << endl;
        if (cabeza == nullptr){
            cout << " estaaaaa vaciaaaaa" << endl;
            return true;
        }else{
            cout << " no estaaaaa vaciaaaaa" << endl;
            return false;
        }
        return (cabeza == nullptr);
    }

//                  graficar
// Genera un archivo .dot describiendo el grafo y luego llama al comando
// "dot" (de Graphviz) para convertirlo en una imagen .png, todo dentro de
// clase1/linked_list/reporte.

// Cada nodo se dibuja como una caja dividida en dos partes: el dato y el
// puntero "siguiente". Un pequeño nodo "cabeza" en forma de punto apunta
// al primer nodo, igual que en un diagrama de pizarrón.
void ListaEnlazada::graficar(const string& nombreArchivo) const {
    
    // Carpeta donde se guardan el .dot y el .png generados. Coincide con
    // la ruta pedida: clase1/linked_list/reporte
    const string carpeta = "linked_list/reporte";
    const string rutaDot = carpeta + "/" + nombreArchivo + ".dot";
    const string rutaPng = carpeta + "/" + nombreArchivo + ".png";

    // 1) Construimos el contenido del archivo .dot en un string.
    ofstream archivo(rutaDot);
    if (!archivo.is_open()) {
        cerr << "No se pudo crear el archivo " << rutaDot << endl;
        return;
    }

    archivo << "digraph ListaEnlazada {\n";
    // rankdir=LR hace que el grafo se dibuje de izquierda a derecha,
    // como normalmente dibujamos una lista enlazada en el pizarrón.
    archivo << "    rankdir=LR;\n";
    archivo << "    node [shape=record, fontname=\"Helvetica\"];\n";
    archivo << "    edge [fontname=\"Helvetica\"];\n\n";

    if (cabeza == nullptr) {
        // Lista vacía: solo dibujamos un nodo indicando que está vacía.
        archivo << "    vacio [label=\"Lista vacia\", shape=plaintext];\n";
    } else {
        // Nodo "cabeza" pequeño (un punto) que apunta al primer nodo real,
        // para dejar claro cuál es el punto de entrada de la lista.
        archivo << "    cabeza [shape=point];\n";
        archivo << "    cabeza -> nodo0;\n\n";

        Nodo* actual = cabeza;
        int indice = 0;
        while (actual != nullptr) {
            // Cada nodo se dibuja como una caja tipo "record" con dos
            // celdas: el dato guardado, y el puntero "siguiente".
            // Si es el último nodo, el puntero se etiqueta como NULL.
            archivo << "    nodo" << indice
                    << " [label=\"{ " << actual->dato << " | <sig> * }\"];\n";

            if (actual->siguiente != nullptr) {
                // Flecha desde el campo "siguiente" de este nodo hacia
                // el siguiente nodo del grafo.
                archivo << "    nodo" << indice << ":sig -> nodo" << (indice + 1) << ";\n";
            } else {
                // Último nodo: dibujamos un pequeño nodo "NULL" al final.
                archivo << "    null" << indice << " [label=\"NULL\", shape=plaintext];\n";
                archivo << "    nodo" << indice << ":sig -> null" << indice << ";\n";
            }

            actual = actual->siguiente;
            indice++;
        }
    }

    archivo << "}\n";
    archivo.close();

    // 2) Ejecutamos el comando "dot" para convertir el .dot en .png.
    //    Equivale a correr en la terminal:
    //        dot -Tpng reporte/lista.dot -o reporte/lista.png
    string comando = "dot -Tpng " + rutaDot + " -o " + rutaPng;
    int resultado = system(comando.c_str());

    if (resultado == 0) {
        cout << "Imagen generada en: " << rutaPng << endl;
    } else {
        cerr << "Ocurrio un error al ejecutar Graphviz (dot). "
             << "Verifica que este instalado." << endl;
    }
}