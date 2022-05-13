#ifndef INITIAL_INFO_DIALOG_H
#define INITIAL_INFO_DIALOG_H

#include <automaton_gi.h>
#include <QDialog>
#include <QString>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>

class InitialInfoDialog: public QDialog
{
public:
     InitialInfoDialog( AutomatonGI* caller, bool is_crypto = false );
     ~InitialInfoDialog() = default;
protected:
     void get_filename();
     QString parse_filename( const QString& filepath ) const;

     bool is_crypto_automaton_ = false;

     AutomatonGI* caller_ = nullptr;
     QVBoxLayout* layout_ = nullptr;
     QLineEdit* initial_info_input_ = nullptr;
     QLineEdit* key_input_ = nullptr;
     QLineEdit* function_name_input_ = nullptr;
     QLabel* filename_label_ = nullptr;
};

#endif // INITIAL_INFO_DIALOG_H
