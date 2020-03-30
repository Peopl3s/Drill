#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QRegExpValidator>

#include <cstdio>
#include <stdexcept>

#include "utils.h"
#include "json.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("pics/drill.png"));
    setQssStyle("style/style.qss");

    QRegExp regExpDoubleValue(R"(-?\d+\.?\d*)");
    QValidator *validator = new QRegExpValidator(regExpDoubleValue);
    ui->inputPhi0->setValidator(validator);
}

void MainWindow::setQssStyle(const QString &qssFilePath)
{
    QFile qssFile(qssFilePath);
    qssFile.open(QFile::ReadOnly);
    QString strCss = QLatin1String(qssFile.readAll());
    this->setStyleSheet(strCss);
    qssFile.close();
}

void MainWindow::on_open_clicked()
{
    QString jsonFile =  QFileDialog::getOpenFileName(this, "", "", tr("Json файлы (*.json)"));
    if(jsonFile != QString())
    {
        try
        {
            Utils::getInstance().calculate(jsonFile.toLocal8Bit().toStdString());
        }
        catch(const std::runtime_error &systemException)
        {
            QMessageBox::critical(0, "Ошибка", systemException.what());
            return;
        }
        catch(const nlohmann::json::exception &jsonParseError)
        {
            Q_UNUSED(jsonParseError);
            QMessageBox::critical(0, "Ошибка", "Ошибка в структуре json файла");
            return;
        }

        ui->graphic->clear();
        ui->draw->setEnabled(true);
        ui->clear->setEnabled(false);
    }
}

MainWindow::~MainWindow()
{
    remove(Utils::getInstance().getTempfile().c_str());
    delete ui;
}

void MainWindow::on_exit_clicked()
{
    this->close();
}

void MainWindow::on_clear_clicked()
{
    ui->graphic->clear();
    ui->draw->setEnabled(true);
    ui->clear->setEnabled(false);
}

void MainWindow::on_draw_clicked()
{
    double phi = ui->inputPhi0->text().toDouble();
    ui->graphic->setPhi(phi);
    ui->graphic->draw(phi);
    ui->draw->setEnabled(false);
    ui->clear->setEnabled(true);
}

void MainWindow::on_inputPhi0_returnPressed()
{
    ui->graphic->draw(ui->inputPhi0->text().toDouble());
    ui->clear->setEnabled(true);
}
