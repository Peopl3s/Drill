#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>

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
    void on_exit_clicked();
    void on_clear_clicked();
    void on_draw_clicked();
    void on_open_clicked();
    void on_inputPhi0_returnPressed();

private:
    Ui::MainWindow *ui;

private:
    void setQssStyle(const QString &);
};

#endif
