#------------------------------------------------------------------------------#

ROOT_DIR = $${PWD}/../..                       # путь к корневой директории проекта
SRC_DIR = $${ROOT_DIR}/src                     # путь к исходным текстам
LIBS_DIR = $${ROOT_DIR}/libs                   # путь к собранным библиотекам
PLUGINS_DIR = $${ROOT_DIR}/plugins             # путь к собранным плагинам

#------------------------------------------------------------------------------#

PRO_NAME = game

TARGET = $${PRO_NAME}

TEMPLATE = app
QT += core gui svg qml quick
CONFIG -= debug_and_release debug_and_release_target
DESTDIR = $${ROOT_DIR}/app
DEFINES += $${upper($$TARGET)}_LIB

include($${PRO_NAME}.pri)

INCLUDEPATH += $${SRC_DIR}/$${PRO_NAME}

LIBS += -L$${LIBS_DIR}/ -lcore
INCLUDEPATH += $${SRC_DIR}/core
INCLUDEPATH += $${SRC_DIR}/core/include

LIBS += -L$${LIBS_DIR}/ -lservices
INCLUDEPATH += $${SRC_DIR}/services

#------------------------------------------------------------------------------#

MOC_DIR = $${ROOT_DIR}/build-$${QT_VERSION}/$${TARGET}
OBJECTS_DIR = $${ROOT_DIR}/build-$${QT_VERSION}/$${TARGET}
UI_DIR = $${ROOT_DIR}/build-$${QT_VERSION}/$${TARGET}

