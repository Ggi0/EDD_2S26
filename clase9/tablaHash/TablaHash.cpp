#include "TablaHash.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;


TablaHash::TablaHash() {
    for (int i = 0; i < NUM_BUCKETS; i++) {
        buckets[i] = new ListaEnlazada();
    }
}


TablaHash::~TablaHash() {
    for (int i = 0; i < NUM_BUCKETS; i++) {
        delete buckets[i];
    }
}

int TablaHash::funcionHash(const string& clave) const {
    int suma = 0;
    for (char c : clave) {
        suma += static_cast<int>(c); // valor ASCII del caracter
    }
    return suma % NUM_BUCKETS;
}


// insertar(): calcula el índice con la función hash
void TablaHash::insertar(const string& clave, const string& valor) {
    int idx = funcionHash(clave);

    // Evitamos duplicar la misma clave.
    string valorExistente;
    if (buckets[idx]->buscar(clave, valorExistente)) {
        cout << "Aviso: la clave '" << clave << "' ya existe (valor actual: '"
             << valorExistente << "'). No se insertó de nuevo." << endl;
        return;
    }

    buckets[idx]->insertar(clave, valor, idx);
}


// eliminar(): calculamos el bucket con la MISMA función hash (siempre debe
// ser la misma, si no, nuca camos a encontrar los datos que insertamos) y le
// pedimos a ese bucket que elimine la clave.
bool TablaHash::eliminar(const string& clave) {
    int idx = funcionHash(clave);
    return buckets[idx]->eliminar(clave);
}


// buscar(): mismo principio que eliminar(): recalculamos el indice y
// delegamos la búsqueda al bucket correspondiente.
bool TablaHash::buscar(const string& clave, string& valorEncontrado) const {
    int idx = funcionHash(clave);
    return buckets[idx]->buscar(clave, valorEncontrado);
}


// imprimir(): recorre TODO el array de buckets e imprimri cada bucket
void TablaHash::imprimir() const {
    cout << " Estado de la Tabla Hash " << endl;
    for (int i = 0; i < NUM_BUCKETS; i++) {
        cout << "Bucket [" << i << "]: ";
        buckets[i]->imprimir();
        cout << endl;
    }
}

int TablaHash::obtenerNumBuckets() const {
    return NUM_BUCKETS;
}

void TablaHash::graficar(const string& nombreArchivo) const {
    const string carpeta = "tablaHash/reportes";
    const string rutaDot = carpeta + "/" + nombreArchivo + ".dot";
    const string rutaPng = carpeta + "/" + nombreArchivo + ".png";

    ofstream archivo(rutaDot);
    if (!archivo.is_open()) {
        cerr << "No se pudo crear el archivo: " << rutaDot << endl;
        return;
    }

    archivo << "digraph TablaHash {\n";
    archivo << "    rankdir=LR;\n";
    archivo << "    node [fontname=\"Helvetica\"];\n";
    archivo << "    edge [fontname=\"Helvetica\"];\n\n";

    // Recorremos el array de buckets
    for (int i = 0; i < NUM_BUCKETS; i++) {
        string idBucket = "bucket" + to_string(i);

        // Dibujamos el bucket como una caja gris con su numero de indice.
        archivo << "    " << idBucket
                << " [shape=box, style=filled, fillcolor=\"#D9D9D9\", "
                << "label=\"Bucket " << i << "\"];\n";

        Nodo* actual = buckets[i]->obtenerCabeza();

        if (actual == nullptr) {
            // Bucket vacio: no hay nada más que dibujar para este indice.
            continue;
        }

        string idAnterior = idBucket; // el primer enlace sale del bucket
        int contadorCadena = 0;

        // Recorremos la lista enlazada de este bucket (cabeza -> ... -> nullptr),
        while (actual != nullptr) {
            string idNodo = "n" + to_string(i) + "_" + to_string(contadorCadena);

            // Color: naranja si el nodo fue una colision, azul si no.
            string color = actual->esColision ? "#F4A261" : "#A8C8E6";

            archivo << "    " << idNodo
                    << " [shape=ellipse, style=filled, fillcolor=\"" << color << "\", "
                    << "label=\"" << actual->clave << "\\n" << actual->valor << "\"];\n";

  
            archivo << "    " << idAnterior << " -> " << idNodo;
            if (idAnterior != idBucket) {
                // Solo etiquetamos como "siguiente" las aristas entre nodos
                // (la arista bucket -> primer nodo no necesita esa etiqueta).
                archivo << " [label=\"siguiente\"]";
            }
            archivo << ";\n";

            idAnterior = idNodo;
            actual = actual->siguiente;
            contadorCadena++;
        }
    }

    archivo << "}\n";
    archivo.close();

    // Invocamos a Graphviz para convertir el .dot en una imagen .png.
    string comando = "dot -Tpng \"" + rutaDot + "\" -o \"" + rutaPng + "\"";
    int resultado = system(comando.c_str());

    if (resultado == 0) {
        cout << "Imagen generada en: " << rutaPng << endl;
    } else {
        cerr << "no hay reporte no hay puntos :(" << endl;
    }
}
