#include <finite_automaton_gi.h>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>

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

     state_info->setText( QString::fromStdString( processor_.get_state() ) );
     state_info->setLineWrapMode( QTextEdit::NoWrap );
     state_info->setFixedHeight( 45 );
     state_info->setReadOnly( true );

     layout->setAlignment( Qt::AlignTop );
     layout->addWidget( state_label );
     layout->addWidget( state_info );

     info_dialog->setWindowTitle( "Automaton " + QString::number( get_automaton_index() ) + " info" );
     info_dialog->setLayout( layout );
     info_dialog->setMinimumSize( 320, 80 );
     info_dialog->setAttribute(Qt::WA_DeleteOnClose);
     info_dialog->show();
}
