#include <python_function.h>

#include <mainwindow.h>
#include <ui_mainwindow.h>
#include <QDebug>

namespace py = pybind11;

MainWindow::MainWindow( QWidget *parent ):
     QMainWindow( parent ), ui( new Ui::MainWindow )
{
     ui->setupUi( this );
     // add path to import adaptors
     py::exec( R"(
          import sys
          sys.path.append('adaptors')
     )" );
}


MainWindow::~MainWindow()
{
     delete ui;
}


void MainWindow::on_action_open_triggered()
{

}


void MainWindow::on_action_save_triggered()
{

}

void MainWindow::on_action_save_as_triggered()
{

}
