#include <QApplication>
#include <QTranslator>
#include <QDebug>

#include <main-window.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    translator.load("./photometric-curves-pl.qm");
    a.installTranslator(&translator);

    MainWindow *w = new MainWindow();
    if (w != nullptr)  w->show();


    return a.exec();
}
