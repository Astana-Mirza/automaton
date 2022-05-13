#include <initial_info_dialog.h>
#include <QFileDialog>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QFileInfo>

InitialInfoDialog::InitialInfoDialog( AutomatonGI* caller, bool is_crypto )
{
     setMinimumWidth( 400 );
     setWindowTitle( "Automaton configuration" );
     QVBoxLayout *layout = new QVBoxLayout( this );
     set_title( caller, layout );
     set_init( caller, layout, is_crypto );
     set_script_selector( caller, layout );
}


void InitialInfoDialog::set_title( AutomatonGI* caller, QVBoxLayout *layout )
{
     QLabel* header = new QLabel( "Automaton " + QString::number( caller->get_automaton_index() ) );
     QFont font( header->font() );
     font.setPointSize( 18 );
     font.setBold( true );
     header->setFont( font );
     layout->addWidget( header );
}


void InitialInfoDialog::set_init( AutomatonGI* caller, QVBoxLayout *layout, bool is_crypto )
{
     QLabel* initial_info_label = new QLabel( "Initial State:" );
     layout->addWidget( initial_info_label );

     QLineEdit *initial_info_input = new QLineEdit( this );
     initial_info_input->setText( caller->get_initial_state() );
     layout->addWidget( initial_info_input );
     connect( initial_info_input, &QLineEdit::textChanged, this,
          [ caller ]( const QString& value )
          {
               caller->set_initial_state( value );
          }
     );
     if ( is_crypto )
     {
          QLabel* initial_key_label = new QLabel( "Crypto Automaton Key:" );
          layout->addWidget( initial_key_label );

          QLineEdit *key_input = new QLineEdit;
          key_input->setText( caller->get_initial_key() );
          layout->addWidget( key_input );
          connect( key_input, &QLineEdit::textChanged, this,
               [ caller ]( const QString& value )
               {
                    caller->set_initial_key( value );
               }
          );
     }
}


void InitialInfoDialog::set_script_selector( AutomatonGI* caller, QVBoxLayout *layout )
{
     QHBoxLayout* file_select_layout = new QHBoxLayout;
     layout->addLayout( file_select_layout );

     QPushButton* file_select_button = new QPushButton( "Select file" );
     QLabel *filename_label = new QLabel( parse_filename( caller->get_function_path() ) );

     file_select_button->setFixedWidth( 100 );
     file_select_layout->addWidget( file_select_button );
     connect( file_select_button, &QPushButton::clicked, this,
              [ this, caller, filename_label ]()
          {
               get_filename( caller, filename_label );
          }
     );
     file_select_layout->addWidget( filename_label );

     QLabel* function_name_label = new QLabel( "Transition Function Name:" );
     layout->addWidget( function_name_label );

     QLineEdit *function_name_input = new QLineEdit;
     function_name_input->setText( caller->get_function_name() );
     layout->addWidget( function_name_input );
     connect( function_name_input, &QLineEdit::textChanged, this,
          [ caller ]( const QString& value ) {
               caller->set_function_name( value );
          }
     );

     QDialogButtonBox* buttonBox = new QDialogButtonBox( QDialogButtonBox::Ok );
     connect( buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept );
     layout->addWidget( buttonBox );
}


void InitialInfoDialog::get_filename( AutomatonGI* caller, QLabel *filename_label )
{
     QString filepath = QFileDialog::getOpenFileName( this, "Select python module file",
                                                      QDir::home().dirName(), "Python Module (*.py)" );
     if ( !filepath.isEmpty() )
     {
          caller->set_function_path( filepath );
          filename_label->setText( parse_filename( filepath ) );
     }
}

QString InitialInfoDialog::parse_filename( const QString& filepath ) const
{
     if ( filepath.isEmpty() )
     {
          return "File not selected";
     }
     return QFileInfo( filepath ).fileName();
}

