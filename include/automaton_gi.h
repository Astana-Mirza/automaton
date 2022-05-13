#ifndef AUTOMATON_GI_H
#define AUTOMATON_GI_H

#include <python_function.h>
#include <automaton/finite_automaton.h>
#include <element_gi.h>
#include <input_gi.h>
#include <connector_gi.h>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QString>

class AutomatonGI: public ElementGI
{
public:
     explicit AutomatonGI( const std::string& init_state,
                           const std::string& tr_file,
                           const std::string& tr_func_name,
                           const std::string& out_file,
                           const std::string& out_func_name,
                           uint32_t index = 0 );
     ~AutomatonGI();

     void set_output( ElementGI* output );
     QRectF boundingRect() const;

     void set_initial_state( const QString& state ) { initial_state_ = state; }
     void set_initial_key( const QString& key ) { initial_key_ = key; }

     QString get_initial_state() const { return initial_state_; }
     QString get_initial_key() const { return initial_key_; }

     uint32_t get_automaton_index() const { return automaton_index_; }
protected:
     void paint( QPainter *painter, const QStyleOptionGraphicsItem *, QWidget * );
     void mouseMoveEvent( QGraphicsSceneMouseEvent *event );
     void mousePressEvent( QGraphicsSceneMouseEvent *event );
     void mouseReleaseEvent( QGraphicsSceneMouseEvent *event );

     bool check_input_colliding( QGraphicsItem* item );

     void call_modal();
private:
//     FiniteAutomaton< std::string, std::string, std::string,
//                      PythonFunction< std::string >,
//                      PythonFunction< std::string > > processor_;
     QString initial_state_;
     QString initial_key_;
     uint32_t automaton_index_;
     ConnectorGI* connector_ = nullptr;
};

#endif // AUTOMATON_GI_H
