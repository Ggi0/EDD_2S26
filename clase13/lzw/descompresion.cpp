
#include "descompresion.h"
#include "diccionario.h"

#include <fstream>
#include <iostream>
#include <filesystem>
#include <cstdint>
#include <string>

// Lee códigos de ancho variable, bit por bit.
class LectorBits {
private:
    std::ifstream& entrada;
    uint8_t byteActual = 0;
    int bitsRestantes = 0;

public:
    explicit LectorBits(std::ifstream& archivo) : entrada(archivo) {}

    bool leer(int ancho, uint16_t& codigo) {
        codigo = 0;

        for (int i = 0; i < ancho; ++i) {
            if (bitsRestantes == 0) {
                char byte;

                if (!entrada.get(byte)) {
                    return false;
                }

                byteActual = static_cast<uint8_t>(
                    static_cast<unsigned char>(byte)
                );

                bitsRestantes = 8;
            }

            // Lee desde el bit más significativo.
            int bit = (byteActual >> (bitsRestantes - 1)) & 1;

            codigo = static_cast<uint16_t>(
                (codigo << 1) | bit
            );

            bitsRestantes--;
        }

        return true;
    }
};

bool descomprimirArchivo(
    const std::string& rutaComprimida,
    const std::string& rutaDescomprimida) {

    namespace fs = std::filesystem;

    std::ifstream entrada(rutaComprimida, std::ios::binary);

    if (!entrada) {
        std::cerr << "Error: no se pudo abrir el archivo comprimido.\n";
        return false;
    }

    // Comprueba la cabecera para evitar leer archivos ajenos al formato.
    char cabecera[4];

    if (!entrada.read(cabecera, 4) ||
        std::string(cabecera, 4) != "LZW1") {
        std::cerr << "Error: el archivo no tiene una cabecera LZW1 válida.\n";
        return false;
    }

    fs::path destino(rutaDescomprimida);

    if (destino.has_parent_path()) {
        fs::create_directories(destino.parent_path());
    }

    std::ofstream salida(
        rutaDescomprimida,
        std::ios::binary | std::ios::trunc
    );

    if (!salida) {
        std::cerr << "Error: no se pudo crear el archivo de salida.\n";
        return false;
    }

    Diccionario diccionario;
    LectorBits lector(entrada);

    int ancho = 9;
    uint16_t codigo;

    // Lee el primer código.
    if (!lector.leer(ancho, codigo)) {
        std::cerr << "Error: el archivo no contiene códigos LZW.\n";
        return false;
    }

    // Un código de fin al inicio representa un archivo vacío.
    if (codigo == Diccionario::CODIGO_FIN) {
        salida.close();
        return static_cast<bool>(salida);
    }

    std::string anterior;

    if (!diccionario.obtenerSecuencia(codigo, anterior)) {
        std::cerr << "Error: el primer código no es válido.\n";
        return false;
    }

    salida.write(
        anterior.data(),
        static_cast<std::streamsize>(anterior.size())
    );

    while (lector.leer(ancho, codigo)) {
        if (codigo == Diccionario::CODIGO_FIN) {
            salida.close();
            return static_cast<bool>(salida);
        }

        std::string actual;

        if (diccionario.obtenerSecuencia(codigo, actual)) {
            // El código ya existe en el diccionario.
        } else if (
            codigo == diccionario.obtenerSiguienteCodigo() &&
            diccionario.obtenerSiguienteCodigo() <
                Diccionario::MAX_CODIGOS) {

            // Caso especial de LZW:
            // la secuencia es anterior + primer byte de anterior.
            actual = anterior + anterior[0];
        } else {
            std::cerr << "Error: código inválido en el archivo.\n";
            return false;
        }

        salida.write(
            actual.data(),
            static_cast<std::streamsize>(actual.size())
        );

        // Reconstruye la entrada que el compresor agregó.
        if (diccionario.obtenerSiguienteCodigo() <
            Diccionario::MAX_CODIGOS) {

            std::string nueva =
                anterior + actual[0];

            diccionario.agregar(nueva);

            // El descompresor agrega una entrada después
            // de leer el código actual. Por eso el ajuste
            // de ancho debe compensar el retraso de una entrada.
            if (ancho < 16 &&
                diccionario.obtenerSiguienteCodigo() ==
                    ((1u << ancho) - 1)) {
                ancho++;
            }
        }

        anterior = actual;
    }

    // Llegar al final físico sin el código de fin indica
    // un archivo incompleto o dañado.
    std::cerr << "Error: falta el código de fin del archivo.\n";
    return false;
}
