cmake_minimum_required(VERSION 3.15)

project(backend_crow)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES

    main.cpp

    # Controllers
    controllers/cantante_controller.cpp

    # Services
    services/cantante_service.cpp

    # Estructuras
    estructuras/cantante/cantante.cpp
    estructuras/cancion/cancion.cpp

    estructuras/lista_circular/lista_circular.cpp
    estructuras/lista_circular/NodoCircular.cpp

    estructuras/lista_doble/Lista_doble.cpp
    estructuras/lista_doble/Nodo.cpp

    data/datos_iniciales.cpp
)



add_executable(backend ${SOURCES})

target_include_directories(backend PRIVATE

    ${CMAKE_CURRENT_SOURCE_DIR}

    ${CMAKE_CURRENT_SOURCE_DIR}/../Crow/include

    /opt/local/include
)

target_link_libraries(
    backend
    PRIVATE
    pthread
)