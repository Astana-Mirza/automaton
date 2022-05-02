#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <pybind11/embed.h>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
     Q_OBJECT

public:
     MainWindow( QWidget *parent = nullptr );
     ~MainWindow();

private slots:
     void on_action_open_triggered();
     void on_action_save_triggered();
     void on_action_save_as_triggered();

private:
     pybind11::scoped_interpreter guard{};
     Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
