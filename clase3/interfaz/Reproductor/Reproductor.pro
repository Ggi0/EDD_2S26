QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    ../../lista_circular/lista_circular.cpp \
    ../../lista_circular/NodoCircular.cpp \
    ../../lista_doble/Lista_doble.cpp \
    ../../lista_doble/Nodo.cpp \
    ../../cancion/cancion.cpp \
    ../../cantante/cantante.cpp

HEADERS += \
    mainwindow.h \
    ../../lista_circular/lista_circular.h \
    ../../lista_circular/NodoCircular.h \
    ../../lista_doble/Lista_doble.h \
    ../../cancion/cancion.h \
    ../../cantante/cantante.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
