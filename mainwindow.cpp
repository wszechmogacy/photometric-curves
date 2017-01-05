#include <algorithm>
#include <QDialog>
#include <QDebug>
#include <QFileDialog>
#include <QPointF>
#include <QString>
#include <QVector2D>
#include <QWidget>
#include <vector>

#include <introduction-dialog-window.h>
#include <luminous-flux-calculator.h>
#include <luminous-flux-window.h>
#include <mainwindow.h>
#include <point.h>
#include <polar-graph-window.h>
#include <project-settings.h>
#include <surface-window.h>
#include <ui_mainwindow.h>


void MainWindow::setup_table_view(int columns_count, int rows_count)
{
    ui->dataTable->setRowCount(rows_count);
    ui->dataTable->setColumnCount(columns_count);

    QStringList horizontal_label;
    for(size_t col = 0; col <= columns_count; col++) {
        horizontal_label.append(QString::number(90*col/columns_count));
    }
    ui->dataTable->setHorizontalHeaderLabels(horizontal_label);

    QStringList vertical_label;
    for(size_t row = 0; row < rows_count; row++) {
        vertical_label.append(QString::number(360*row/rows_count));
    }
    ui->dataTable->setVerticalHeaderLabels(vertical_label);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{setWindowTitle("Photometric Curves Calculator");
    ui->setupUi(this);

    IntroductionDialogWindow intro(&project_settings);
    intro.exec();

    rows_count = 360 / project_settings.step_in_parallel;
    columns_count = 90 / project_settings.step_in_meridian;

    qDebug() << "col: " << QString::number(columns_count) << QString::number(rows_count);
    setup_table_view(columns_count, rows_count);

    for(size_t col = 0; col <= columns_count; col++) {
        for(size_t row = 0; row < rows_count; row++) {
          //  ui->dataTable->setItem(row, col, new QTableWidgetItem(QString(QString::number((col + row)*0.54 + 2.4))));
             ui->dataTable->setItem(row, col, new QTableWidgetItem(QString(QString::number(1))));
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


QList<QPointF> MainWindow::get_meridian_section_values(int i, QModelIndexList selection)
{
    QModelIndex index = selection.at(i);

    QList<QPointF> vec;
    for (unsigned angle = 0; angle < 90; angle += project_settings.step_in_meridian) {
        QString next_val_txt = ui->dataTable->item(index.row(), angle / project_settings.step_in_meridian)->text();
        QString prev_val_txt = ui->dataTable->item( (ui->dataTable->rowCount() / 2 + index.row()) % ui->dataTable->rowCount(), angle / project_settings.step_in_meridian)->text();
        QLocale c(QLocale::C);
        double next_val = c.toDouble(next_val_txt);
        double prev_val = c.toDouble(prev_val_txt);
        vec.append(QPointF(next_val, angle));
        vec.prepend(QPointF(prev_val, (-1.0) * angle));
    }

    return vec;
}

void MainWindow::on_photometricCurveButton_clicked()
{
    QModelIndexList selection = ui->dataTable->selectionModel()->selectedRows();

    for(int i=0; i< selection.count(); i++)
    {
        QList<QPointF> vec = get_meridian_section_values(i, selection);

        PolarGraphWindow *polar_graph = new PolarGraphWindow(GraphType::curve,vec);
        polar_graph->show();
    }

}

void MainWindow::on_sectionButton_clicked()
{
    QModelIndexList selection = ui->dataTable->selectionModel()->selectedColumns();

    for(int i=0; i< selection.count(); i++)
    {
        QModelIndex index = selection.at(i);

        QList<QPointF> vec;
        for (unsigned j = 0; j < rows_count; j++) {
            QString txt = ui->dataTable->item(j, index.column())->text();
            QLocale c(QLocale::C);
            double d = c.toDouble(txt);

            vec.append(QPointF(d, 360 / rows_count * j));
        }
        QLocale n(QLocale::C);
        double first_raw_item_value = n.toDouble(ui->dataTable->item(0, index.column())->text());
        vec.append(QPointF(first_raw_item_value, 0));
        PolarGraphWindow *polar_graph = new PolarGraphWindow(GraphType::section, vec);
        polar_graph->show();
    }
}

void MainWindow::on_lumniousFluxButton_clicked()
{
    //get data from table
    auto table_data = MainWindow::getTableData();
    const double sphere_radius = project_settings.radius;
        //TODO: set radius as below, for now, I am using radius=1 to debug calculation
    //LuminousFluxCalculator flux_calculator(sphere_radius);
    LuminousFluxCalculator flux_calculator(1.0);
    double luminous_flux = flux_calculator(table_data, columns_count);

    LuminousFluxWindow window(luminous_flux, project_settings.units);
    window.exec();
}

std::vector<Point> MainWindow::getTableData()
{
    std::vector<Point> table_data;

    for(size_t row = 0; row < rows_count; row++) {
        for(size_t column = 0; column < columns_count; column++) {
            QString meridianName = ui->dataTable->horizontalHeaderItem(column)->text();
            QString parallelName = ui->dataTable->verticalHeaderItem(row)->text();
            QString valueName =  ui->dataTable->item(row, column)->text();
            //TODO: handle return values from toDouble (
            table_data.emplace_back(parallelName.toDouble(),
                                    meridianName.toDouble(),
                                    valueName.toDouble()
                                    );
        }
        //TODO : hack to fill with "estimated value at the end of range"
        // please replace this with esitmation
        table_data.emplace_back(ui->dataTable->verticalHeaderItem(row)->text().toDouble(), 90.0, 1.0);
    }

    return table_data;
}

void MainWindow::on_draw3DplotButton_clicked()
{
    auto table_data = MainWindow::getTableData();
    SurfaceWindow *window = new SurfaceWindow(table_data, columns_count, rows_count);
    window->show();
}

QString MainWindow::prepare_data_to_save()
{
    QString textData;
    int rows = ui->dataTable->rowCount();
    int columns = ui->dataTable->columnCount();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {

            textData += ui->dataTable->item(i,j)->text();
            textData += ", ";
        }
        textData += "\n";
    }

    return textData;
}

void MainWindow::on_saveDataButton_clicked()
{
    QString textData = prepare_data_to_save();
    QString file_name = QFileDialog::getSaveFileName(this, tr("Open File"), ".", tr("CSV Files (*.csv)"));
    if (!file_name.endsWith(".csv")) {
        file_name.append(".csv");
    }

    QFile csv_file(file_name);
    if(csv_file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {

        QTextStream stream(&csv_file);
        stream << textData;

        csv_file.close();
    }
}

void MainWindow::on_readFileButton_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("CSV Files (*.csv)"));
    qDebug() << "file: " << file_name;
    QFile csv_file(file_name);
    csv_file.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream stream(&csv_file);
    unsigned rows_count = 0;
    unsigned columns_count = 0;


    while (!stream.atEnd()) {
        QString line = stream.readLine();
        QStringList list = line.split(",");
        columns_count = list.count() - 1;
        rows_count++;
    }
    project_settings.step_in_meridian = 90 / columns_count;
    project_settings.step_in_parallel = 360 / rows_count;
    this->columns_count = columns_count;
    this->rows_count = rows_count;

    qDebug() << "steps: " << QString::number(project_settings.step_in_meridian) << QString::number(project_settings.step_in_parallel);

    setup_table_view(columns_count, rows_count);


    stream.seek(0);


    int row = 0;
    while (!stream.atEnd()) {
        QString line = stream.readLine();
        QStringList list = line.split(",");
        for(int col = 0; col < list.count(); col++) {
            ui->dataTable->setItem(row, col, new QTableWidgetItem(list[col]));
        }
        row++;
    }

    csv_file.close();
}
