#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <pybind11/embed.h>
#include <automaton_gi.h>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <vector>

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

private:
     bool eventFilter(QObject* target, QEvent* event);
     void setup_scene();
     void setup_timer();

     pybind11::scoped_interpreter guard{};
     Ui::MainWindow *ui;
     QTimer timer;

     QGraphicsScene* scene = nullptr;
     std::vector<AutomatonGI*> automatons;
     uint32_t next_automaton_index = 0;
};

#endif // MAINWINDOW_H
