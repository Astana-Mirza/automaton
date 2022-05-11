#ifndef AUTOMATON_GI_H
#define AUTOMATON_GI_H

#include <python_function.h>
#include <automaton/finite_automaton.h>
#include <element_gi.h>
#include <input_gi.h>
#include <connector_gi.h>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

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
protected:
     void paint( QPainter *painter, const QStyleOptionGraphicsItem *, QWidget * );
     void mouseMoveEvent( QGraphicsSceneMouseEvent *event );
     void mousePressEvent( QGraphicsSceneMouseEvent * );
     void mouseReleaseEvent( QGraphicsSceneMouseEvent * );

     bool check_input_colliding( QGraphicsItem* item );

private:
//     FiniteAutomaton< std::string, std::string, std::string,
//                      PythonFunction< std::string >,
//                      PythonFunction< std::string > > processor_;
     uint32_t automaton_index_;
     ConnectorGI* connector_ = nullptr;
};

#endif // AUTOMATON_GI_H
