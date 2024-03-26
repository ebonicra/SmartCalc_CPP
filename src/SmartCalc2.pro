QT       += core gui widgets printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += ./view

SOURCES += \
    controller/controller.cc \
    main.cc \
    view/credit.cc \
    view/deposit.cc \
    view/mainwindow.cc \
    view/qcustomplot.cc \
    model/token.cc \
    model/maincalculator.cc \
    model/creditcalculator.cc \
    model/date.cc \
    model/depositcalculator.cc \


HEADERS += \
    controller/controller.h \
    view/credit.h \
    view/deposit.h \
    view/mainwindow.h \
    view/qcustomplot.h \
    model/token.h \
    model/maincalculator.h \
    model/creditcalculator.h \
    model/date.h \
    model/depositcalculator.h \

FORMS += \
    view/credit.ui \
    view/deposit.ui \
    view/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
