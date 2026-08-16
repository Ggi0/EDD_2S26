#include <iostream>
#include "./matriz/MatrizDispersa.h"
#include "./pelicula/pelicula.h"

/*
   Mapeo de indices (fila = director, columna = genero)

    Directores (filas):              Generos (columnas):
      0 = Francis Ford Coppola         0 = Drama
      1 = Quentin Tarantino            1 = Thriller
      2 = Christopher Nolan            2 = Ciencia Ficcion
      3 = Peter Jackson                3 = Fantasia
 */

int main() {
    MatrizDispersa matriz;

    // Le damos nombre a cada fila/columna 
    matriz.definirEtiquetaFila(0, "Francis Ford Coppola");
    matriz.definirEtiquetaFila(1, "Quentin Tarantino");
    matriz.definirEtiquetaFila(2, "Christopher Nolan");
    matriz.definirEtiquetaFila(3, "Peter Jackson");

    matriz.definirEtiquetaColumna(0, "Drama");
    matriz.definirEtiquetaColumna(1, "Thriller");
    matriz.definirEtiquetaColumna(2, "Ciencia Ficcion");
    matriz.definirEtiquetaColumna(3, "Fantasia");
    matriz.definirEtiquetaColumna(4, "Accion");
    matriz.definirEtiquetaColumna(5, "comedia");

    // Creamos las peliculas (el "new" es porque la matriz se queda con el puntero y es responsable de liberarlo) 
    Pelicula* elPadrino = new Pelicula("El Padrino", "Francis Ford Coppola", 175, 1972, "Drama");
    Pelicula* djangoDesencadenado = new Pelicula("Django Desencadenado", "Quentin Tarantino", 165, 2012, "Drama");
    Pelicula* pulpFiction = new Pelicula("Pulp Fiction", "Quentin Tarantino", 154, 1994, "Thriller");
    Pelicula* memento = new Pelicula("Memento", "Christopher Nolan", 113, 2000, "Thriller");
    Pelicula* inception = new Pelicula("Inception", "Christopher Nolan", 148, 2010, "Ciencia Ficcion");
    Pelicula* senorAnillos  = new Pelicula("El Senor de los Anillos", "Peter Jackson", 178, 2001, "Fantasia");
    Pelicula* peli7  = new Pelicula("Peli7", "Peter Jackson", 178, 2001, "Thriller");
    Pelicula* peli8  = new Pelicula("Peli8", "Peter Jackson", 178, 2001, "Accion");

    // Insertamos: insertar(fila, columna, pelicula)
    // (0,0): Coppola / Drama
    matriz.insertar(0, 0, elPadrino);
    
    // (1,0): Tarantino / Drama  y  (1,1): Tarantino / Thriller  -> misma fila, dos columnas
    matriz.insertar(1, 0, djangoDesencadenado);
    matriz.insertar(1, 1, pulpFiction);
    
    // (2,1): Nolan / Thriller  y  (2,2): Nolan / Ciencia Ficcion -> misma fila
    matriz.insertar(2, 1, memento);
    matriz.insertar(2, 2, inception);
    
    // (3,3): Jackson / Fantasia
    matriz.insertar(3, 3, senorAnillos);
    matriz.insertar(3, 1, peli7);
    matriz.insertar(3, 4, peli8);

    std::cout << "\n Estado inicial de la matriz \n";
    matriz.mostrar();

    //  BUSCAR()
    NodoDato* encontrado = matriz.buscar(2, 2); // buscar (2, 2)
    if (encontrado != nullptr) {
        std::cout << "Encontrado: " << encontrado->pelicula->toString() << "\n";
    } else {
        std::cout << "No existe dato en (2,2)\n";
    }

    NodoDato* noEncontrado = matriz.buscar(0, 3); // buscar (0,3) este no exites
    std::cout << (noEncontrado == nullptr ? "No existe dato en (0,3), como se esperaba\n"
                                            : "ERROR: no deberia haber encontrado algo\n");


    // Generamos el archivo .dot 
    matriz.exportarDOT("matriz_peliculas");

    return 0;

}