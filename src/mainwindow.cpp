#include <mainwindow.h>
#include <ui_mainwindow.h>
#include <finite_automaton_gi.h>
#include <crypto_automaton_gi.h>
#include <initial_info_dialog.h>

#include <QMessageBox>
#include <QTextEdit>
#include <QDialogButtonBox>

namespace py = pybind11;

MainWindow::MainWindow( QWidget *parent ):
     QMainWindow( parent ), automaton_count_{ 0 }, ui_{ new Ui::MainWindow }
{
     ui_->setupUi( this );
     py::initialize_interpreter();
     // add path to import adaptors
     py::exec( R"(
          import sys
          sys.path.append('adaptors')
     )" );
     setup_scene();
     input_ = new InputGI( scene_ );
     input_->setPos( 200, 200 );
}


MainWindow::~MainWindow()
{
     delete ui_;
     delete scene_;
     py::finalize_interpreter();
}


void MainWindow::error_window( const QString& info )
{
     QMessageBox window;
     window.critical( this, "Error", info, QMessageBox::Ok, QMessageBox::Ok );
}


void MainWindow::setup_scene()
{
     scene_ = new QGraphicsScene( this );
     ui_->graphicsView->setAlignment( Qt::AlignCenter );
     ui_->graphicsView->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
     ui_->graphicsView->setMinimumHeight( 200 );
     ui_->graphicsView->setMinimumWidth( 200 );
     ui_->graphicsView->setScene( scene_ );
     ui_->graphicsView->setViewportUpdateMode( QGraphicsView::FullViewportUpdate );
     ui_->graphicsView->show();
}


void MainWindow::on_action_add_finite_automaton_triggered()
{
     InitialInfoDialog dialog( automaton_count_ );
     if ( dialog.exec() == QDialog::Rejected )
     {
          return;
     }
     if ( !dialog.get_tr_file_name().isEmpty() && !dialog.get_tr_func_name().isEmpty()
          && !dialog.get_out_file_name().isEmpty() && !dialog.get_out_func_name().isEmpty() )
     {
          try
          {
               new FiniteAutomatonGI( scene_,
                    dialog.get_initial_state().toStdString(),
                    dialog.get_tr_file_name().toStdString(),
                    dialog.get_tr_func_name().toStdString(),
                    dialog.get_out_file_name().toStdString(),
                    dialog.get_out_func_name().toStdString(),
                    automaton_count_
               );
               automaton_count_++;
          }
          catch( std::exception& e )
          {
               error_window( e.what() );
          }
     }
     else
     {
          error_window( "To create an automaton, please set output and transform functions" );
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
          try
          {
               new CryptoAutomatonGI( scene_,
                    dialog.get_initial_state().toStdString(),
                    dialog.get_initial_key().toStdString(),
                    dialog.get_tr_file_name().toStdString(),
                    dialog.get_tr_func_name().toStdString(),
                    dialog.get_out_file_name().toStdString(),
                    dialog.get_out_func_name().toStdString(),
                    automaton_count_
               );
               automaton_count_++;
          }
          catch( std::exception& e )
          {
               error_window( e.what() );
          }
     }
     else
     {
          error_window( "To create an automaton, please set output and transform functions" );
     }
}


void MainWindow::on_action_run_step_triggered()
{
     if ( !input_->empty() )
     {
          AutomatonGI *automaton = dynamic_cast< AutomatonGI * >( input_->get_output() );
          std::string str{ ( input_->popData() ).toStdString() };
          try
          {
               while ( automaton )
               {
                    str = automaton->step( str );
                    automaton = dynamic_cast< AutomatonGI * >( automaton->get_output() );
               }
          }
          catch ( std::exception& e )
          {
               error_window( e.what() );
          }
     }
}


void MainWindow::on_action_run_all_triggered()
{
     QStringList result;
     try
     {
          while ( !input_->empty() )
          {
               AutomatonGI *automaton = dynamic_cast< AutomatonGI * >( input_->get_output() );
               std::string str{ ( input_->popData() ).toStdString() };
               while ( automaton )
               {
                    str = automaton->step( str );
                    automaton = dynamic_cast< AutomatonGI * >( automaton->get_output() );
               }
               result.push_back( QString::fromStdString( str ) );
          }
     }
     catch ( std::exception& e )
     {
          error_window( e.what() );
          return;
     }
     QDialog dialog;
     QVBoxLayout *layout = new QVBoxLayout;
     QTextEdit *text = new QTextEdit;
     QDialogButtonBox* buttonBox = new QDialogButtonBox( QDialogButtonBox::Ok );

     dialog.setWindowTitle( "Automaton output" );
     dialog.connect( buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept );

     text->setText( result.join( "\n" ) );
     text->setReadOnly( true );

     layout->addWidget( text );
     layout->addWidget( buttonBox );
     dialog.setLayout( layout );
     dialog.exec();
}
