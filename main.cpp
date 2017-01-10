#include <QApplication>
#include <QTranslator>
#include <QDebug>

#include <main-window.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    translator.load("/home/tomasz/devel/photometric-curves/photometric-curves-pl.qm");
    a.installTranslator(&translator);

    MainWindow *w = new MainWindow();
    w->show();

    return a.exec();
}
