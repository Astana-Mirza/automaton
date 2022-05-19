#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <pybind11/embed.h>
#include <input_gi.h>
#include <QMainWindow>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
     Q_OBJECT

public:
     MainWindow( QWidget *parent = nullptr );
     ~MainWindow();
     void error_window( const QString& info );

private slots:
     void on_action_add_finite_automaton_triggered();
     void on_action_add_crypto_automaton_triggered();
     void on_action_run_step_triggered();
     void on_action_run_all_triggered();

private:
     void setup_scene();
     void setup_timer();

     pybind11::scoped_interpreter guard_;
     size_t automaton_count_;
     Ui::MainWindow *ui_;
     QGraphicsScene* scene_;
     InputGI* input_;
};

#endif // MAINWINDOW_H
