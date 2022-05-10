#include <automaton_gi.h>
#include <QCursor>

AutomatonGI::AutomatonGI( const std::string& init_state,
                          const std::string& tr_file,
                          const std::string& tr_func_name,
                          const std::string& out_file,
                          const std::string& out_func_name,
                          uint32_t index ):
     processor_(init_state, { tr_file, tr_func_name }, { out_file, out_func_name } ),
     automaton_index_( index ) {}


QRectF AutomatonGI::boundingRect() const
{
     return QRectF( -60, -35, 120, 70 );
}


void AutomatonGI::paint( QPainter *painter, const QStyleOptionGraphicsItem *, QWidget * )
{
     QPolygon polygon;
     polygon << QPoint( -35, -35 ) << QPoint( -35, 35 )
             << QPoint( 35, 35 )   << QPoint( 35, -35 );
     painter->setPen( Qt::black );
     painter->drawText( QRect{ -20, -20, 40, 40 }, Qt::AlignHCenter | Qt::AlignVCenter,
                        QString::number( automaton_index_ ) );

     QFont in_out_font = painter->font();
     in_out_font.setPixelSize( 10 );
     painter->setFont( in_out_font );
     painter->drawText( QRect{-50, -15, 13, 15},
                        Qt::AlignRight | Qt::AlignVCenter, "in" );
     painter->drawText( QRect{38, -15, 15, 15},
                        Qt::AlignLeft | Qt::AlignVCenter, "out" );

     painter->setBrush( QBrush( Qt::NoBrush ) );
     painter->drawPolygon( polygon );
     painter->drawLine( !is_input_set() ? -60 : -45, 0, -35, 0 );
     painter->drawLine( !is_output_set() ? 60 :  45, 0,  35, 0 );
}


void AutomatonGI::mouseMoveEvent( QGraphicsSceneMouseEvent *event )
{
     setPos( event->scenePos().x(), event->scenePos().y() );
}


void AutomatonGI::mousePressEvent( QGraphicsSceneMouseEvent * )
{
     setCursor( QCursor( Qt::ClosedHandCursor ) );
}


void AutomatonGI::mouseReleaseEvent( QGraphicsSceneMouseEvent * )
{
     setCursor( QCursor( Qt::ArrowCursor ) );
     auto colliding = collidingItems( Qt::IntersectsItemBoundingRect );
     if ( is_input_set() )
     {
          get_input()->set_output( nullptr );
     }
     set_input( nullptr );
     if ( is_output_set() )
     {
          get_output()->set_input( nullptr );
     }
     set_output( nullptr );
     for ( QGraphicsItem* item : colliding )
     {
          AutomatonGI* automaton = dynamic_cast<AutomatonGI*>( item );
          if ( automaton->scenePos().x() <= scenePos().x() && !automaton->is_output_set() )
          {
               set_input( automaton );
               automaton->set_output( this );
               setPos( automaton->scenePos().x() + automaton->boundingRect().width(),
                       automaton->scenePos().y() );
               break;
          }
          else if ( automaton->scenePos().x() >= scenePos().x() && !automaton->is_input_set() )
          {
               set_output( automaton );
               automaton->set_input( this );
               setPos( automaton->scenePos().x() - automaton->boundingRect().width(),
                       automaton->scenePos().y() );
               break;
          }
     }
     update();
}
