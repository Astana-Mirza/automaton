#include <mainwindow.h>
#include <ui_mainwindow.h>
#include <QDebug>

namespace py = pybind11;

MainWindow::MainWindow( QWidget *parent ):
     QMainWindow( parent ), ui_( new Ui::MainWindow ),
     timer_( new QTimer( this ) )
{
     ui_->setupUi( this );
     // add path to import adaptors
     py::exec( R"(
          import sys
          sys.path.append('adaptors')
     )" );
     setup_scene();
     setup_timer();
     automatons_.push_back( new AutomatonGI( "", "", "", "", "", 0 ) );
     automatons_.push_back( new AutomatonGI( "", "", "", "", "", 1 ) );
     // automatons_[ 0 ]->set_output( automatons_[ 1 ] );
     // automatons_[ 1 ]->set_input( automatons_[ 0 ] );
     input_ = new InputGI;
     scene_->addItem( input_ );
     scene_->addItem( automatons_[ 0 ] );
     scene_->addItem( automatons_[ 1 ] );

     automatons_[ 1 ]->setPos( automatons_[ 0 ]->scenePos().x() + 120,
                               automatons_[ 0 ]->scenePos().y() );
     input_->setPos( automatons_[ 0 ]->scenePos().x() - 85,
                               automatons_[ 0 ]->scenePos().y() );
}


MainWindow::~MainWindow()
{
     delete ui_;
     delete scene_;
     delete input_;
}

void MainWindow::setup_scene()
{
     scene_ = new QGraphicsScene(this);
     ui_->graphicsView->setAlignment( Qt::AlignCenter );
     ui_->graphicsView->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
     ui_->graphicsView->setMinimumHeight( 200 );
     ui_->graphicsView->setMinimumWidth( 200 );
     ui_->graphicsView->setScene( scene_ );
     // ui_->graphicsView->setDragMode( QGraphicsView::ScrollHandDrag );
     ui_->graphicsView->setViewportUpdateMode( QGraphicsView::FullViewportUpdate );
     ui_->graphicsView->show();
}


void MainWindow::setup_timer()
{
    connect( &timer_, &QTimer::timeout, this, [&]() {

    } );
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


void MainWindow::on_action_add_finite_automaton_triggered()
{

}


void MainWindow::on_action_add_crypto_automaton_triggered()
{

}


void MainWindow::on_action_remove_triggered()
{

}
