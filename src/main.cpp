#include <QApplication>
#include <QResource>
#include <QTextCodec>

#include "Form.h"

int main(int argc, char *argv[])
{
   QApplication app(argc, argv);

   QResource resource(":/Skins/ui-dark-orange");
   QByteArray data((const char*) resource.data(), resource.size());
    if (resource.isCompressed())
      data = qUncompress(data);
   QString css = QTextCodec::codecForLocale()->toUnicode(data);
   app.setStyleSheet(css);

   Form form;
   form.show();
   return app.exec();
}