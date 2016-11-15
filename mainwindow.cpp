#include <QDebug>
#include <QWidget>
#include <QDialog>
#include <QPointF>
#include <QVector2D>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "polar-graph-window.h"
#include "point.h"

#define ROW_COUNT 18
#define COLUMN_COUNT 18

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{setWindowTitle("WIlcze okno");
    ui->setupUi(this);
    ui->dataTable->setRowCount(ROW_COUNT);
    ui->dataTable->setColumnCount(COLUMN_COUNT + 1);

    QStringList horizontal_label;
    for(size_t col = 0; col <= COLUMN_COUNT; col++) {
        horizontal_label.append(QString::number(180*col/COLUMN_COUNT));
    }
    ui->dataTable->setHorizontalHeaderLabels(horizontal_label);

    QStringList vertical_label;
    for(size_t row = 0; row < ROW_COUNT; row++) {
        vertical_label.append(QString::number(360*row/ROW_COUNT));
    }
    ui->dataTable->setVerticalHeaderLabels(vertical_label);

    for(size_t col = 0; col <= COLUMN_COUNT; col++) {
        for(size_t row = 0; row < ROW_COUNT; row++) {
            ui->dataTable->setItem(row, col, new QTableWidgetItem(QString(QString::number((col + row)*0.54 + 2.4))));
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
        for (int j = 0; j < ROW_COUNT; j++) {
            QString txt = ui->dataTable->item(j, index.column())->text();
            QLocale c(QLocale::C);
            double d = c.toDouble(txt);

            vec.append(QPointF(d, 360 / ROW_COUNT * j));
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
        for (int j = 0; j <= COLUMN_COUNT; j++) {
            QString txt = ui->dataTable->item(index.row(), j)->text();
            QLocale c(QLocale::C);
            double d = c.toDouble(txt);

            vec.append(QPointF(d, 180 / COLUMN_COUNT * j));
        }
        PolarGraphWindow *polar_graph = new PolarGraphWindow(vec);
        polar_graph->resize(800,600);
        polar_graph->show();
    }
}

void MainWindow::on_calculateAreaButton_clicked()
{
    int row_count = ui->dataTable->rowCount();
    int column_count = ui->dataTable->columnCount();

    for(size_t row = 0; row < row_count; row++) {
        for(size_t column = 0; column < column_count; column++) {
            qDebug() << ui->dataTable->item(row, column)->text();
        }
    }


    ui->dataTable->setCurrentCell(0, 0);
    ui->dataTable->row();

}
