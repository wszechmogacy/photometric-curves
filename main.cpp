#include <QApplication>
#include <QTranslator>
#include <QDebug>

#include <main-window.h>

void setPolishLanguage(QApplication &a)
{
    QTranslator translator;
    translator.load("photometric-curves-pl.qm");
    a.installTranslator(&translator);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auto language = QLocale::system().name();

    QString fileName("photometric-curves-");
    fileName.append(language);
    fileName.append(".qm");

    auto translator = new QTranslator();
    translator->load(fileName);
    a.installTranslator(translator);
    qDebug() << "lan: " << fileName;

    MainWindow *w = new MainWindow(translator);
    if (w != nullptr)  w->show();

    return a.exec();
}
