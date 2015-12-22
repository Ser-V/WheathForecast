TEMPLATE = app
TARGET = WeatherForecast
DEPENDPATH += .
INCLUDEPATH += .
QT += widgets

win32:RC_ICONS += resources/images/Weather.ico

HEADERS += src/Form.h \
           src/Utils.h

SOURCES += src/Form.cpp \
           src/main.cpp \
           src/Utils.cpp

RESOURCES += WeatherForecast.qrc

TRANSLATIONS += translations/weatherforecast_ru.ts