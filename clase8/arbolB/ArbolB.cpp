#include "ArbolB.h"
#include <iostream>


//    CONSTRUCTOR Y DESTRUCTOR

ArbolB::ArbolB(int grado)
{
    M = grado;
    maxClaves = M - 1;
    maxHijos = M;

    // ceil(M/2) calculado con aritmetica entera: (M + 1) / 2
    // Ejemplos: M=3 -> (3+1)/2=2 | M=4 -> (4+1)/2=2 | M=5 -> (5+1)/2=3
    //           M=6 -> (6+1)/2=3
    minHijos = (M + 1) / 2;
    minClaves = minHijos - 1;

    raiz = nullptr;
    contadorGraficado = 0;
}

ArbolB::~ArbolB()
{
    // Al hacer delete sobre la raiz, el destructor de Nodo se encarga,
    // de forma RECURSIVA, de liberar todos los nodos descendientes.
    delete raiz;
}

bool ArbolB::estaVacio() const
{
    return raiz == nullptr;
}


//                        INSERCION


void ArbolB::insertar(int valor)
{
    if (raiz == nullptr)
    {
        // Caso base: el arbol esta vacio, se crea la raiz como una hoja
        // con una sola clave.
        raiz = new Nodo(true);
        raiz->insertarClaveEnPosicion(valor, 0);
        return;
    }

    if (buscar(valor))
    {
        // En un arbol de busqueda no tiene sentido guardar duplicados.
        std::cout << "  (el valor " << valor << " ya existe, no se inserta duplicado)" << std::endl;
        return;
    }

    insertarEnNodo(raiz, valor);
}

// insertarEnNodo: desciende recursivamente hasta la hoja correcta,
// inserta ahi la clave y, si el nodo queda con overflow, dispara la division.
void ArbolB::insertarEnNodo(Nodo *nodo, int valor)
{
    bool encontrada = false;
    int pos = nodo->buscarPosicion(valor, encontrada);

    if (nodo->esHoja)
    {
        // ---- CASO BASE ----
        nodo->insertarClaveEnPosicion(valor, pos);
        if (nodo->numClaves > maxClaves)
        {
            dividirNodo(nodo);
        }
    }
    else
    {
        // ---- CASO RECURSIVO ----
        // "pos" es tambien el indice del hijo por el cual se debe seguir
        // bajando (el hijo que queda "entre" las claves vecinas).
        Nodo *siguienteNodo = nodo->obtenerHijo(pos);
        insertarEnNodo(siguienteNodo, valor); // LLAMADA RECURSIVA
    }
}

// dividirNodo: parte un nodo que quedo con M claves (una mas del
// maximo permitido, que es M-1) en dos nodos, y sube la clave central
// al padre.
// Si al insertar la clave central en el padre, el padre TAMBIEN queda
// con overflow, se vuelve a llamar dividirNodo sobre el padre. Esta es
// una recursividad "ascendente": el desbordamiento puede subir varios
// niveles seguidos, incluso hasta la raiz (caso en el que se crea una
// nueva raiz y el arbol crece un nivel).
void ArbolB::dividirNodo(Nodo *nodo)
{
    int totalClaves = nodo->numClaves; // = M (una mas del maximo)
    int medio = totalClaves / 2;       // indice (0-based) de la clave que sube

    int valorMedio = nodo->obtenerClave(medio);

    // Se crea el nuevo nodo hermano (quedara a la derecha de "nodo")
    Nodo *nuevoHermano = new Nodo(nodo->esHoja);

    // Se mueven hacia el nuevo hermano todas las claves que quedan
    // despues de la clave del medio. Como al eliminar la clave en la
    // posicion (medio+1) las demas "se recorren" dentro de la lista
    // enlazada, siempre pedimos la misma posicion (medio+1).
    int totalAMover = totalClaves - medio - 1;
    for (int i = 0; i < totalAMover; i++)
    {
        int val = nodo->obtenerClave(medio + 1);
        nodo->eliminarClaveEnPosicion(medio + 1);
        nuevoHermano->insertarClaveEnPosicion(val, nuevoHermano->numClaves);
    }

    // Se retira del nodo original la clave central (ya la tenemos
    // guardada en valorMedio, es la que subira al padre).
    nodo->eliminarClaveEnPosicion(medio);

    // Si el nodo no es hoja, tambien hay que repartir los hijos entre
    // "nodo" y "nuevoHermano".
    if (!nodo->esHoja)
    {
        int totalHijos = nodo->numHijos; // = M + 1 (uno mas del maximo)
        int hijosQueQuedan = medio + 1;  // "nodo" se queda con estos
        int hijosAMover = totalHijos - hijosQueQuedan;

        for (int i = 0; i < hijosAMover; i++)
        {
            Nodo *h = nodo->obtenerHijo(hijosQueQuedan);
            nodo->eliminarHijoEnPosicion(hijosQueQuedan);
            h->padre = nuevoHermano;
            nuevoHermano->insertarHijoEnPosicion(h, nuevoHermano->numHijos);
        }
    }

    if (nodo == raiz)
    {
        // ---- CASO ESPECIAL: se divide la raiz ----
        // Se crea una nueva raiz con una sola clave (la que subio) y dos
        // hijos: el nodo original y su nuevo hermano. El arbol crece un
        // nivel de altura.
        Nodo *nuevaRaiz = new Nodo(false); // una raiz que se acaba de dividir nunca es hoja
        nuevaRaiz->insertarClaveEnPosicion(valorMedio, 0);
        nuevaRaiz->insertarHijoEnPosicion(nodo, 0);
        nuevaRaiz->insertarHijoEnPosicion(nuevoHermano, 1);

        nodo->padre = nuevaRaiz;
        nuevoHermano->padre = nuevaRaiz;
        raiz = nuevaRaiz;
    }
    else
    {
        // ---- CASO GENERAL: el nodo tiene padre ----
        // La clave central sube al padre, y el nuevo hermano se inserta
        // como hijo del padre, justo a la derecha de "nodo".
        Nodo *padre = nodo->padre;
        bool encontrada = false;
        int posEnPadre = padre->buscarPosicion(valorMedio, encontrada);

        padre->insertarClaveEnPosicion(valorMedio, posEnPadre);
        padre->insertarHijoEnPosicion(nuevoHermano, posEnPadre + 1);
        nuevoHermano->padre = padre;

        if (padre->numClaves > maxClaves)
        {
            dividirNodo(padre); // LLAMADA RECURSIVA (el overflow sigue subiendo)
        }
    }
}


//               BUSQUEDA
bool ArbolB::buscar(int valor) const
{
    return buscarRec(raiz, valor);
}

// buscarRec: busca "valor" dentro del subarbol "nodo".
// Caso base 1: nodo == nullptr (llegamos al final sin encontrarlo).
// Caso base 2: el valor esta en el nodo actual (encontrada == true).
// Caso base 3: el nodo es una hoja y el valor no esta (no hay a donde bajar).
// Caso recursivo: el nodo es interno y el valor no esta aqui, se sigue
// buscando en el hijo correspondiente.
bool ArbolB::buscarRec(Nodo *nodo, int valor) const
{
    if (nodo == nullptr)
        return false; // arbol vacio o subarbol inexistente

    bool encontrada = false;
    int pos = nodo->buscarPosicion(valor, encontrada);

    if (encontrada)
        return true;
    if (nodo->esHoja)
        return false;

    return buscarRec(nodo->obtenerHijo(pos), valor); // LLAMADA RECURSIVA
}


//          ELIMINACION


void ArbolB::eliminar(int valor)
{
    if (raiz == nullptr)
    {
        std::cout << "  (el arbol esta vacio, no se puede eliminar " << valor << ")" << std::endl;
        return;
    }

    if (!buscar(valor))
    {
        std::cout << "  (el valor " << valor << " no existe en el arbol)" << std::endl;
        return;
    }

    eliminarRec(raiz, valor);

    // Tras eliminar, la raiz pudo haberse quedado sin claves (esto pasa
    // cuando la raiz sufre una fusion de sus dos unicos hijos).
    if (raiz->numClaves == 0)
    {
        if (raiz->esHoja)
        {
            // El arbol queda completamente vacio.
            delete raiz;
            raiz = nullptr;
        }
        else
        {
            // La raiz se queda con un solo hijo: ese hijo pasa a ser la
            // nueva raiz (el arbol "pierde" un nivel de altura).
            Nodo *nuevaRaiz = raiz->obtenerHijo(0);
            raiz->eliminarHijoEnPosicion(0); // se desconecta para no perderlo al hacer delete
            nuevaRaiz->padre = nullptr;
            delete raiz; // ya no tiene claves ni hijos, se libera sin arrastrar nada mas
            raiz = nuevaRaiz;
        }
    }
}

// eliminarRec: elimina "valor" del subarbol "nodo" usando el enfoque
// PREVENTIVO / DESCENDENTE (se corrige el underflow ANTES de bajar, no
// despues), lo cual evita tener que "deshacer" pasos ya dados.
//
// Hay tres llamadas recursivas distintas, segun el caso:
//   1) Cuando la clave esta en un nodo interno y se reemplaza por su
//      predecesor o sucesor: se vuelve a llamar sobre el hijo del que
//      se tomo ese predecesor/sucesor, para eliminarlo de ahi.
//   2) Cuando hay que fusionar dos hijos: se llama de nuevo sobre el
//      nodo fusionado, porque el valor buscado ahora vive ahi.
//   3) Cuando el valor no esta en este nodo: se llama sobre el hijo
//      correspondiente para seguir bajando.
void ArbolB::eliminarRec(Nodo *nodo, int valor)
{
    bool encontrada = false;
    int pos = nodo->buscarPosicion(valor, encontrada);

    if (encontrada)
    {
        if (nodo->esHoja)
        {
            //  CASO BASE: clave encontrada en una hoja 
            // Se elimina directamente, no hace falta nada mas.
            nodo->eliminarClaveEnPosicion(pos);
        }
        else
        {
            //  CASO: clave encontrada en un nodo interno 
            // No se puede quitar "a secas" una clave interna (perderiamos
            // la separacion entre subarboles). Se reemplaza por su
            // predecesor (el mayor del subarbol izquierdo) o su sucesor
            // (el menor del subarbol derecho), y ESE valor duplicado se
            // elimina despues de forma recursiva desde una hoja.
            Nodo *hijoIzq = nodo->obtenerHijo(pos);
            Nodo *hijoDer = nodo->obtenerHijo(pos + 1);

            if (hijoIzq->numClaves > minClaves)
            {
                // El hijo izquierdo tiene claves "de sobra": usamos el predecesor
                int predecesor = obtenerMaximo(hijoIzq);
                nodo->eliminarClaveEnPosicion(pos);
                nodo->insertarClaveEnPosicion(predecesor, pos);
                eliminarRec(hijoIzq, predecesor); // LLAMADA RECURSIVA
            }
            else if (hijoDer->numClaves > minClaves)
            {
                // El hijo derecho tiene claves "de sobra": usamos el sucesor
                int sucesor = obtenerMinimo(hijoDer);
                nodo->eliminarClaveEnPosicion(pos);
                nodo->insertarClaveEnPosicion(sucesor, pos);
                eliminarRec(hijoDer, sucesor); // LLAMADA RECURSIVA
            }
            else
            {
                // Ninguno de los dos hijos tiene claves de sobra:
                // se fusionan hijoIzq + clave(pos) + hijoDer en un solo nodo.
                fusionar(nodo, pos);
                // Tras la fusion, "valor" quedo dentro de hijoIzq (que
                // ahora contiene tambien todo lo que tenia hijoDer).
                eliminarRec(hijoIzq, valor); // LLAMADA RECURSIVA
            }
        }
    }
    else
    {
        //  La clave NO esta en este nodo: hay que bajar 
        if (nodo->esHoja)
        {
            // No deberia ocurrir (ya validamos antes que el valor existe
            // en el arbol), se deja como salvaguarda defensiva.
            return;
        }

        Nodo *hijo = nodo->obtenerHijo(pos);

        if (hijo->numClaves == minClaves)
        {
            // El hijo por el que hay que bajar esta "al minimo": si se le
            // quita una clave abajo podria quedar en underflow. Se
            // rebalancea PREVENTIVAMENTE antes de descender.
            reestructurar(nodo, pos);

            // Tras reestructurar (rotacion o fusion), la posicion del
            // hijo correcto puede cambiar (sobre todo si hubo fusion),
            // por lo que se vuelve a calcular.
            pos = nodo->buscarPosicion(valor, encontrada);
            if (encontrada)
            {
                // Con rotaciones/fusiones que solo bajan claves del padre
                // (nunca las suben), esto no deberia pasar; se deja como
                // salvaguarda.
                eliminarRec(nodo, valor); // LLAMADA RECURSIVA (salvaguarda)
                return;
            }
            hijo = nodo->obtenerHijo(pos);
        }

        eliminarRec(hijo, valor); // LLAMADA RECURSIVA (descenso normal)
    }
}

// obtenerMaximo: baja siempre por el ULTIMO hijo hasta llegar a una
// hoja, y devuelve su ultima clave (el valor mas grande del subarbol).
// >>> RECURSIVA <<<
int ArbolB::obtenerMaximo(Nodo *nodo) const
{
    if (nodo->esHoja)
    {
        return nodo->obtenerClave(nodo->numClaves - 1);
    }
    return obtenerMaximo(nodo->obtenerHijo(nodo->numHijos - 1)); // LLAMADA RECURSIVA
}

// obtenerMinimo: baja siempre por el PRIMER hijo hasta llegar a una
// hoja, y devuelve su primera clave (el valor mas pequeño del subarbol).
int ArbolB::obtenerMinimo(Nodo *nodo) const
{
    if (nodo->esHoja)
    {
        return nodo->obtenerClave(0);
    }
    return obtenerMinimo(nodo->obtenerHijo(0)); // LLAMADA RECURSIVA
}

// reestructurar: garantiza que el hijo en la posicion "indice" de
// "nodo" tenga MAS del minimo de claves, ya sea pidiendole prestado a
// un hermano (rotacion, mas barato) o fusionandolo con un hermano
// (cuando ningun hermano puede prestar sin quedar el mismo en underflow).
// NO es recursiva: es un paso local de un solo nivel.
void ArbolB::reestructurar(Nodo *nodo, int indice)
{
    Nodo *hermanoIzq = (indice > 0) ? nodo->obtenerHijo(indice - 1) : nullptr;
    Nodo *hermanoDer = (indice < nodo->numHijos - 1) ? nodo->obtenerHijo(indice + 1) : nullptr;

    if (hermanoIzq != nullptr && hermanoIzq->numClaves > minClaves)
    {
        // El hermano izquierdo puede prestar una clave sin quedar el
        // mismo por debajo del minimo.
        rotarDerecha(nodo, indice);
    }
    else if (hermanoDer != nullptr && hermanoDer->numClaves > minClaves)
    {
        // El hermano derecho puede prestar una clave.
        rotarIzquierda(nodo, indice);
    }
    else if (hermanoIzq != nullptr)
    {
        // Ningun hermano puede prestar: se fusiona con el izquierdo.
        fusionar(nodo, indice - 1);
    }
    else
    {
        // No hay hermano izquierdo: se fusiona obligatoriamente con el derecho.
        fusionar(nodo, indice);
    }
}

// rotarDerecha: el hermano IZQUIERDO le "presta" una clave al hijo en
// "indice", pasando por el padre (rotacion simple de un solo nivel).
//
//        Antes:                          Despues:
//    padre: [... X ...]              padre: [... Y ...]
//   herm=[A,B,Y]  hijo=[Z,...]      herm=[A,B]   hijo=[X,Z,...]
//
// (X baja del padre al inicio del hijo; Y, la clave mas grande del
//  hermano, sube al padre en el lugar de X)
void ArbolB::rotarDerecha(Nodo *nodo, int indice)
{
    Nodo *hijo = nodo->obtenerHijo(indice);
    Nodo *hermanoIzq = nodo->obtenerHijo(indice - 1);

    // La clave del padre (posicion indice-1) baja al inicio del hijo
    int claveDelPadre = nodo->obtenerClave(indice - 1);
    hijo->insertarClaveEnPosicion(claveDelPadre, 0);

    // La ultima clave del hermano izquierdo sube a ocupar ese lugar en el padre
    int claveHermano = hermanoIzq->obtenerClave(hermanoIzq->numClaves - 1);
    hermanoIzq->eliminarClaveEnPosicion(hermanoIzq->numClaves - 1);
    nodo->eliminarClaveEnPosicion(indice - 1);
    nodo->insertarClaveEnPosicion(claveHermano, indice - 1);

    // Si no son hojas, el ULTIMO hijo del hermano izquierdo pasa a ser
    // el PRIMER hijo del nodo que recibio la clave (mantiene el orden).
    if (!hermanoIzq->esHoja)
    {
        Nodo *hijoMovido = hermanoIzq->obtenerHijo(hermanoIzq->numHijos - 1);
        hermanoIzq->eliminarHijoEnPosicion(hermanoIzq->numHijos - 1);
        hijo->insertarHijoEnPosicion(hijoMovido, 0);
        hijoMovido->padre = hijo;
    }
}

// rotarIzquierda: simetrica a rotarDerecha, pero el hermano DERECHO es
// quien le presta una clave al hijo en "indice".
void ArbolB::rotarIzquierda(Nodo *nodo, int indice)
{
    Nodo *hijo = nodo->obtenerHijo(indice);
    Nodo *hermanoDer = nodo->obtenerHijo(indice + 1);

    // La clave del padre (posicion indice) baja al final del hijo
    int claveDelPadre = nodo->obtenerClave(indice);
    hijo->insertarClaveEnPosicion(claveDelPadre, hijo->numClaves);

    // La primera clave del hermano derecho sube a ocupar ese lugar en el padre
    int claveHermano = hermanoDer->obtenerClave(0);
    hermanoDer->eliminarClaveEnPosicion(0);
    nodo->eliminarClaveEnPosicion(indice);
    nodo->insertarClaveEnPosicion(claveHermano, indice);

    // Si no son hojas, el PRIMER hijo del hermano derecho pasa a ser el
    // ULTIMO hijo del nodo que recibio la clave.
    if (!hermanoDer->esHoja)
    {
        Nodo *hijoMovido = hermanoDer->obtenerHijo(0);
        hermanoDer->eliminarHijoEnPosicion(0);
        hijo->insertarHijoEnPosicion(hijoMovido, hijo->numHijos);
        hijoMovido->padre = hijo;
    }
}

// fusionar: junta el hijo "indice" y el hijo "indice+1" de "nodo" en un
// solo nodo (el izquierdo sobrevive, el derecho se destruye), bajando
// la clave "indice" del padre justo al medio de los dos.
//
//        Antes:                              Despues:
//    padre: [... X ...]                  padre: [... ...]   (X desaparece de aqui)
//   izq=[A,B]   der=[C,D]              izq=[A,B,X,C,D]   (un solo nodo)
//
// NO es recursiva por si misma, pero quien la llama (eliminarRec) SI
// vuelve a recorrer recursivamente dentro del nodo resultante.
void ArbolB::fusionar(Nodo *nodo, int indice)
{
    Nodo *hijoIzq = nodo->obtenerHijo(indice);
    Nodo *hijoDer = nodo->obtenerHijo(indice + 1);

    // La clave del padre baja al final de hijoIzq (queda justo en medio)
    int claveBajada = nodo->obtenerClave(indice);
    hijoIzq->insertarClaveEnPosicion(claveBajada, hijoIzq->numClaves);

    // Se mueven todas las claves de hijoDer al final de hijoIzq, en orden
    while (hijoDer->numClaves > 0)
    {
        int val = hijoDer->obtenerClave(0);
        hijoDer->eliminarClaveEnPosicion(0);
        hijoIzq->insertarClaveEnPosicion(val, hijoIzq->numClaves);
    }

    // Si no son hojas, tambien se mueven todos los hijos de hijoDer,
    // reasignando su puntero "padre" al nuevo dueño (hijoIzq)
    if (!hijoDer->esHoja)
    {
        while (hijoDer->numHijos > 0)
        {
            Nodo *h = hijoDer->obtenerHijo(0);
            hijoDer->eliminarHijoEnPosicion(0);
            h->padre = hijoIzq;
            hijoIzq->insertarHijoEnPosicion(h, hijoIzq->numHijos);
        }
    }

    // Se retira del padre la clave que bajo y el puntero al hijo derecho
    // (que ya quedo vacio y se destruye).
    nodo->eliminarClaveEnPosicion(indice);
    nodo->eliminarHijoEnPosicion(indice + 1);

    delete hijoDer; // ya no tiene claves ni hijos propios, se libera limpio
}


//      IMPRESION POR NIVELES (depuracion)


// obtenerAltura: cuenta cuantos niveles hay por debajo de "nodo"
// (0 si "nodo" ya es una hoja). >>> RECURSIVA <<<
int ArbolB::obtenerAltura(Nodo *nodo) const
{
    if (nodo == nullptr)
        return -1;
    if (nodo->esHoja)
        return 0;
    return 1 + obtenerAltura(nodo->obtenerHijo(0)); // LLAMADA RECURSIVA
}

// imprimirNivel: imprime las claves de todos los nodos que estan
// exactamente "nivel" escalones por debajo de "nodo".
// (el caso base es nivel == 0; el caso recursivo baja
// un nivel por cada uno de los hijos).
void ArbolB::imprimirNivel(Nodo *nodo, int nivel) const
{
    if (nodo == nullptr)
        return;

    if (nivel == 0)
    {
        nodo->imprimirClaves();
        std::cout << "  ";
    }
    else
    {
        for (int i = 0; i < nodo->numHijos; i++)
        {
            imprimirNivel(nodo->obtenerHijo(i), nivel - 1); // LLAMADA RECURSIVA
        }
    }
}

void ArbolB::imprimirPorNiveles() const
{
    if (raiz == nullptr)
    {
        std::cout << "(arbol vacio)" << std::endl;
        return;
    }

    int altura = obtenerAltura(raiz);
    for (int nivel = 0; nivel <= altura; nivel++)
    {
        std::cout << "  Nivel " << nivel << ": ";
        imprimirNivel(raiz, nivel);
        std::cout << std::endl;
    }
}


//                GRAFICADO CON GRAPHVIZ (.dot)


// contarClaves: suma las claves de todo el arbol (recorrido completo).
// >>> RECURSIVA <<< Solo se usa para el titulo del grafico.
int ArbolB::contarClaves(Nodo *nodo) const
{
    if (nodo == nullptr)
        return 0;

    int total = nodo->numClaves;
    if (!nodo->esHoja)
    {
        for (int i = 0; i < nodo->numHijos; i++)
        {
            total += contarClaves(nodo->obtenerHijo(i)); // LLAMADA RECURSIVA
        }
    }
    return total;
}

// generarDot: escribe en "archivo" la definicion de "nodo" (en formato
// "record" de Graphviz) y luego, si tiene hijos, escribe recursivamente
// la definicion de cada hijo y la flecha que los conecta.
//
//  Es un recorrido en PREORDEN: primero se dibuja el
// nodo actual, y despues (dentro del for) se dibuja cada subarbol hijo.
std::string ArbolB::generarDot(Nodo *nodo, std::ofstream &archivo)
{
    // aquí va su codigo de graficar el dot :)
}

void ArbolB::graficar(const std::string &nombreArchivo)
{

    const std::string carpeta = "arbolB/reportes";
    const std::string rutaDot = carpeta + "/" + nombreArchivo + ".dot";
    const std::string rutaPng = carpeta + "/" + nombreArchivo + ".png";

    std::ofstream archivo(rutaDot);
    if (!archivo.is_open())
    {
        std::cout << "No se pudo crear el archivo: " << rutaDot << std::endl;
        return;
    }

    contadorGraficado = 0; // reiniciar los identificadores n0, n1, ... en cada grafico

    archivo << "digraph BTree {\n";
    archivo << "    rankdir=TB;\n";
    archivo << "    splines=false;\n";
    archivo << "    nodesep=0.4;\n";
    archivo << "    ranksep=1.2;\n";
    archivo << "    ordering=out;\n";
    archivo << "    node [\n";
    archivo << "        shape=record,\n";
    archivo << "        style=filled,\n";
    archivo << "        fontname=\"Arial\",\n";
    archivo << "        fontsize=12,\n";
    archivo << "        height=0.45\n";
    archivo << "    ];\n";
    archivo << "    edge [color=\"#111111\", arrowhead=none, penwidth=1.3];\n";

    int totalClaves = (raiz == nullptr) ? 0 : contarClaves(raiz);
    archivo << "    label=\"Arbol B  -  Orden M=" << M
            << "  -  Claves totales=" << totalClaves << "\";\n";
    archivo << "    labelloc=top;\n";
    archivo << "    fontsize=13;\n";

    if (raiz != nullptr)
    {
        generarDot(raiz, archivo);
    }

    archivo << "}\n";
    archivo.close();

    // Generar imagen PNG usando Graphviz
    std::string comando = "dot -Tpng \"" + rutaDot + "\" -o \"" + rutaPng + "\"";

    int resultado = system(comando.c_str());
    if (resultado == 0)
    {
        std::cout << "Imagen generada en: "
                  << rutaPng << std::endl;
    }
    else
    {
        std::cerr << "Error al ejecutar Graphviz (dot)." << std::endl;
    }
}
