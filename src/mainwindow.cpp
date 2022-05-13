#include <mainwindow.h>
#include <ui_mainwindow.h>
#include <automaton_gi.h>
#include <initial_info_dialog.h>

namespace py = pybind11;

MainWindow::MainWindow( QWidget *parent ):
     QMainWindow( parent ), automaton_count_{ 0 }, ui_( new Ui::MainWindow )
{
     ui_->setupUi( this );
     // add path to import adaptors
     py::exec( R"(
          import sys
          sys.path.append('adaptors')
     )" );
     setup_scene();
     input_ = new InputGI;
     scene_->addItem( input_ );
     input_->setPos( 200, 200 );
}


MainWindow::~MainWindow()
{
     delete ui_;
     delete scene_;
}


void MainWindow::setup_scene()
{
     scene_ = new QGraphicsScene( this );
     ui_->graphicsView->setAlignment( Qt::AlignCenter );
     ui_->graphicsView->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
     ui_->graphicsView->setMinimumHeight( 200 );
     ui_->graphicsView->setMinimumWidth( 200 );
     ui_->graphicsView->setScene( scene_ );
     // ui_->graphicsView->setDragMode( QGraphicsView::ScrollHandDrag );
     ui_->graphicsView->setViewportUpdateMode( QGraphicsView::FullViewportUpdate );
     ui_->graphicsView->show();
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

// TODO: try..catch block over construction of automaton
void MainWindow::on_action_add_finite_automaton_triggered()
{
     InitialInfoDialog dialog( automaton_count_ );
     if ( dialog.exec() == QDialog::Rejected )
     {
          return;
     }
     if ( /*!dialog.get_tr_file_name().isEmpty() && !dialog.get_tr_func_name().isEmpty()
          && !dialog.get_out_file_name().isEmpty() && !dialog.get_out_func_name().isEmpty()*/ true )
     {
          AutomatonGI *automaton = new AutomatonGI(
               dialog.get_initial_state().toStdString(),
               dialog.get_tr_file_name().toStdString(),
               dialog.get_tr_func_name().toStdString(),
               dialog.get_out_file_name().toStdString(),
               dialog.get_out_func_name().toStdString(),
               automaton_count_
          );
          automaton_count_++;
          scene_->addItem( automaton );
     }
     else
     {
          // error message
     }
}


void MainWindow::on_action_add_crypto_automaton_triggered()
{
     InitialInfoDialog dialog( automaton_count_, true );
     if ( dialog.exec() == QDialog::Rejected )
     {
          return;
     }
     if ( !dialog.get_tr_file_name().isEmpty() && !dialog.get_tr_func_name().isEmpty()
          && !dialog.get_out_file_name().isEmpty() && !dialog.get_out_func_name().isEmpty() )
     {
          // make crypto automaton
     }
     else
     {
          // error message
     }
}


void MainWindow::on_action_remove_triggered()
{

}
