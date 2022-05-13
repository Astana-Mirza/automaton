#ifndef INITIAL_INFO_DIALOG_H
#define INITIAL_INFO_DIALOG_H

#include <automaton_gi.h>
#include <QDialog>
#include <QString>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>

class InitialInfoDialog: public QDialog
{
public:
     InitialInfoDialog( AutomatonGI* caller, bool is_crypto = false );
     ~InitialInfoDialog() = default;

private:
     void set_title( AutomatonGI* caller, QVBoxLayout *layout );
     void set_init( AutomatonGI* caller, QVBoxLayout *layout, bool is_crypto );
     void set_script_selector( AutomatonGI* caller, QVBoxLayout *layout );
     void get_filename( AutomatonGI* caller, QLabel *filename_label );
     QString parse_filename( const QString& filepath ) const;
};

#endif // INITIAL_INFO_DIALOG_H
