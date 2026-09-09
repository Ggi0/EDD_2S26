#include "avl.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>

using namespace std;

//  Constructor / Destructor 

AVL::AVL() {
    raiz = nullptr;
}

AVL::~AVL() {
    liberarArbol(raiz);
    raiz = nullptr;
}

void AVL::liberarArbol(Nodo* nodo) {
    if (nodo == nullptr) return;
    liberarArbol(nodo->izquierdo);
    liberarArbol(nodo->derecho);
    delete nodo;
}

bool AVL::estaVacio() {
    return raiz == nullptr;
}


// Altura: un arbol vacio (nullptr) tiene altura -1.
int AVL::alturaNodo(Nodo* nodo) {
    if (nodo == nullptr) return -1;
    return nodo->altura;
}

// Factor de balance de un nodo.
int AVL::factorBalance(Nodo* nodo) {
    if (nodo == nullptr) return 0;
    return alturaNodo(nodo->izquierdo) - alturaNodo(nodo->derecho);
}

// La altura de un nodo es 1 + la mayor altura entre sus dos hijos.
void AVL::actualizarAltura(Nodo* nodo) {
    if (nodo == nullptr) return;
    nodo->altura = 1 + max(alturaNodo(nodo->izquierdo), alturaNodo(nodo->derecho));
}

/*
    ROTACIÓN SIMPLE DERECHA

    Se usa cuando el subárbol IZQUIERDO está demasiado pesado (caso LL).
    "y" baja y su hijo izquierdo "x" sube a ocupar su lugar.

           y                  x
          / \                / \
         x   T3   ------>   T1  y
        / \                    / \
       T1  T2                 T2  T3

    T2 (el hijo derecho de x) se reacomoda como hijo izquierdo de "y",
    porque T2 siempre es mayor que x y menor que y.
*/
Nodo* AVL::rotarDerecha(Nodo* y) {
    Nodo* x = y->izquierdo;
    Nodo* T2 = x->derecho;

    // Hacemos la rotación
    x->derecho = y;
    y->izquierdo = T2;

    // OJITOOOOO: 
    // el orden importa. Primero actualizamos "y" (que ahora quedo más abajo, como hijo), 
    // y hasta después "x" (que quedó como la nueva raíz del subárbol), 
    // porque la altura de x depende de la altura ya actualizada de y.
    actualizarAltura(y);
    actualizarAltura(x);

    return x; // x es la nueva raíz de este subarbol
}

/*
    ROTACIÓN SIMPLE IZQUIERDA
    
    Se usa cuando el subárbol DERECHO está demasiado pesado (caso RR). 
    "x" baja y su hijo derecho "y" sube a ocupar su lugar.

       x                      y
      / \                    / \
     T1  y     ------>      x   T3
        / \                / \
       T2  T3             T1  T2
*/
Nodo* AVL::rotarIzquierda(Nodo* x) {
    Nodo* y = x->derecho;
    Nodo* T2 = y->izquierdo;

    x->derecho = T2;
    y->izquierdo = x;

    actualizarAltura(x); // x quedó abajo, se actualiza primero
    actualizarAltura(y); // y es la nueva raíz, depende de la altura de x

    return y;
}

/*
    balancear(nodo)

    Punto central del autobalanceo. Se llama después de insertar o
    eliminar, ya con la altura de "nodo" actualizada. Revisa el factor
    de balance y decide si hace falta 0, 1 o 2 rotaciones.
*/
Nodo* AVL::balancear(Nodo* nodo) {
    if (nodo == nullptr) return nodo;

    int fb = factorBalance(nodo);

    //  Desbalance hacia la izquierda (subárbol izq. muy alto) 
    if (fb > 1) {
        // Caso Izquierda-Derecha (LR)
        //  Primero convertimos el hijo izquierdo en un caso simple LL rotándolo a la
        // izquierda, y luego resolvemos con una rotación a la derecha.
        if (factorBalance(nodo->izquierdo) < 0) {
            nodo->izquierdo = rotarIzquierda(nodo->izquierdo);
        }
        // Caso Izquierda-Izquierda (LL): una sola rotación derecha basta.
        return rotarDerecha(nodo);
    }

    //  Desbalance hacia la derecha (subárbol der. muy alto) 
    if (fb < -1) {
        // Caso Derecha-Izquierda (RL): convertimos el hijo derecho en
        // un caso simple RR rotándolo a la derecha...
        if (factorBalance(nodo->derecho) > 0) {
            nodo->derecho = rotarDerecha(nodo->derecho);
        }
        // Caso Derecha-Derecha (RR): una sola rotación izquierda basta.
        return rotarIzquierda(nodo);
    }

    // fb está entre -1 y 1: el nodo ya está balanceado, no se toca.
    return nodo;
}

//  INSERTAR 

void AVL::insertar(int valor) {
    raiz = insertarRec(raiz, valor); //80
}

Nodo* AVL::insertarRec(Nodo* nodo, int valor) {
    // como en el BST: bajamos hasta encontrar el espacio vacío.
    if (nodo == nullptr) {
        return new Nodo(valor);
    }

    if (valor < nodo->dato) {
        nodo->izquierdo = insertarRec(nodo->izquierdo, valor);
    } else if (valor > nodo->dato) {
        nodo->derecho = insertarRec(nodo->derecho, valor);
    } else {
        // No se permiten duplicados.
        cout << " El valor " << valor << " ya existe, no se inserta duplicado.\n";
        return nodo;
    }

    // 2) la recursión, este nodo es ancestro del nodo
    //    recién insertado, así que puede haberse desbalanceado:
    //    recalculamos su altura...
    actualizarAltura(nodo);

    // 3) ...y lo balanceamos si hace falta. Esto se repite en cada
    //    nivel del camino de regreso hasta la raíz, garantizando que
    //    el árbol completo vuelva a cumplir la propiedad AVL.
    return balancear(nodo);
}

//  BUSCAR 
bool AVL::buscar(int valor) {
    return buscarRec(raiz, valor) != nullptr;
}

Nodo* AVL::buscarRec(Nodo* nodo, int valor) {
    if (nodo == nullptr || nodo->dato == valor) {
        return nodo;
    }
    if (valor < nodo->dato) {
        return buscarRec(nodo->izquierdo, valor);
    }
    return buscarRec(nodo->derecho, valor);
}

//  ELIMINAR 

void AVL::eliminar(int valor) {
    raiz = eliminarRec(raiz, valor);
}

Nodo* AVL::eliminarRec(Nodo* nodo, int valor) {
    if (nodo == nullptr) {
        cout << "[info] El valor " << valor << " no existe en el árbol.\n";
        return nodo;
    }

    if (valor < nodo->dato) {
        nodo->izquierdo = eliminarRec(nodo->izquierdo, valor);
    } else if (valor > nodo->dato) {
        nodo->derecho = eliminarRec(nodo->derecho, valor);
    } else {
        // Encontramos el nodo a eliminar (misma lógica que en el BST):

        // Caso 1: sin hijos (hoja)
        if (nodo->izquierdo == nullptr && nodo->derecho == nullptr) {
            delete nodo;
            return nullptr;
        }

        // Caso 2: un solo hijo -> el hijo ocupa el lugar del nodo
        if (nodo->izquierdo == nullptr) {
            Nodo* temp = nodo->derecho;
            delete nodo;
            return temp; // igual se rebalanceará más arriba en la recursión
        }
        if (nodo->derecho == nullptr) {
            Nodo* temp = nodo->izquierdo;
            delete nodo;
            return temp;
        }

        // Caso 3: dos hijos -> reemplazamos con el sucesor inorden
        // (el mínimo del subárbol derecho) y eliminamos ese sucesor
        // de su posición original.
        Nodo* sucesor = encontrarMinimo(nodo->derecho);
        nodo->dato = sucesor->dato;
        nodo->derecho = eliminarRec(nodo->derecho, sucesor->dato);
    }

    // PEROOOOOOOO aquí NO basta con devolver "nodo":
    // eliminar un valor puede reducir la altura de un subárbol y
    // desbalancear a cualquiera de sus ancestros. Por eso, igual que
    // en insertarRec, en cada nivel del regreso recalculamos altura y balanceamos.
    actualizarAltura(nodo);
    return balancear(nodo);
}

Nodo* AVL::encontrarMinimo(Nodo* nodo) {
    while (nodo->izquierdo != nullptr) {
        nodo = nodo->izquierdo;
    }
    return nodo;
}

//  RECORRIDOS 
void AVL::inOrden() {
    cout << "InOrden:   ";
    inOrdenRec(raiz);
    cout << endl;
}

void AVL::inOrdenRec(Nodo* nodo) {
    if (nodo == nullptr) return;
    inOrdenRec(nodo->izquierdo);
    cout << nodo->dato << " ";
    inOrdenRec(nodo->derecho);
}

void AVL::preOrden() {
    cout << "PreOrden:  ";
    preOrdenRec(raiz);
    cout << endl;
}

void AVL::preOrdenRec(Nodo* nodo) {
    if (nodo == nullptr) return;
    cout << nodo->dato << " ";
    preOrdenRec(nodo->izquierdo);
    preOrdenRec(nodo->derecho);
}

void AVL::postOrden() {
    cout << "PostOrden: ";
    postOrdenRec(raiz);
    cout << endl;
}

void AVL::postOrdenRec(Nodo* nodo) {
    if (nodo == nullptr) return;
    postOrdenRec(nodo->izquierdo);
    postOrdenRec(nodo->derecho);
    cout << nodo->dato << " ";
}

//  ALTURA / CONTEOS 
int AVL::altura() {
    return alturaNodo(raiz);
}

int AVL::contarNodos() {
    return contarNodosRec(raiz);
}

int AVL::contarNodosRec(Nodo* nodo) {
    if (nodo == nullptr) return 0;
    return 1 + contarNodosRec(nodo->izquierdo) + contarNodosRec(nodo->derecho);
}

int AVL::contarHojas() {
    return contarHojasRec(raiz);
}

int AVL::contarHojasRec(Nodo* nodo) {
    if (nodo == nullptr) return 0;
    if (nodo->izquierdo == nullptr && nodo->derecho == nullptr) return 1;
    return contarHojasRec(nodo->izquierdo) + contarHojasRec(nodo->derecho);
}

//  IMPRESIÓN POR NIVELES 

void AVL::imprimirPorNiveles() {
    int h = altura();
    if (h == -1) {
        cout << "(árbol vacío)" << endl;
        return;
    }

    for (int nivel = 0; nivel <= h; nivel++) {
        cout << "Nivel " << nivel << ": ";
        imprimirNivelRec(raiz, nivel, 0);
        cout << endl;
    }
}

void AVL::imprimirNivelRec(Nodo* nodo, int nivelObjetivo, int nivelActual) {
    if (nodo == nullptr) return;

    if (nivelActual == nivelObjetivo) {
        cout << nodo->dato << "(fb=" << factorBalance(nodo) << ") ";
        return;
    }

    imprimirNivelRec(nodo->izquierdo, nivelObjetivo, nivelActual + 1);
    imprimirNivelRec(nodo->derecho, nivelObjetivo, nivelActual + 1);
}

//  GRAFICAR (Graphviz) 

void AVL::graficar(const string& nombreArchivo) const {
    const string carpeta = "avl/reporte";
    const string rutaDot = carpeta + "/" + nombreArchivo + ".dot";
    const string rutaPng = carpeta + "/" + nombreArchivo + ".png";

    ofstream archivo(rutaDot);
    if (!archivo.is_open()) {
        cerr << "No se pudo crear el archivo: " << rutaDot << endl;
        return;
    }

    archivo << "digraph AVL {\n";
    archivo << "    rankdir=TB;\n";
    archivo << "    node [fontname=\"Helvetica\"];\n";
    archivo << "    edge [fontname=\"Helvetica\"];\n\n";

    if (raiz == nullptr) {
        archivo << "    vacio [label=\"Arbol vacio\", shape=plaintext];\n";
        archivo << "}\n";
        archivo.close();
        string comandoVacio = "dot -Tpng \"" + rutaDot + "\" -o \"" + rutaPng + "\"";
        system(comandoVacio.c_str());
        return;
    }

    int contador = 0;
    string idRaiz = graficarRec(raiz, archivo, contador);

    archivo << "\n    raizPtr [shape=point];\n";
    archivo << "    raizPtr -> " << idRaiz << ";\n";

    archivo << "}\n";
    archivo.close();

    string comando = "dot -Tpng \"" + rutaDot + "\" -o \"" + rutaPng + "\"";
    int resultado = system(comando.c_str());

    if (resultado == 0) {
        cout << "Imagen generada en: " << rutaPng << endl;
    } else {
        cerr << "Ocurrio un error al ejecutar Graphviz (dot). yanosale:(" << endl;
    }
}

string AVL::graficarRec(Nodo* nodo, ofstream& archivo, int& contador) const {
    if (nodo == nullptr) return "";

    string idActual = "nodo" + to_string(contador++);

    // Ademas del dato, mostramos altura (h) y factor de balance (fb)
    // directamente en el nodo: es la forma mas facil de comprobar
    // visualmente que el arbol siempre queda balanceado (fb en {-1,0,1}).
    int alturaIzq = (nodo->izquierdo != nullptr) ? nodo->izquierdo->altura : -1;
    int alturaDer = (nodo->derecho != nullptr) ? nodo->derecho->altura : -1;
    int fb = alturaIzq - alturaDer;

    archivo << "    " << idActual
            << " [shape=circle, style=\"filled\", fillcolor=\"#A8C8E6\", "
            << "label=\"" << nodo->dato
            << "\\nh=" << nodo->altura << " fb=" << fb << "\"];\n";

    string idIzq = graficarRec(nodo->izquierdo, archivo, contador);
    if (!idIzq.empty()) {
        archivo << "    " << idActual << " -> " << idIzq
                << " [color=\"#2E5A8B\", label=\"I\"];\n";
    }

    string idDer = graficarRec(nodo->derecho, archivo, contador);
    if (!idDer.empty()) {
        archivo << "    " << idActual << " -> " << idDer
                << " [color=\"#2E5A8B\", label=\"D\"];\n";
    }

    return idActual;
}