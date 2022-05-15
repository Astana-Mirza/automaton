#include <crypto_automaton_gi.h>
#include <QPainter>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>

CryptoAutomatonGI::CryptoAutomatonGI( const std::string& init_state,
                                      const std::string& init_key,
                                      const std::string& tr_file,
                                      const std::string& tr_func_name,
                                      const std::string& out_file,
                                      const std::string& out_func_name,
                                      size_t index ) :
     AutomatonGI( index ),
     processor_( init_state, init_key, { tr_file, tr_func_name }, { out_file, out_func_name } ) {}


void CryptoAutomatonGI::show_info() const
{
     QDialog* info_dialog = new QDialog();
     QVBoxLayout* layout = new QVBoxLayout();
     QLabel* state_label = new QLabel( "Automaton current state:", info_dialog );
     QTextEdit* state_info = new QTextEdit( info_dialog );
     QLabel* key_label = new QLabel( "Crypto automaton key:", info_dialog );
     QTextEdit* key_info = new QTextEdit( info_dialog );

     state_info->setText( QString::fromStdString( processor_.get_state() ) );
     state_info->setLineWrapMode( QTextEdit::NoWrap );
     state_info->setFixedHeight( 45 );
     state_info->setReadOnly( true );

     key_info->setText( QString::fromStdString( processor_.get_key() ) );
     key_info->setLineWrapMode( QTextEdit::NoWrap );
     key_info->setFixedHeight( 45 );
     key_info->setReadOnly( true );

     layout->setAlignment( Qt::AlignTop );
     layout->addWidget( state_label );
     layout->addWidget( state_info );
     layout->addWidget( key_label );
     layout->addWidget( key_info );

     info_dialog->setWindowTitle( "Crypto automaton " + QString::number( get_automaton_index() ) + " info" );
     info_dialog->setLayout( layout );
     info_dialog->setMinimumSize( 320, 140 );
     info_dialog->setAttribute(Qt::WA_DeleteOnClose);
     info_dialog->show();
}


void CryptoAutomatonGI::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget )
{
     AutomatonGI::paint( painter, option, widget );
     QPolygon polygon;
     polygon << QPoint( -23, -10 ) << QPoint( -15, -10 ) << QPoint( -19, -18 );
     painter->drawPolygon( polygon );
     painter->drawRect( -25, -20, 12, 12 );
     painter->drawArc( QRectF{ -24, -25, 10, 10 }, 0, 2880 );
}
