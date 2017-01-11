#include <algorithm>
#include <QDialog>
#include <QDebug>
#include <QFileDialog>
#include <QPointF>
#include <QString>
#include <QVector2D>
#include <QWidget>
#include <stdexcept>
#include <vector>

#include <introduction-dialog-window.h>
#include <luminous-flux-calculator.h>
#include <luminous-flux-window.h>
#include <main-window.h>
#include <point.h>
#include <polar-graph-window.h>
#include <project-settings.h>
#include <surface-window.h>
#include <ui_mainwindow.h>


void MainWindow::setup_table_view(int columns_count, int rows_count)
{
    if (rows_count == 0 || columns_count == 00) {
        throw std::runtime_error("Input data (columns or rows) are invalid");
    }

    ui_->dataTable->setRowCount(rows_count);
    ui_->dataTable->setColumnCount(columns_count);

    QStringList horizontal_label;
    for(int col = 0; col <= columns_count; col++) {
        horizontal_label.append(QString::number(90*col/columns_count));
    }
    ui_->dataTable->setHorizontalHeaderLabels(horizontal_label);

    QStringList vertical_label;
    for(int row = 0; row < rows_count; row++) {
        vertical_label.append(QString::number(360*row/rows_count));
    }
    ui_->dataTable->setVerticalHeaderLabels(vertical_label);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
    setWindowTitle(tr("Photometric Curves"));

    ui_->lumniousFluxButton->setText(tr("Luminous Flux"));
    ui_->photometricCurveButton->setText(tr("Photometric Curve"));
    ui_->readFileButton->setText(tr("Read data"));
    ui_->saveDataButton->setText(tr("Save to file"));
    ui_->sectionButton->setText(tr("Section"));
    ui_->draw3DplotButton->setText(tr("Photometric solid"));


    IntroductionDialogWindow intro(&project_settings_);
    intro.exec();

    if (project_settings_.step_in_parallel_dir_ == 0 || project_settings_.step_in_meridian_dir_ == 0) return;

    rows_count_ = 360 / project_settings_.step_in_parallel_dir_;
    columns_count_ = 90 / project_settings_.step_in_meridian_dir_;

    qDebug() << "col: " << QString::number(columns_count_) << QString::number(rows_count_);
    setup_table_view(columns_count_, rows_count_);

    for(size_t col = 0; col <= columns_count_; col++) {
        for(size_t row = 0; row < rows_count_; row++) {
            //ui_->dataTable->setItem(row, col, new QTableWidgetItem(QString(QString::number((col + row)*0.54 + 2.4))));
            //ui_->dataTable->setItem(row, col, new QTableWidgetItem(QString(QString::number(1))));
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui_;
}


QList<QPointF> MainWindow::get_meridian_section_values(int i, QModelIndexList selection)
{
    QModelIndex index = selection.at(i);

    QList<QPointF> vec;
    for (unsigned angle = 0; angle < 90; angle += project_settings_.step_in_meridian_dir_) {
        QString next_val_txt = ui_->dataTable->item(index.row(), angle / project_settings_.step_in_meridian_dir_)->text();
        QString prev_val_txt = ui_->dataTable->item( (ui_->dataTable->rowCount() / 2 + index.row()) % ui_->dataTable->rowCount(), angle / project_settings_.step_in_meridian_dir_)->text();
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
    QModelIndexList selection = ui_->dataTable->selectionModel()->selectedRows();

    for(int i=0; i< selection.count(); i++)
    {
        QList<QPointF> vec = get_meridian_section_values(i, selection);

        PolarGraphWindow *polar_graph = new PolarGraphWindow("Nazwa grafu", GraphType::curve, vec);
        polar_graph->show();
    }

}

void MainWindow::on_sectionButton_clicked()
{
    QModelIndexList selection = ui_->dataTable->selectionModel()->selectedColumns();

    for(int i=0; i< selection.count(); i++)
    {
        QModelIndex index = selection.at(i);

        QList<QPointF> vec;
        for (unsigned j = 0; j < rows_count_; j++) {
            QString txt = ui_->dataTable->item(j, index.column())->text();
            QLocale c(QLocale::C);
            double d = c.toDouble(txt);

            vec.append(QPointF(d, 360 / rows_count_ * j));
        }

        QLocale n(QLocale::C);
        double first_raw_item_value = n.toDouble(ui_->dataTable->item(0, index.column())->text());
        vec.append(QPointF(first_raw_item_value, 360));

        QString graph_name = "Section " + project_settings_.source_name_+ " for "
                + QString::number(90 / columns_count_ * selection.at(i).column()) + " deg";
        PolarGraphWindow *polar_graph = new PolarGraphWindow(graph_name, GraphType::section, vec);
        polar_graph->show();
    }
}

void MainWindow::on_lumniousFluxButton_clicked()
{
    //get data from table
    auto table_data = MainWindow::get_table_data();
    const double sphere_radius_m = project_settings_.radius_;
    LuminousFluxCalculator flux_calculator(sphere_radius_m);
    double luminous_flux = flux_calculator(table_data, project_settings_.units_scale_, columns_count_);

    LuminousFluxWindow window(luminous_flux);
    window.exec();
}

std::vector<Point> MainWindow::get_table_data()
{
    std::vector<Point> table_data;
    double last, prelast;
    for(size_t row = 0; row < rows_count_; row++) {
        for(size_t column = 0; column < columns_count_; column++) {
            QString meridianName = ui_->dataTable->horizontalHeaderItem(column)->text();
            QString parallelName = ui_->dataTable->verticalHeaderItem(row)->text();
            QString valueName =  ui_->dataTable->item(row, column)->text();
            //TODO: handle return values from toDouble (
            table_data.emplace_back(parallelName.toDouble(),
                                    meridianName.toDouble(),
                                    valueName.toDouble()
                                    );

            if (column == columns_count_ - 1) last = valueName.toDouble();
            if (column == columns_count_ - 2) prelast = valueName.toDouble();
        }
        if (columns_count_ > 2) {
            table_data.emplace_back(ui_->dataTable->verticalHeaderItem(row)->text().toDouble(), 90.0, last + (last - prelast));
        }
    }

    return table_data;
}

void MainWindow::on_draw3DplotButton_clicked()
{
    auto table_data = MainWindow::get_table_data();
    SurfaceWindow *window = new SurfaceWindow(table_data, columns_count_, rows_count_);
    window->show();
}

QString MainWindow::prepare_data_to_save()
{
    QString textData;
    int rows = ui_->dataTable->rowCount();
    int columns = ui_->dataTable->columnCount();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {

            textData += ui_->dataTable->item(i,j)->text();
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

    if (columns_count != 0 && rows_count != 0) {
        project_settings_.step_in_meridian_dir_ = 90 / columns_count;
        project_settings_.step_in_parallel_dir_ = 360 / rows_count;
        this->columns_count_ = columns_count;
        this->rows_count_ = rows_count;
    } else {
        qDebug() << "Error when reading data";
    }

    qDebug() << "steps: " << QString::number(project_settings_.step_in_meridian_dir_) << QString::number(project_settings_.step_in_parallel_dir_);

    setup_table_view(columns_count, rows_count);


    stream.seek(0);


    int row = 0;
    while (!stream.atEnd()) {
        QString line = stream.readLine();
        QStringList list = line.split(",");
        for(int col = 0; col < list.count(); col++) {
            ui_->dataTable->setItem(row, col, new QTableWidgetItem(list[col]));
        }
        row++;
    }

    csv_file.close();
}
