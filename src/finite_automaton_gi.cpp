#include <finite_automaton_gi.h>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QMessageBox>

FiniteAutomatonGI::FiniteAutomatonGI( QGraphicsScene *scene,
                                      const std::string& init_state,
                                      const std::string& tr_file,
                                      const std::string& tr_func_name,
                                      const std::string& out_file,
                                      const std::string& out_func_name,
                                      size_t index ) :
     AutomatonGI( scene, index ),
     processor_( init_state, { tr_file, tr_func_name }, { out_file, out_func_name } ) {}


std::string FiniteAutomatonGI::step( const std::string& data )
{
     std::string out{ processor_.step( data ) };
     connector_->updateLabel( QString::fromStdString( out ) );
     return out;
}


void FiniteAutomatonGI::show_info() const
{
     QDialog* info_dialog = new QDialog();
     QVBoxLayout* layout = new QVBoxLayout();
     QLabel* state_label = new QLabel( "Automaton current state:", info_dialog );
     QTextEdit* state_info = new QTextEdit( info_dialog );
     QPushButton* delete_btn = new QPushButton( info_dialog );

     delete_btn->setText( "Delete automaton" );
     delete_btn->setStyleSheet( "border: none; color: white; background-color: red; border-radius: 5px; min-height: 32px;" );
     delete_btn->setCursor( QCursor( Qt::PointingHandCursor ) );
     info_dialog->connect( delete_btn, &QPushButton::clicked, info_dialog,
              [ this, info_dialog ]()
          {
               QMessageBox msgBox;
               msgBox.setText( QString( "Automaton %0 deletion" ).arg( get_automaton_index() ) );
               msgBox.setInformativeText( "Are you sure you want to delete this automaton?" );
               msgBox.setStandardButtons( QMessageBox::No | QMessageBox::Yes );
               msgBox.setDefaultButton( QMessageBox::No );
               switch (msgBox.exec())
               {
                    case QMessageBox::No:
                         return;
                    case QMessageBox::Yes:
                         self_destroy();
                         info_dialog->done( 0 );
                         return;
                    default:
                         return;
             }
          }
     );

     state_info->setText( QString::fromStdString( processor_.get_state() ) );
     state_info->setLineWrapMode( QTextEdit::NoWrap );
     state_info->setFixedHeight( 45 );
     state_info->setReadOnly( true );

     layout->setAlignment( Qt::AlignTop );
     layout->addWidget( state_label );
     layout->addWidget( state_info );
     layout->addWidget( delete_btn );

     info_dialog->setWindowTitle( "Automaton " + QString::number( get_automaton_index() ) + " info" );
     info_dialog->setLayout( layout );
     info_dialog->setMinimumSize( 320, 80 );
     info_dialog->setAttribute(Qt::WA_DeleteOnClose);
     info_dialog->exec();
}
