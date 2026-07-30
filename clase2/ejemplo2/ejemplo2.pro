QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    ../doubly_linked_list/Nodo.cpp \
    ../doubly_linked_list/doubly_linked_list.cpp \
    ../pelicula/pelicula.cpp \
    ventana2.cpp \
    ventana3.cpp

HEADERS += \
    mainwindow.h \
    ../doubly_linked_list/Nodo.h \
    ../doubly_linked_list/doubly_linked_list.h \
    ../pelicula/pelicula.h \
    ventana2.h \
    ventana3.h

FORMS += \
    mainwindow.ui \
    ventana2.ui \
    ventana3.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
