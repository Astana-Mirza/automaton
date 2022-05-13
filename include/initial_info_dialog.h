#ifndef INITIAL_INFO_DIALOG_H
#define INITIAL_INFO_DIALOG_H

#include <QDialog>
#include <QString>
#include <QVBoxLayout>
#include <QLabel>

class InitialInfoDialog: public QDialog
{
public:
     InitialInfoDialog( size_t automaton_num, bool is_crypto = false );
     ~InitialInfoDialog() = default;

     const QString& get_initial_state() const { return initial_state_; }
     const QString& get_initial_key()   const { return initial_key_;   }
     const QString& get_tr_file_name()  const { return tr_file_name_;  }
     const QString& get_tr_func_name()  const { return tr_func_name_;  }
     const QString& get_out_file_name() const { return out_file_name_; }
     const QString& get_out_func_name() const { return out_func_name_; }

private:
     QString initial_state_;
     QString initial_key_;
     QString tr_file_name_;
     QString tr_func_name_;
     QString out_file_name_;
     QString out_func_name_;

     void set_title( size_t automaton_num, QVBoxLayout *layout );
     void set_init( QVBoxLayout *layout, bool is_crypto );
     void set_script_selector( QVBoxLayout *layout, const QString& text, QString& filename, QString& func_name );
     QString get_filename( QLabel *filename_label );
     QString parse_filename( const QString& filepath ) const;
};

#endif // INITIAL_INFO_DIALOG_H
