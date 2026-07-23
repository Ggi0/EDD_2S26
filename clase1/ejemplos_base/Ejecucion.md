# Manual Técnico
## Compilación y ejecución de ejemplos en C++

### Requisitos

Antes de ejecutar los ejemplos es necesario contar con un compilador de C++ instalado en el sistema. Se recomienda utilizar alguno de los siguientes:

- **g++** (GNU Compiler Collection)
- **clang++** (LLVM Clang)

### Compilación

Para generar el archivo ejecutable se utiliza el siguiente comando:

```bash
g++ ejemplo1.cpp -o ejemplo1
```

#### Descripción de los parámetros

| Parámetro | Descripción |
|-----------|-------------|
| `g++` | Compilador de C++. |
| `ejemplo1.cpp` | Archivo fuente que será compilado. |
| `-o ejemplo1` | Define el nombre del archivo ejecutable generado. |

Al finalizar este proceso, el compilador traduce el código fuente a código máquina y genera el ejecutable correspondiente.

### 3. Ejecución

Una vez compilado, el programa puede ejecutarse con el siguiente comando:

```bash
./ejemplos_base/ejemplo1
```

En sistemas Linux y macOS, el prefijo `./` indica que el ejecutable se encuentra en el directorio especificado.


### ejecutar todo desde un solo comando desde la carpetal `clase1/`:
```bash
g++ ejemplos_base/ejemplo1.cpp -o ejemplos_base/ejemplo1 && ./ejemplos_base/ejemplo1
```

para los otros archivos:
```bash
gio@MacBook-Pro-de-Gio clase1 % g++ ejemplos_base/ejemplo2.cpp -o ejemplos_base/ejemplo2 && ./ejemplos_base/ejemplo2
```

desde la carpeta `ejemplos_base`:
```bash
gio@MacBook-Pro-de-Gio ejemplos_base % g++ ejemplo3.cpp -o ejemplo3 && ./ejemplo3  
```




### Flujo de trabajo

1. Crear o modificar el archivo fuente (`.cpp`).
2. Compilar el programa utilizando `g++`.
3. Verificar que el ejecutable se haya generado correctamente.
4. Ejecutar el programa desde la terminal.