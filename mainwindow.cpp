#include "mainwindow.h"
#include "ui_mainwindow.h"

#define ROW_COUNT 18
#define COLUMN_COUNT 18

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->dataTable->setRowCount(ROW_COUNT);
    ui->dataTable->setColumnCount(COLUMN_COUNT);


    QStringList horizontal_label;
    for(size_t col = 0; col < COLUMN_COUNT; col++) {
        horizontal_label.append(QString::number(180*col/COLUMN_COUNT));
    }
    ui->dataTable->setHorizontalHeaderLabels(horizontal_label);

    QStringList vertical_label;
    for(size_t row = 0; row < ROW_COUNT; row++) {
        vertical_label.append(QString::number(360*row/ROW_COUNT));
    }
    ui->dataTable->setVerticalHeaderLabels(vertical_label);

    for(size_t col = 0; col < COLUMN_COUNT; col++) {
        for(size_t row = 0; row < ROW_COUNT; row++) {
            ui->dataTable->setItem(row, col, new QTableWidgetItem(QString(QString::number((col + row)*0.54 + 2.4))));
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
