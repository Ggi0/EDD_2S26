
#include "tablaHash/TablaHash.h"
#include <iostream>
using namespace std;

int main() {
    TablaHash tabla;

    // Insertamos varias placas de ejemplo.
    tabla.insertar("P-123BCD", "Carlos Perez");
    tabla.insertar("P-456XYZ", "Maria Lopez");
    tabla.insertar("P-789QRS", "Jose Ramirez");
    tabla.insertar("P-321ABC", "Ana Gutierrez");
    tabla.insertar("P-654LMN", "Luis Fernandez");
    tabla.insertar("P-987OPQ", "Sofia Castillo");
    tabla.insertar("P-111AAA", "Pedro Morales");
    tabla.insertar("P-222BBB", "Karla Rojas");

    tabla.graficar("tabla_placas");

    // Intentamos insertar una clave duplicada, para mostrar como la tabla lo detecta y evita el duplicado.
    tabla.insertar("P-123BCD", "Otro Nombre");
    

    // Mostramos el estado completo de la tabla (bucket por bucket).
    tabla.imprimir();

    // buscar
    string propietario;
    string placaBuscada = "P-789QRS";
    cout << ">> Buscando la placa " << placaBuscada << endl;
    if (tabla.buscar(placaBuscada, propietario)) {
        cout << "   Encontrada. Propietario: " << propietario << endl;
    } else {
        cout << "   La placa " << placaBuscada << " no esta registrada." << endl;
    }

    string placaInexistente = "P-000ZZZ";
    cout << ">> Buscando la placa " << placaInexistente << endl;
    if (tabla.buscar(placaInexistente, propietario)) {
        cout << "   Encontrada. Propietario: " << propietario << endl;
    } else {
        cout << "   La placa " << placaInexistente << " no esta registrada." << endl;
    }
    cout << endl;

    //  eliminar
    string placaEliminar = "P-456XYZ";
    if (tabla.eliminar(placaEliminar)) {
        cout << "   Registro eliminado correctamente." << endl;
    } else {
        cout << "   No se pudo eliminar (no existia)." << endl;
    }

    tabla.imprimir();

    tabla.graficar("tabla_placas_2");

    return 0;
}
