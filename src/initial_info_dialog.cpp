#include <initial_info_dialog.h>
#include <QString>

InitialInfoDialog::InitialInfoDialog( AutomatonGI* caller, bool is_crypto ):
     is_crypto_automaton_( is_crypto )
{
     setMinimumWidth( 300 );
     setWindowTitle( "Automaton configuration" );

     QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
          | QDialogButtonBox::Cancel);

     connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
     connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

     layout_ = new QGridLayout( this );

     initial_info_input_ = new QLineEdit( this );
     initial_info_input_->setText(
          QString::number( caller->get_automaton_index() )
     );
     layout_->addWidget( initial_info_input_, 0, 0 );
//     connect(

//     );

     if ( is_crypto_automaton_ )
     {
          key_input_ = new QLineEdit( this );
          layout_->addWidget( key_input_, 1, 0 );
     }

     layout_->addWidget(buttonBox, 2, 0);
}
