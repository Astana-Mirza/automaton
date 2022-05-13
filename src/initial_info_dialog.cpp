#include <initial_info_dialog.h>
#include <QFileDialog>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QFileInfo>

InitialInfoDialog::InitialInfoDialog( AutomatonGI* caller, bool is_crypto ):
     caller_( caller ),
     is_crypto_automaton_( is_crypto )
{
     setMinimumWidth( 400 );
     setWindowTitle( "Automaton configuration" );

     layout_ = new QVBoxLayout( this );

     QLabel* header = new QLabel( "Automaton " + QString::number( caller_->get_automaton_index() ), this );
     QFont font( header->font() );
     font.setPointSize( 18 );
     font.setBold( true );
     header->setFont( font );
     layout_->addWidget( header );

     QLabel* initial_info_label = new QLabel( "Initial State:", this );
     layout_->addWidget( initial_info_label );

     initial_info_input_ = new QLineEdit( this );
     initial_info_input_->setText( caller_->get_initial_state() );
     layout_->addWidget( initial_info_input_ );
     connect(
          initial_info_input_,
          &QLineEdit::textChanged,
          this,
          [caller]( const QString& value ) {
               caller->set_initial_state( value );
          }
     );

     if ( is_crypto_automaton_ )
     {
          QLabel* initial_key_label = new QLabel( "Crypto Automaton Key:", this );
          layout_->addWidget( initial_key_label );

          key_input_ = new QLineEdit( this );
          key_input_->setText( caller_->get_initial_key() );
          layout_->addWidget( key_input_ );
          connect(
               key_input_,
               &QLineEdit::textChanged,
               this,
               [caller]( const QString& value ) {
                    caller->set_initial_key( value );
               }
          );
     }

     QGridLayout* file_select_layout = new QGridLayout( this );

     QPushButton* file_select_button = new QPushButton( "Select file", this );
     file_select_button->setFixedWidth( 100 );
     file_select_layout->addWidget( file_select_button, 0, 0 );
     connect(
          file_select_button,
          &QPushButton::clicked,
          this,
          &InitialInfoDialog::get_filename
     );
     filename_label_ = new QLabel(
          parse_filename( caller_->get_function_path() ),
          this
     );
     file_select_layout->addWidget( filename_label_, 0, 1 );

     layout_->addLayout( file_select_layout );

     QLabel* function_name_label = new QLabel( "Transition Function Name:", this );
     layout_->addWidget( function_name_label );

     function_name_input_ = new QLineEdit( this );
     function_name_input_->setText( caller_->get_function_name() );
     layout_->addWidget( function_name_input_ );
     connect(
          function_name_input_,
          &QLineEdit::textChanged,
          this,
          [caller]( const QString& value ) {
               caller->set_function_name( value );
          }
     );

     QDialogButtonBox* buttonBox = new QDialogButtonBox( QDialogButtonBox::Ok, this );
     connect( buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept );

     layout_->addWidget( buttonBox );
}

void InitialInfoDialog::get_filename()
{
     QString filepath = QFileDialog::getOpenFileName(
          this,
          "Select python module file",
          QDir::home().dirName(),
          "Python Module (*.py)"
     );
     if ( !filepath.isEmpty() )
     {
          caller_->set_function_path( filepath );
          filename_label_->setText( parse_filename( filepath ) );
     }
}

QString InitialInfoDialog::parse_filename( const QString& filepath ) const
{
     if ( filepath.isEmpty() )
          return "File not selected";
     return QFileInfo( filepath ).fileName();
}

