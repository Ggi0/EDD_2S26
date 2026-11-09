
#include "lzw/compresion.h"
#include "lzw/descompresion.h"

#include <iostream>
#include <string>
#include <filesystem>
#include <cstdint>
#include <iomanip>
#include <fstream>

// Elimina las comillas que suelen aparecer al copiar una ruta.
std::string limpiarRuta(std::string ruta) {
    if (ruta.size() >= 2 &&
        ((ruta.front() == '"' && ruta.back() == '"') ||
         (ruta.front() == '\'' && ruta.back() == '\''))) {
        ruta = ruta.substr(1, ruta.size() - 2);
    }

    return ruta;
}

// Muestra el texto recuperado sin modificar su contenido.
void mostrarTexto(const std::string& ruta) {
    std::ifstream archivo(ruta, std::ios::binary);

    if (!archivo) {
        std::cerr << "No se pudo abrir el texto descomprimido.\n";
        return;
    }

    std::cout << "\n                   TEXTO DESCOMPRIMIDO \n";

    char caracter;

    while (archivo.get(caracter)) {
        std::cout.put(caracter);
    }

    std::cout << "\n\n";
}

int main() {
    namespace fs = std::filesystem;

    int opcion;

    do {
        std::cout << "\n                  COMPRESOR LZW \n";
        std::cout << "1. Comprimir archivo\n";
        std::cout << "2. Descomprimir archivo\n";
        std::cout << "3. Salir\n";
        std::cout << "Seleccione una opcion: ";

        if (!(std::cin >> opcion)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Opcion no valida.\n";
            continue;
        }

        // Descarta el salto de línea para usar getline.
        std::cin.ignore(10000, '\n');

        if (opcion == 1) {
            std::string rutaOriginal;

            std::cout << "Ruta del archivo que desea comprimir: ";
            std::getline(std::cin, rutaOriginal);

            rutaOriginal = limpiarRuta(rutaOriginal);

            if (!fs::exists(rutaOriginal) ||
                !fs::is_regular_file(rutaOriginal)) {
                std::cout << "El archivo no existe o no es valido.\n";
                continue;
            }

            // Conserva el nombre del archivo y cambia la extensión.
            fs::path original(rutaOriginal);

            fs::path destino =
                fs::path("archivos_comprimidos") /
                (original.stem().string() + ".lzw");

            uint64_t tamanoOriginal = 0;
            uint64_t tamanoComprimido = 0;

            if (comprimirArchivo(
                    rutaOriginal,
                    destino.string(),
                    tamanoOriginal,
                    tamanoComprimido)) {

                std::cout << "\nCompresion realizada correctamente.\n";
                std::cout << "Archivo generado: "
                          << destino.string() << '\n';

                std::cout << "Tamano original: "
                          << tamanoOriginal << " bytes\n";

                std::cout << "Tamano comprimido: "
                          << tamanoComprimido << " bytes\n";

                if (tamanoOriginal > 0) {
                    double ahorro =
                        (1.0 -
                         static_cast<double>(tamanoComprimido) /
                         static_cast<double>(tamanoOriginal)) * 100.0;

                    std::cout << std::fixed << std::setprecision(2);
                    std::cout << "Ahorro de espacio: "
                              << ahorro << "%\n";

                    if (ahorro < 0) {
                        std::cout
                            << "El archivo comprimido ocupa mas espacio "
                            << "que el original.\n";
                    }
                } else {
                    std::cout
                        << "Ahorro de espacio: no aplica a un archivo "
                        << "original vacio.\n";
                }
            } else {
                std::cout << "No se pudo comprimir el archivo.\n";
            }

        } else if (opcion == 2) {
            std::string rutaComprimida;

            std::cout << "Ruta del archivo .lzw que desea descomprimir: ";
            std::getline(std::cin, rutaComprimida);

            rutaComprimida = limpiarRuta(rutaComprimida);

            if (!fs::exists(rutaComprimida) ||
                !fs::is_regular_file(rutaComprimida)) {
                std::cout << "El archivo no existe o no es valido.\n";
                continue;
            }

            fs::path comprimido(rutaComprimida);

            fs::path destino =
                fs::path("archivos_descomprimidos") /
                (comprimido.stem().string() + "_vc.txt");

            if (descomprimirArchivo(
                    rutaComprimida,
                    destino.string())) {

                std::cout << "\nDescompresion realizada correctamente.\n";
                std::cout << "Archivo generado: "
                          << destino.string() << '\n';

                // Muestra el contenido recuperado.
                mostrarTexto(destino.string());
            } else {
                std::cout << "No se pudo descomprimir el archivo.\n";
            }

        } else if (opcion == 3) {
            std::cout << "Programa finalizado.\n";

        } else {
            std::cout << "Opcion no valida. Intente nuevamente.\n";
        }

    } while (opcion != 3);

    return 0;
}