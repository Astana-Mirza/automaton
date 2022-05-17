#include <automaton_gi.h>
#include <input_gi.h>
#include <QCursor>
#include <QGraphicsScene>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QString>

AutomatonGI::AutomatonGI( QGraphicsScene *scene, size_t index ):
     ElementGI::ElementGI( scene ), automaton_index_{ index }, connector_{ nullptr }
{
     setFlag( QGraphicsItem::ItemIsSelectable, true );
     connector_ = new ConnectorGI( this );
     connector_->setPos(
          scenePos().x() + ( boundingRect().width() / 2 - 15 ) + ( connector_->boundingRect().width() / 2 ),
          scenePos().y()
     );
}


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
     painter->drawText( QRect{ -50, -15, 13, 15 },
                        Qt::AlignRight | Qt::AlignVCenter, "in" );
     painter->drawText( QRect{ 38, -15, 15, 15 },
                        Qt::AlignLeft | Qt::AlignVCenter, "out" );

     painter->setBrush( QBrush( Qt::NoBrush ) );
     painter->drawPolygon( polygon );
     painter->drawLine( !is_input_set() ? -60 : -45, 0, -35, 0 );
     painter->drawLine( !is_output_set() ? 60 :  45, 0,  35, 0 );
}


void AutomatonGI::mouseMoveEvent( QGraphicsSceneMouseEvent *event )
{
     if ( isSelected() )
     {
          setPos( event->scenePos().x(), event->scenePos().y() );
     }
}


void AutomatonGI::mousePressEvent( QGraphicsSceneMouseEvent *event )
{
     if ( event->button() == Qt::RightButton )
     {
          show_info();
     }
     else if ( event->button() == Qt::LeftButton )
     {
          setSelected( true );
          setCursor( QCursor( Qt::ClosedHandCursor ) );
     }
}


void AutomatonGI::mouseReleaseEvent( QGraphicsSceneMouseEvent * )
{
     setCursor( QCursor( Qt::ArrowCursor ) );
     if ( !isSelected() )
     {
          return;
     }
     setSelected( false );
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
          if ( !automaton )
          {
               bool input_colliding = check_input_colliding( item );
               if ( input_colliding )
               {
                    break;
               }
               continue;
          }
          if ( automaton->scenePos().x() <= scenePos().x() && !automaton->is_output_set() )
          {
               automaton->set_output( this );
               setPos( automaton->scenePos().x() + automaton->boundingRect().width(),
                       automaton->scenePos().y() );
               set_input( automaton );
               break;
          }
          else if ( automaton->scenePos().x() >= scenePos().x() && !automaton->is_input_set() )
          {
               automaton->set_input( this );
               setPos( automaton->scenePos().x() - automaton->boundingRect().width(),
                       automaton->scenePos().y() );
               set_output( automaton );
               break;
          }
     }
     update();
}


void AutomatonGI::set_output( ElementGI* output )
{
     ElementGI::set_output( output );
     update();
}


bool AutomatonGI::check_input_colliding( QGraphicsItem* item )
{
     InputGI* input_gi = dynamic_cast<InputGI*>( item );
     if ( !input_gi )
     {
          return false;
     }
     if ( input_gi->is_input_set() || input_gi->scenePos().x() > scenePos().x() )
     {
          return false;
     }
     input_gi->set_output( this );
     set_input( input_gi );
     setPos( item->scenePos().x() + ( item->boundingRect().width() / 4 ) + ( boundingRect().width() / 2 ),
             item->scenePos().y() );
     return true;
}
