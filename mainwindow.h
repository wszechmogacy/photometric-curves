#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "point.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_horizontalSectionButton_clicked();

    void on_verticalSectionButton_clicked();

    void on_calculateAreaButton_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<Point> getTableData();
};

#endif // MAINWINDOW_H
