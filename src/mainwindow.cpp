#include <python_function.h>

#include <mainwindow.h>
#include <ui_mainwindow.h>
#include <QDebug>

namespace py = pybind11;

MainWindow::MainWindow( QWidget *parent ):
     QMainWindow( parent ), ui( new Ui::MainWindow ),
     timer( new QTimer( this ) )
{
     ui->setupUi( this );
     // add path to import adaptors
     py::exec( R"(
          import sys
          sys.path.append('adaptors')
     )" );

     this->setup_scene();
     this->setup_timer();

     this->automatons.push_back(new AutomatonGI(this->next_automaton_index++));
     this->automatons.push_back(new AutomatonGI(this->next_automaton_index++));

//     this->automatons.at(0)->set_output(this->automatons.at(1));
//     this->automatons.at(1)->set_input(this->automatons.at(0));

     this->scene->addItem(this->automatons.at(0));
     this->scene->addItem(this->automatons.at(1));

     this->automatons.at(1)->setPos(
         this->automatons.at(0)->scenePos().x() + 120,
         this->automatons.at(0)->scenePos().y()
     );
}


MainWindow::~MainWindow()
{
     delete ui;
     delete scene;
}

void MainWindow::setup_scene()
{
    this->scene = new QGraphicsScene;
    ui->graphicsView->setAlignment(Qt::AlignCenter);
    ui->graphicsView->setSizePolicy(
        QSizePolicy::Expanding,
        QSizePolicy::Expanding
    );
    ui->graphicsView->setMinimumHeight(200);
    ui->graphicsView->setMinimumWidth(200);

    ui->graphicsView->setScene(this->scene);

//    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    ui->graphicsView->setViewportUpdateMode(
        QGraphicsView::FullViewportUpdate);
    ui->graphicsView->show();
}


void MainWindow::setup_timer()
{
    this->connect(&timer, &QTimer::timeout, this, [&](){

    });
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
