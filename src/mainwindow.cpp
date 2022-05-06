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
     this->scene->installEventFilter(this);
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

#include <iostream>
bool MainWindow::eventFilter(QObject* target, QEvent* event)
{
    if (
        target == scene &&
        event->type() == QEvent::GraphicsSceneMouseRelease
    )
    {
        QGraphicsSceneMouseEvent* mouse_event =
            static_cast<QGraphicsSceneMouseEvent*>(event);
        AutomatonGI* current = dynamic_cast<AutomatonGI*>(
            this->scene->itemAt(mouse_event->scenePos(), QTransform()));
        if (!current)
            return QMainWindow::eventFilter(target, event);
        QList<QGraphicsItem*> colliding = current->collidingItems(
            Qt::IntersectsItemBoundingRect
        );
        bool has_intersections = false;
        for (QGraphicsItem* item: colliding)
        {
            AutomatonGI* automaton = dynamic_cast<AutomatonGI*>(item);
            if (
                automaton->scenePos().x() <= current->scenePos().x() &&
                !automaton->is_output_set()
            )
            {
                current->set_input(automaton);
                automaton->set_output(current);
                current->setPos(
                    automaton->scenePos().x() + automaton->boundingRect().width(),
                    automaton->scenePos().y()
                );
                has_intersections = true;
                break;
            } else if (
                automaton->scenePos().x() >= current->scenePos().x() &&
                !automaton->is_input_set()
            )
            {
                current->set_output(automaton);
                automaton->set_input(current);
                current->setPos(
                    automaton->scenePos().x() - automaton->boundingRect().width(),
                    automaton->scenePos().y()
                );
                has_intersections = true;
                break;
            }
        }
        if (!has_intersections)
        {
            if (current->is_input_set())
                current->get_input()->set_output(nullptr);
            current->set_input(nullptr);

            if (current->is_output_set())
                current->get_output()->set_input(nullptr);
            current->set_output(nullptr);
        }
    }
    return QMainWindow::eventFilter(target, event);
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
