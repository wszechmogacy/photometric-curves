#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndexList>
#include <QTextStream>

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
    void on_horizontalSectionButton_clicked();

    void on_verticalSectionButton_clicked();

    void on_calculateAreaButton_clicked();

    void on_draw3DplotButton_clicked();

    void on_saveDataButton_clicked();

    void on_readFileButton_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<Point> getTableData();
    ProjectSettings project_settings;
    unsigned rows_count;
    unsigned columns_count;
    QList<QPointF> get_meridian_values(QModelIndexList selection, int i);
    QList<QPointF> get_meridian_section_values(int i, QModelIndexList selection);
    QString prepare_data_to_save();
    void setup_table_view(int columns_count, int rows_count);
    void put_data_to_table(QTextStream &stream);
    void get_desired_table_dimension(QTextStream &stream, unsigned columns_count, unsigned rows_count);
};

#endif // MAINWINDOW_H
