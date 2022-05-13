#include <initial_info_dialog.h>
#include <QFileDialog>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QFileInfo>
#include <QLineEdit>

InitialInfoDialog::InitialInfoDialog( size_t automaton_num, bool is_crypto )
{
     setWindowFlags(
          Qt::Dialog |
          Qt::WindowCloseButtonHint |
          Qt::WindowSystemMenuHint
     );
     setMinimumWidth( 400 );
     setWindowTitle( "Automaton configuration" );
     QVBoxLayout *layout = new QVBoxLayout( this );
     set_title( automaton_num, layout );
     set_init( layout, is_crypto );
     set_script_selector( layout, "Transition Function Name:", tr_file_name_, tr_func_name_ );
     set_script_selector( layout, "Output Function Name:", out_file_name_, out_func_name_ );
     QDialogButtonBox* buttonBox = new QDialogButtonBox( QDialogButtonBox::Ok );
     connect( buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept );
     layout->addWidget( buttonBox );
}


void InitialInfoDialog::set_title( size_t automaton_num, QVBoxLayout *layout )
{
     QLabel* header = new QLabel( "Automaton " + QString::number( automaton_num ) );
     QFont font( header->font() );
     font.setPointSize( 18 );
     font.setBold( true );
     header->setFont( font );
     layout->addWidget( header );
}


void InitialInfoDialog::set_init( QVBoxLayout *layout, bool is_crypto )
{
     QLabel* initial_info_label = new QLabel( "Initial State:" );
     layout->addWidget( initial_info_label );

     QLineEdit *initial_info_input = new QLineEdit( this );
     layout->addWidget( initial_info_input );
     connect( initial_info_input, &QLineEdit::textChanged, this,
          [ this ]( const QString& value )
          {
               initial_state_ = value;
          }
     );
     if ( is_crypto )
     {
          QLabel* initial_key_label = new QLabel( "Crypto Automaton Key:" );
          layout->addWidget( initial_key_label );

          QLineEdit *key_input = new QLineEdit;
          layout->addWidget( key_input );
          connect( key_input, &QLineEdit::textChanged, this,
               [ this ]( const QString& value )
               {
                    initial_key_ = value;
               }
          );
     }
}


void InitialInfoDialog::set_script_selector( QVBoxLayout *layout, const QString& text,
                                        QString& filename, QString& func_name )
{
     QHBoxLayout* file_select_layout = new QHBoxLayout;
     layout->addLayout( file_select_layout );

     QPushButton* file_select_button = new QPushButton( "Select file" );
     QLabel *filename_label = new QLabel( "File not selected" );

     file_select_button->setFixedWidth( 100 );
     file_select_layout->addWidget( file_select_button );
     connect( file_select_button, &QPushButton::clicked, this,
              [ this, &filename, filename_label ]()
          {
               filename = get_filename( filename_label );
          }
     );
     file_select_layout->addWidget( filename_label );

     QLabel* function_name_label = new QLabel( text );
     layout->addWidget( function_name_label );

     QLineEdit *function_name_input = new QLineEdit;
     layout->addWidget( function_name_input );
     connect( function_name_input, &QLineEdit::textChanged, this,
          [ &func_name ]( const QString& value ) {
               func_name = value;
          }
     );
}


QString InitialInfoDialog::get_filename( QLabel *filename_label )
{
     QString filepath = QFileDialog::getOpenFileName( this, "Select python module file",
                                                      QDir::home().dirName(), "Python Module (*.py)" );
     if ( !filepath.isEmpty() )
     {
          filename_label->setText( parse_filename( filepath ) );
     }
     return filepath;
}

QString InitialInfoDialog::parse_filename( const QString& filepath ) const
{
     if ( filepath.isEmpty() )
     {
          return "File not selected";
     }
     return QFileInfo( filepath ).fileName();
}

