#ifndef INITIAL_INFO_DIALOG_H
#define INITIAL_INFO_DIALOG_H

#include <automaton_gi.h>
#include <QDialog>
#include <QGridLayout>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <string>

class InitialInfoDialog: public QDialog
{
public:
     InitialInfoDialog( AutomatonGI* caller, bool is_crypto = false );
     ~InitialInfoDialog() = default;
protected:
     bool is_crypto_automaton_ = false;

     QGridLayout* layout_ = nullptr;
     QLineEdit* initial_info_input_ = nullptr;
     QLineEdit* key_input_ = nullptr;
};

#endif // INITIAL_INFO_DIALOG_H
