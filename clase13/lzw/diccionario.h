
#ifndef DICCIONARIO_H
#define DICCIONARIO_H

#include <string>
#include <unordered_map>
#include <vector>
#include <cstdint>

class Diccionario {
private:
    // Relaciona una secuencia de bytes con su código.
    std::unordered_map<std::string, uint16_t> secuenciaACodigo;

    // Relaciona un código con su secuencia de bytes.
    std::vector<std::string> codigoASecuencia;

    // Próximo código disponible para una secuencia nueva.
    uint32_t siguienteCodigo;

public:
    static constexpr uint32_t CODIGO_FIN = 256;
    static constexpr uint32_t PRIMER_CODIGO_NUEVO = 257;
    static constexpr uint32_t MAX_CODIGOS = 65536;

    Diccionario();

    // Comprueba si una secuencia ya existe.
    bool contieneSecuencia(const std::string& secuencia) const;

    // Obtiene el código correspondiente a una secuencia.
    uint16_t obtenerCodigo(const std::string& secuencia) const;

    // Obtiene la secuencia correspondiente a un código.
    bool obtenerSecuencia(uint16_t codigo,
                          std::string& secuencia) const;

    // Agrega una secuencia nueva al diccionario.
    bool agregar(const std::string& secuencia);

    // Indica cuál es el próximo código disponible.
    uint32_t obtenerSiguienteCodigo() const;
};

#endif
