
#include "compresion.h"
#include "diccionario.h"

#include <fstream>
#include <iostream>
#include <filesystem>
#include <algorithm>
#include <cstdint>
#include <string>

// Escribe códigos de ancho variable, bit por bit.
// Los bits se escriben desde el más significativo al menos significativo.
class EscritorBits {
private:
    std::ofstream& salida;
    uint8_t byteActual = 0;
    int bitsOcupados = 0;

public:
    explicit EscritorBits(std::ofstream& archivo) : salida(archivo) {}

    void escribir(uint16_t codigo, int ancho) {
        for (int i = ancho - 1; i >= 0; --i) {
            int bit = (codigo >> i) & 1;

            byteActual = static_cast<uint8_t>(
                (byteActual << 1) | bit
            );

            bitsOcupados++;

            // Al completar ocho bits, se escribe un byte.
            if (bitsOcupados == 8) {
                salida.put(static_cast<char>(byteActual));
                byteActual = 0;
                bitsOcupados = 0;
            }
        }
    }

    void finalizar() {
        // Completa el último byte con ceros si hace falta.
        if (bitsOcupados > 0) {
            byteActual = static_cast<uint8_t>(
                byteActual << (8 - bitsOcupados)
            );

            salida.put(static_cast<char>(byteActual));
            byteActual = 0;
            bitsOcupados = 0;
        }
    }
};

bool comprimirArchivo(
    const std::string& rutaOriginal,
    const std::string& rutaComprimida,
    uint64_t& tamanoOriginal,
    uint64_t& tamanoComprimido) {

    namespace fs = std::filesystem;

    tamanoOriginal = 0;
    tamanoComprimido = 0;

    std::ifstream entrada(rutaOriginal, std::ios::binary);

    if (!entrada) {
        std::cerr << "Error: no se pudo abrir el archivo original.\n";
        return false;
    }

    // Crea el directorio de salida si todavía no existe.
    fs::path destino(rutaComprimida);

    if (destino.has_parent_path()) {
        fs::create_directories(destino.parent_path());
    }

    std::ofstream salida(
        rutaComprimida,
        std::ios::binary | std::ios::trunc
    );

    if (!salida) {
        std::cerr << "Error: no se pudo crear el archivo comprimido.\n";
        return false;
    }

    // Cabecera propia del formato de este proyecto.
    // Permite identificar archivos creados por nuestro compresor.
    salida.write("LZW1", 4);

    EscritorBits escritor(salida);
    Diccionario diccionario;

    tamanoOriginal = fs::file_size(rutaOriginal);

    char caracter;

    // Si el archivo está vacío, solo se escribe el código de fin.
    if (!entrada.get(caracter)) {
        escritor.escribir(
            static_cast<uint16_t>(Diccionario::CODIGO_FIN), 9
        );
        escritor.finalizar();
        salida.close();

        tamanoComprimido = fs::file_size(rutaComprimida);
        return static_cast<bool>(salida);
    }

    // La primera secuencia contiene el primer byte.
    std::string secuencia(1, caracter);

    int ancho = 9;

    while (entrada.get(caracter)) {
        std::string ampliada = secuencia + caracter;

        if (diccionario.contieneSecuencia(ampliada)) {
            // Si la secuencia existe, seguimos ampliándola.
            secuencia = ampliada;
        } else {
            // La secuencia actual se representa con su código.
            escritor.escribir(
                diccionario.obtenerCodigo(secuencia), ancho
            );

            // Se registra la nueva combinación.
            if (diccionario.obtenerSiguienteCodigo() <
                Diccionario::MAX_CODIGOS) {

                diccionario.agregar(ampliada);

                // Se aumenta el ancho cuando ya se necesita
                // representar el siguiente código disponible.
                if (ancho < 16 &&
                    diccionario.obtenerSiguienteCodigo() ==
                        (1u << ancho)) {
                    ancho++;
                }
            }

            // La secuencia vuelve a comenzar con el byte actual.
            secuencia = std::string(1, caracter);
        }
    }

    // Emite la última secuencia pendiente.
    escritor.escribir(
        diccionario.obtenerCodigo(secuencia), ancho
    );

    // Indica al descompresor que no quedan más códigos.
    escritor.escribir(
        static_cast<uint16_t>(Diccionario::CODIGO_FIN), ancho
    );

    escritor.finalizar();
    salida.close();

    if (!salida) {
        std::cerr << "Error al escribir el archivo comprimido.\n";
        return false;
    }

    tamanoComprimido = fs::file_size(rutaComprimida);

    return true;
}
