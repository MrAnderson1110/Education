#------------------------------------------------------------------------------#

ROOT_DIR = $${PWD}/..                           # путь к корневой директории проекта
SRC_DIR = $${ROOT_DIR}/src                      # путь к исходным текстам
LIBS_DIR = $${ROOT_DIR}/libs                    # путь к собранным библиотекам
PLUGINS_DIR = $${ROOT_DIR}/plugins              # путь к собранным плагинам

#------------------------------------------------------------------------------#

CONFIG -= debug_and_release debug_and_release_target
CONFIG += ordered

TEMPLATE = subdirs

SUBDIRS +=  $$SRC_DIR/core \
            $$SRC_DIR/services \
            $$SRC_DIR/game \



QML_IMPORT_PATH += $${PLUGINS_DIR} $${SRC_DIR}

#------------------------------------------------------------------------------#
