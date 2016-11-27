#include "introduction-dialog-window.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    IntroductionDialogWindow intro;
    intro.exec();

    MainWindow w;
    w.show();

    return a.exec();
}
