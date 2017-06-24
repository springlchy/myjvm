TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    main.c

HEADERS += \
    structs.h \
    utils.h \
    constants.h \
    jvm_debug.h \
    opcode.h \
    my_types.h \
    op_core.h \
    class_hash.h \
    method_table.h

