#include "MatrizDispersa.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>

MatrizDispersa::MatrizDispersa() {
    cabFilas = nullptr;
    cabColumnas = nullptr;
}

MatrizDispersa::~MatrizDispersa() {
    // Liber todos los NodoDato recorriendo por filas.
    // Cada dato se libera UNA sola vez aunque pertenezca tambie a una lista de columna (no lo tocamos desde ahi).
    NodoCabecera* f = cabFilas;
    while (f != nullptr) {
        NodoDato* d = f->acceso;
        while (d != nullptr) {
            NodoDato* siguienteDato = d->derecha;
            delete d; // el destructor de NodoDato libera tambien la Pelicula*
            d = siguienteDato;
        }
        NodoCabecera* sigCab = f->siguiente;
        delete f;
        f = sigCab;
    }

    // Liberamos las cabeceras de columna (los datos ya se liberaron arriba)
    NodoCabecera* c = cabColumnas;
    while (c != nullptr) {
        NodoCabecera* sig = c->siguiente;
        delete c;
        c = sig;
    }
}

NodoCabecera* MatrizDispersa::buscarCabecera(NodoCabecera* lista, int indice) const {
    NodoCabecera* actual = lista;
    // Lista ordenada ascendente -> podemos detenernos apenas nos pasamos
    while (actual != nullptr && actual->indice < indice) {
        actual = actual->siguiente;
    }

    if (actual != nullptr && actual->indice == indice) return actual;
    
    return nullptr;
}

NodoCabecera* MatrizDispersa::obtenerOCrearCabecera(NodoCabecera*& lista, 
                                                    int indice,
                                                    const std::string& etiqueta) 
{
    // Caso especial: lista vacia
    if (lista == nullptr) {
        lista = new NodoCabecera(indice, etiqueta);
        return lista;
    }

    NodoCabecera* actual = lista;
    NodoCabecera* anteriorNodo = nullptr;

    // Avanzamos mientras el indice actual sea menor al buscado
    while (actual != nullptr && actual->indice < indice) {
        anteriorNodo = actual;
        actual = actual->siguiente;
    }

    // Ya existe esa cabecera: si nos pasaron una etiqueta nueva, la actualizamos
    if (actual != nullptr && actual->indice == indice) {
        if (!etiqueta.empty()) actual->etiqueta = etiqueta;
        return actual;
    }

    // No existe: creamos la cabecera y la insertamos entre anteriorNodo y actual
    NodoCabecera* nueva = new NodoCabecera(indice, etiqueta);
    nueva->siguiente = actual;
    nueva->anterior = anteriorNodo;

    if (actual != nullptr) actual->anterior = nueva;

    if (anteriorNodo != nullptr) anteriorNodo->siguiente = nueva;
    else lista = nueva; // 'nueva' se convirtio en la primera cabecera de la lista

    return nueva;
}

void MatrizDispersa::desenlazarCabecera(NodoCabecera*& lista, NodoCabecera* cab) {
    if (cab->anterior != nullptr) 
        cab->anterior->siguiente = cab->siguiente;
    else 
        lista = cab->siguiente; // 'cab' era la primera de la lista

    if (cab->siguiente != nullptr) 
        cab->siguiente->anterior = cab->anterior;

    delete cab;
}

void MatrizDispersa::definirEtiquetaFila(int indice, const std::string& etiqueta) {
    obtenerOCrearCabecera(cabFilas, indice, etiqueta);
}

void MatrizDispersa::definirEtiquetaColumna(int indice, const std::string& etiqueta) {
    obtenerOCrearCabecera(cabColumnas, indice, etiqueta);
}

void MatrizDispersa::insertar(int fila, int columna, Pelicula* p) {
    
    // Si ya hay un dato en esa posicion, lo reemplazamos (liberando el anterior)
    NodoDato* existente = buscar(fila, columna);
    if (existente != nullptr) {
        delete existente->pelicula;
        existente->pelicula = p;
        return;
    }

    // 1) Obtenemos (o creamos) las cabeceras de fila y columna correspondientes.
    //    Si el usuario ya llamo a definirEtiquetaFila/Columna antes, esa etiqueta
    //    se conserva porque aqui pasamos "" (obtenerOCrearCabecera no la pisa).
    NodoCabecera* cabF = obtenerOCrearCabecera(cabFilas, fila, "");
    NodoCabecera* cabC = obtenerOCrearCabecera(cabColumnas, columna, "");

    // 2) Creamos el nodo dato
    NodoDato* nuevo = new NodoDato(fila, columna, p);

    // 3) Enlazamos HORIZONTALMENTE dentro de la fila (lista ordenada por columna)
    NodoDato* actual = cabF->acceso;
    NodoDato* anteriorDato = nullptr;
    while (actual != nullptr && actual->columna < columna) {
        anteriorDato = actual;
        actual = actual->derecha;
    }
    nuevo->derecha = actual;
    nuevo->izquierda = anteriorDato;
    if (actual != nullptr) actual->izquierda = nuevo;
    if (anteriorDato != nullptr) anteriorDato->derecha = nuevo;
    else cabF->acceso = nuevo; // 'nuevo' es el primer dato de la fila

    // 4) Enlazamos VERTICALMENTE dentro de la columna (lista ordenada por fila)
    actual = cabC->acceso;
    NodoDato* arribaDe = nullptr;
    while (actual != nullptr && actual->fila < fila) {
        arribaDe = actual;
        actual = actual->abajo;
    }
    nuevo->abajo = actual;
    nuevo->arriba = arribaDe;
    if (actual != nullptr) actual->arriba = nuevo;
    if (arribaDe != nullptr) arribaDe->abajo = nuevo;
    else cabC->acceso = nuevo; // 'nuevo' es el primer dato de la columna
}

NodoDato* MatrizDispersa::buscar(int fila, int columna) const {
    // 1) Ubicamos la cabecera de la fila (si no existe, no hay dato)
    NodoCabecera* cabF = buscarCabecera(cabFilas, fila);
    if (cabF == nullptr) return nullptr;

    // 2) Recorremos esa fila hacia la derecha hasta llegar (o pasarnos) de la columna
    NodoDato* actual = cabF->acceso;
    while (actual != nullptr && actual->columna < columna) {
        actual = actual->derecha;
    }

    if (actual != nullptr && actual->columna == columna) return actual;
    return nullptr;
}

bool MatrizDispersa::eliminar(int fila, int columna) {
    NodoDato* nodo = buscar(fila, columna);
    if (nodo == nullptr) return false; // no habia nada que eliminar

    NodoCabecera* cabF = buscarCabecera(cabFilas, fila);
    NodoCabecera* cabC = buscarCabecera(cabColumnas, columna);

    // Desenlazar horizontalmente (sacarlo de la lista de su fila)
    if (nodo->izquierda != nullptr) nodo->izquierda->derecha = nodo->derecha;
    else if (cabF != nullptr) cabF->acceso = nodo->derecha; // era el primero de la fila
    if (nodo->derecha != nullptr) nodo->derecha->izquierda = nodo->izquierda;

    // Desenlazar verticalmente (sacarlo de la lista de su columna)
    if (nodo->arriba != nullptr) nodo->arriba->abajo = nodo->abajo;
    else if (cabC != nullptr) cabC->acceso = nodo->abajo; // era el primero de la columna
    if (nodo->abajo != nullptr) nodo->abajo->arriba = nodo->arriba;

    delete nodo; // libera tambien la Pelicula* asociada

    // Si la fila/columna quedo sin datos, tambien quitamos su cabecera:
    // esto es lo que hace que la matriz se "encoja" dinamicamente.
    if (cabF != nullptr && cabF->acceso == nullptr) desenlazarCabecera(cabFilas, cabF);
    if (cabC != nullptr && cabC->acceso == nullptr) desenlazarCabecera(cabColumnas, cabC);

    return true;
}

bool MatrizDispersa::esVacia() const {
    return cabFilas == nullptr;
}

// este metodo es solo para la interfaz:
std::vector<std::string> MatrizDispersa::obtenerDirectores() const {
    std::vector<std::string> directores;

    NodoCabecera* actual = cabFilas;

    while (actual != nullptr) {
        if (!actual->etiqueta.empty()) {
            directores.push_back(actual->etiqueta);
        }

        actual = actual->siguiente;
    }

    return directores;
}

// este metodo es solo para la interfaz:
std::vector<std::string> MatrizDispersa::obtenerGeneros() const {
    std::vector<std::string> generos;

    NodoCabecera* actual = cabColumnas;

    while (actual != nullptr) {
        if (!actual->etiqueta.empty()) {
            generos.push_back(actual->etiqueta);
        }

        actual = actual->siguiente;
    }

    return generos;
}



void MatrizDispersa::mostrar() const {
    if (esVacia()) {
        std::cout << "(La matriz esta vacia)\n";
        return;
    }
    std::cout << "===== Contenido de la matriz dispersa =====\n";
    NodoCabecera* f = cabFilas;
    while (f != nullptr) {
        std::cout << "Fila " << f->indice;
        if (!f->etiqueta.empty()) std::cout << " (" << f->etiqueta << ")";
        std::cout << ":\n";

        NodoDato* d = f->acceso;
        while (d != nullptr) {
            std::cout << "   -> col " << d->columna << ": " << d->pelicula->toString() << "\n";
            d = d->derecha;
        }
        f = f->siguiente;
    }
    std::cout << "========================================================\n";
}

std::string MatrizDispersa::generarDOT() const {
    std::ostringstream out;

    out << "digraph MatrizDispersa {\n";
    out << "    labelloc=\"t\";\n";
    out << "    label=\"Matriz Dispersa (Lista Enlazada Ortogonal)\";\n";
    out << "    fontsize=16;\n";
    out << "    fontname=\"Arial Bold\";\n";
    out << "    nodesep=0.6;\n";
    out << "    ranksep=0.7;\n\n";
    out << "    node [shape=box, style=filled, fontname=\"Arial\", fontsize=11];\n";
    out << "    edge [fontcolor=black, fontsize=9];\n\n";

    if (esVacia()) {
        out << "    vacio [label=\"MATRIZ VACIA\", fillcolor=lightgray, shape=ellipse];\n}\n";
        return out.str();
    }

    out << "    origen [label=\"fila/columna\", fontsize=10, fillcolor=white];\n\n";

    // ---- Cabeceras de columna ----
    out << "    // Cabeceras de columna (generos)\n";
    NodoCabecera* c = cabColumnas;
    int grupo = 1;
    while (c != nullptr) {
        std::string etq = c->etiqueta.empty() ? ("Col " + std::to_string(c->indice)) : c->etiqueta;
        out << "    cab_col_" << c->indice << " [label=\"" << etq << "\\n(col " << c->indice
            << ")\", group=" << grupo << ", fillcolor=\"#2980b9\", fontcolor=white];\n";
        c = c->siguiente;
        grupo++;
    }
    out << "\n";

    // ---- Cabeceras de fila ----
    out << "    //  Cabeceras de fila (directores) \n";
    NodoCabecera* f = cabFilas;
    while (f != nullptr) {
        std::string etq = f->etiqueta.empty() ? ("Fil " + std::to_string(f->indice)) : f->etiqueta;
        out << "    cab_fil_" << f->indice << " [label=\"" << etq << "\\n(fil " << f->indice
            << ")\", group=0, fillcolor=\"#27ae60\", fontcolor=white];\n";
        f = f->siguiente;
    }
    out << "\n";

    // nodo dato
    out << "    // Nodos dato (peliculas) \n";
    f = cabFilas;
    while (f != nullptr) {
        NodoDato* d = f->acceso;
        while (d != nullptr) {
            // Buscamos la posicion (grupo) de la columna de este dato, para alinearlo
            NodoCabecera* colCab = cabColumnas;
            int g = 1;
            while (colCab != nullptr && colCab->indice != d->columna) {
                colCab = colCab->siguiente;
                g++;
            }
            out << "    dato_" << d->fila << "_" << d->columna
                << " [label=\"(" << d->fila << "," << d->columna << ")\\n"
                << d->pelicula->toGraphvizLabel()
                << "\", group=" << g << ", fillcolor=\"#ecf0f1\"];\n";
            d = d->derecha;
        }
        f = f->siguiente;
    }
    out << "\n";

    // Punteros horizontales (derecha/izquierda), incluye cabecera->primer dato 
    out << "    // Punteros horizontales: derecha / izquierda\n";
    f = cabFilas;
    while (f != nullptr) {
        NodoDato* d = f->acceso;
        std::string prev = "cab_fil_" + std::to_string(f->indice);
        while (d != nullptr) {
            std::string curr = "dato_" + std::to_string(d->fila) + "_" + std::to_string(d->columna);
            out << "    " << prev << " -> " << curr << " [dir=both, color=\"#27ae60\"];\n";
            prev = curr;
            d = d->derecha;
        }
        f = f->siguiente;
    }
    out << "\n";

    // Punteros verticales (arriba/abajo), incluye cabecera->primer dato
    out << "    // Punteros verticales: arriba / abajo\n";
    c = cabColumnas;
    while (c != nullptr) {
        NodoDato* d = c->acceso;
        std::string prev = "cab_col_" + std::to_string(c->indice);
        while (d != nullptr) {
            std::string curr = "dato_" + std::to_string(d->fila) + "_" + std::to_string(d->columna);
            out << "    " << prev << " -> " << curr << " [dir=both, color=\"#2980b9\"];\n";
            prev = curr;
            d = d->abajo;
        }
        c = c->siguiente;
    }
    out << "\n";

    // Punteros siguiente/anterior ENTRE cabeceras (piden verse bidireccionales) ----
    out << "    // Punteros siguiente/anterior entre cabeceras de columna\n";
    c = cabColumnas;
    while (c != nullptr && c->siguiente != nullptr) {
        out << "    cab_col_" << c->indice << " -> cab_col_" << c->siguiente->indice
            << " [dir=both, color=\"#8e44ad\", style=dashed, constraint=false];\n";
        c = c->siguiente;
    }
    out << "\n";

    out << "    // Punteros siguiente/anterior entre cabeceras de fila\n";
    f = cabFilas;
    while (f != nullptr && f->siguiente != nullptr) {
        out << "    cab_fil_" << f->indice << " -> cab_fil_" << f->siguiente->indice
            << " [dir=both, color=\"#8e44ad\", style=dashed, constraint=false];\n";
        f = f->siguiente;
    }
    out << "\n";

    // Alineacion visual 
    out << "    //  Alineacion visual\n";
    out << "    { rank=same; origen;";
    c = cabColumnas;
    while (c != nullptr) {
        out << " cab_col_" << c->indice << ";";
        c = c->siguiente;
    }
    out << " }\n";

    f = cabFilas;
    while (f != nullptr) {
        out << "    { rank=same; cab_fil_" << f->indice << ";";
        NodoDato* d = f->acceso;
        while (d != nullptr) {
            out << " dato_" << d->fila << "_" << d->columna << ";";
            d = d->derecha;
        }
        out << " }\n";
        f = f->siguiente;
    }
    out << "\n";

    // Encuadre invisible superior e izquierdo (para que quede como cuadradito) 
    if (cabColumnas != nullptr) {
        out << "    origen -> cab_col_" << cabColumnas->indice << " [style=invis];\n";
        c = cabColumnas;
        while (c != nullptr && c->siguiente != nullptr) {
            out << "    cab_col_" << c->indice << " -> cab_col_" << c->siguiente->indice << " [style=invis];\n";
            c = c->siguiente;
        }
    }
    if (cabFilas != nullptr) {
        out << "    origen -> cab_fil_" << cabFilas->indice << " [style=invis];\n";
        f = cabFilas;
        while (f != nullptr && f->siguiente != nullptr) {
            out << "    cab_fil_" << f->indice << " -> cab_fil_" << f->siguiente->indice << " [style=invis];\n";
            f = f->siguiente;
        }
    }

    out << "}\n";
    return out.str();
}

void MatrizDispersa::exportarDOT(const std::string& archivoBase) const {
    std::string dotFile = archivoBase + ".dot";
    std::string pngFile = archivoBase + ".png";

    std::ofstream archivo(dotFile);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo crear " << dotFile << "\n";
        return;
    }
    archivo << generarDOT();
    archivo.close();
    std::cout << "Archivo DOT generado: " << dotFile << "\n";

    // Intentamos invocar graphviz para generar el PNG (requiere tenerlo instalado)
    std::string comando = "/opt/local/bin/dot -Tpng " + dotFile + " -o " + pngFile;
    int resultado = std::system(comando.c_str());
    if (resultado == 0) {
        std::cout << "Imagen generada: " << pngFile << "\n";
    } else {
        std::cout << "[Aviso] No se pudo generar el PNG automaticamente. "
                  << "Puedes correr manualmente: " << comando << "\n";
    }
}


std::string MatrizDispersa::obtenerContenidoCelda(int fila, int columna) const
{
    NodoDato* nodo = buscar(fila, columna);

    if (nodo == nullptr) {
        return "";
    }

    return nodo->pelicula->toString();
}