#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndexList>

#include <point.h>
#include <project-settings.h>


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
    void on_draw3DplotButton_clicked();

    void on_saveDataButton_clicked();

    void on_readFileButton_clicked();

    void on_lumniousFluxButton_clicked();

    void on_photometricCurveButton_clicked();

    void on_sectionButton_clicked();

private:
    Ui::MainWindow *ui_;
    std::vector<Point> get_table_data();
    QList<QPointF> get_meridian_values(QModelIndexList selection, int i);
    QList<QPointF> get_meridian_section_values(int i, QModelIndexList selection);
    QString prepare_data_to_save();
    void setup_table_view(int columns_count_, int rows_count_);
    ProjectSettings project_settings_;
    unsigned rows_count_;
    unsigned columns_count_;
};

#endif // MAINWINDOW_H
