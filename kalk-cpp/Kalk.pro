#-------------------------------------------------
#
# Project created by QtCreator 2018-06-15T15:33:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Kalk
TEMPLATE = app
CONFIG += c++14
QMAKE_CXXFLAGS += -std=c++14

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    model/kalkmatrixmodel.cpp \
    model/kalkresultmatrixmodel.cpp \
    model/matrixinfoenumerator.cpp \
    utils/layout/label.cpp \
    utils/debug.cpp \
    view/commonoperationswidget.cpp \
    view/kalkboardwidget.cpp \
    view/kalkoperandboard.cpp \
    view/kalkoperandboardheader.cpp \
    view/logwidget.cpp \
    view/mainview.cpp \
    view/operandinfodialog.cpp \
    view/resultswidget.cpp \
    view/tabwidget.cpp \
    view/transformwidget.cpp \
    view/typechoicequestionwidget.cpp \
    view/typechoicewidget.cpp \
    viewmanager/kalkviewmanager.cpp \
    bootstrap.cpp \
    main.cpp \
    settings.cpp \
    model/settingsprovider.cpp \
    view/matrixtableview.cpp \
    view/inlineoperationrow.cpp

HEADERS += \
    lib/linearalgebra/exceptions/bad_cast.h \
    lib/linearalgebra/exceptions/illegal_dimensions.h \
    lib/linearalgebra/utils/list_utils.h \
    lib/linearalgebra/abstract_container.h \
    lib/linearalgebra/abstract_dense_matrix.h \
    lib/linearalgebra/abstract_diagonal_matrix.h \
    lib/linearalgebra/abstract_matrix.h \
    lib/linearalgebra/abstract_square_matrix.h \
    lib/linearalgebra/dense_diagonal_matrix.h \
    lib/linearalgebra/dense_matrix.h \
    lib/linearalgebra/dense_square_matrix.h \
    lib/linearalgebra/i_container.h \
    lib/linearalgebra/i_diagonal_matrix.h \
    lib/linearalgebra/i_matrix.h \
    lib/linearalgebra/i_square_matrix.h \
    lib/linearalgebra/linear_algebra.fwd.h \
    lib/linearalgebra/linear_algebra.h \
    model/kalkmatrixmodel.h \
    model/kalkresultmatrixmodel.h \
    model/matrixinfoenumerator.h \
    model/resultdestination.h \
    utils/layout/button.h \
    utils/layout/label.h \
    utils/layout/layout.h \
    utils/layout/spinbox.h \
    utils/debug.h \
    utils/utils.h \
    view/commonoperationswidget.h \
    view/kalkboardwidget.h \
    view/kalkoperandboard.h \
    view/kalkoperandboardheader.h \
    view/logwidget.h \
    view/mainview.h \
    view/operandinfodialog.h \
    view/resultswidget.h \
    view/tabwidget.h \
    view/transformwidget.h \
    view/typechoicequestionwidget.h \
    view/typechoicewidget.h \
    viewmanager/kalkviewmanager.h \
    bootstrap.h \
    settings.h \
    model/settingsprovider.h \
    view/matrixtableview.h \
    view/inlineoperationrow.h

RESOURCES += \
    kalkresources.qrc

FORMS += \
        view/mainview.ui
