
#ifndef COMPRESION_H
#define COMPRESION_H

#include <string>
#include <cstdint>

bool comprimirArchivo(
    const std::string& rutaOriginal,
    const std::string& rutaComprimida,
    uint64_t& tamanoOriginal,
    uint64_t& tamanoComprimido
);

#endif
