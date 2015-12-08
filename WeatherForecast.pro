TEMPLATE = app
TARGET = WeatherForecast
DEPENDPATH += .
INCLUDEPATH += .
QT += widgets

HEADERS += src/Form.h \
           src/Utils.h

SOURCES += src/Form.cpp \
           src/main.cpp \
           src/Utils.cpp

RESOURCES += WeatherForecast.qrc