#include <algorithm>
#include <QDebug>
#include <QWidget>
#include <QDialog>
#include <QPointF>
#include <QVector2D>
#include <vector>


#include "luminous-flux-calculator.h"
#include "luminous-flux-window.h"
#include "ui_luminous-flux-window.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "polar-graph-window.h"
#include "point.h"
#include "surface-window.h"
#include "introduction-dialog-window.h"
#include "ui_introduction-dialog-window.h"

const int PARALLEL_POINTS_COUNT = 36;
const int MERIDIAN_POINTS_COUNT = 9;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{setWindowTitle("Photometric Curves Calculator");
    ui->setupUi(this);

    IntroductionDialogWindow intro;
    intro.exec();

    ui->dataTable->setRowCount(PARALLEL_POINTS_COUNT);
    ui->dataTable->setColumnCount(MERIDIAN_POINTS_COUNT + 1);

    QStringList horizontal_label;
    for(size_t col = 0; col <= MERIDIAN_POINTS_COUNT; col++) {
        horizontal_label.append(QString::number(180*col/MERIDIAN_POINTS_COUNT));
    }
    ui->dataTable->setHorizontalHeaderLabels(horizontal_label);

    QStringList vertical_label;
    for(size_t row = 0; row < PARALLEL_POINTS_COUNT; row++) {
        vertical_label.append(QString::number(360*row/PARALLEL_POINTS_COUNT));
    }
    ui->dataTable->setVerticalHeaderLabels(vertical_label);

    for(size_t col = 0; col <= MERIDIAN_POINTS_COUNT; col++) {
        for(size_t row = 0; row < PARALLEL_POINTS_COUNT; row++) {
            ui->dataTable->setItem(row, col, new QTableWidgetItem(QString(QString::number((col + row)*0.54 + 2.4))));
             ui->dataTable->setItem(row, col, new QTableWidgetItem(QString(QString::number(1))));
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_horizontalSectionButton_clicked()
{
    QModelIndexList selection = ui->dataTable->selectionModel()->selectedColumns();

    for(int i=0; i< selection.count(); i++)
    {
        QModelIndex index = selection.at(i);

        QList<QPointF> vec;
        for (int j = 0; j < PARALLEL_POINTS_COUNT; j++) {
            QString txt = ui->dataTable->item(j, index.column())->text();
            QLocale c(QLocale::C);
            double d = c.toDouble(txt);

            vec.append(QPointF(d, 360 / PARALLEL_POINTS_COUNT * j));
        }
        QLocale n(QLocale::C);
        double first_raw_item_value = n.toDouble(ui->dataTable->item(0, index.column())->text());
        vec.append(QPointF(first_raw_item_value, 0));
        PolarGraphWindow *polar_graph = new PolarGraphWindow(vec);
        polar_graph->resize(800,600);
        polar_graph->show();
    }
}

void MainWindow::on_verticalSectionButton_clicked()
{
    QModelIndexList selection = ui->dataTable->selectionModel()->selectedRows();

    for(int i=0; i< selection.count(); i++)
    {
        QModelIndex index = selection.at(i);

        QList<QPointF> vec;
        for (int j = 0; j <= MERIDIAN_POINTS_COUNT; j++) {
            QString txt = ui->dataTable->item(index.row(), j)->text();
            QLocale c(QLocale::C);
            double d = c.toDouble(txt);

            vec.append(QPointF(d, 180 / MERIDIAN_POINTS_COUNT * j));
        }
        PolarGraphWindow *polar_graph = new PolarGraphWindow(vec);
        polar_graph->resize(800,600);
        polar_graph->show();
    }
}

void MainWindow::on_calculateAreaButton_clicked()
{
    //get data from table
    auto table_data = MainWindow::getTableData();
    const double sphere_radius = 1.0;
    LuminousFluxCalculator flux_calculator(sphere_radius);
    double luminous_flux = flux_calculator(table_data, MERIDIAN_POINTS_COUNT, PARALLEL_POINTS_COUNT);
    //show window with value
    qDebug() << "calculated flux =  " << QString::number(luminous_flux);
    QString units = "W/m^2";

    LuminousFluxWindow window;
    window.set_luminous_flux_value(luminous_flux);
    window.set_luminous_flux_units(units);
    window.exec();
}

std::vector<Point> MainWindow::getTableData()
{
    std::vector<Point> table_data;
    size_t row_count = ui->dataTable->rowCount();
    size_t column_count = ui->dataTable->columnCount();

    for(size_t row = 0; row < row_count; row++) {
        for(size_t column = 0; column < column_count; column++) {
            QString horizontalName = ui->dataTable->horizontalHeaderItem(column)->text();
            QString verticalName = ui->dataTable->verticalHeaderItem(row)->text();
            QString valueName =  ui->dataTable->item(row, column)->text();
            //TODO: handle return values from toDouble (
            table_data.emplace_back(horizontalName.toDouble(),
                                    verticalName.toDouble(),
                                    valueName.toDouble()
                                    );
        }
    }
    return table_data;

}

void MainWindow::on_draw3DplotButton_clicked()
{
    auto table_data = MainWindow::getTableData();
    SurfaceWindow *window = new SurfaceWindow(table_data);
}
