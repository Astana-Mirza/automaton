#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <pybind11/embed.h>
#include <automaton_gi.h>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
     Q_OBJECT

public:
     MainWindow( QWidget *parent = nullptr );
     ~MainWindow();

private slots:
     void on_action_open_triggered();
     void on_action_save_triggered();
     void on_action_save_as_triggered();
     void on_action_add_finite_automaton_triggered();
     void on_action_remove_triggered();
     void on_action_add_crypto_automaton_triggered();

private:
     void setup_scene();
     void setup_timer();

     pybind11::scoped_interpreter guard_{};
     Ui::MainWindow *ui_;
     QTimer timer_;

     QGraphicsScene* scene_ = nullptr;
     QVector<AutomatonGI*> automatons_;
};

#endif // MAINWINDOW_H
