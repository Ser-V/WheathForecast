#include <QApplication>
#include <QResource>
#include <QTextCodec>
#include <QTranslator>

#include "Form.h"

int main(int argc, char *argv[])
{
   QApplication app(argc, argv);

   QTranslator translator;
   translator.load(":/Translations/translation_ru");
   app.installTranslator(&translator);
   //*
   QResource resource(":/Skins/d-theme-blue");
   QByteArray data((const char*) resource.data(), resource.size());
    if (resource.isCompressed())
      data = qUncompress(data);
   QString css = QTextCodec::codecForLocale()->toUnicode(data);
   app.setStyleSheet(css);
   /* */
   Form form;
   form.show();
   return app.exec();
}