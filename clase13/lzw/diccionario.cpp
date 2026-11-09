
#include "diccionario.h"

Diccionario::Diccionario() {
    // Los códigos del 0 al 255 representan bytes individuales.
    codigoASecuencia.resize(256);

    for (int i = 0; i < 256; i++) {
        codigoASecuencia[i] = std::string(1, static_cast<char>(i));
        secuenciaACodigo[codigoASecuencia[i]] =
            static_cast<uint16_t>(i);
    }

    // El código 256 se reserva para indicar el final del archivo.
    siguienteCodigo = PRIMER_CODIGO_NUEVO;
}

bool Diccionario::contieneSecuencia(
    const std::string& secuencia) const {

    return secuenciaACodigo.find(secuencia) !=
           secuenciaACodigo.end();
}

uint16_t Diccionario::obtenerCodigo(
    const std::string& secuencia) const {

    auto it = secuenciaACodigo.find(secuencia);

    if (it != secuenciaACodigo.end()) {
        return it->second;
    }

    return 0;
}

bool Diccionario::obtenerSecuencia(
    uint16_t codigo,
    std::string& secuencia) const {

    if (codigo >= codigoASecuencia.size()) {
        return false;
    }

    // Las entradas vacías no son códigos válidos de secuencia.
    if (codigo == CODIGO_FIN ||
        codigoASecuencia[codigo].empty()) {
        return false;
    }

    secuencia = codigoASecuencia[codigo];
    return true;
}

bool Diccionario::agregar(const std::string& secuencia) {
    if (siguienteCodigo >= MAX_CODIGOS) {
        return false;
    }

    // Evita agregar dos veces la misma secuencia.
    if (contieneSecuencia(secuencia)) {
        return false;
    }

    uint16_t codigo = static_cast<uint16_t>(siguienteCodigo);

    secuenciaACodigo[secuencia] = codigo;

    if (codigoASecuencia.size() <= codigo) {
        codigoASecuencia.resize(codigo + 1);
    }

    codigoASecuencia[codigo] = secuencia;
    siguienteCodigo++;

    return true;
}

uint32_t Diccionario::obtenerSiguienteCodigo() const {
    return siguienteCodigo;
}
