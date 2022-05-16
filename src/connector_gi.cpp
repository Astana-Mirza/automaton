#include <automaton_gi.h>
#include <connector_gi.h>
#include <QPainter>
#include <QGraphicsScene>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QLabel>

ConnectorGI::ConnectorGI( AutomatonGI* automaton ):
     automaton_( automaton )
{
     setAcceptHoverEvents(true);
}


QRectF ConnectorGI::boundingRect() const
{
     return QRectF( -15, -15, 30, 30 );
}


void ConnectorGI::paint( QPainter *painter, const QStyleOptionGraphicsItem *, QWidget * )
{
     painter->setPen( Qt::black );
     painter->setBrush( Qt::blue );
     painter->drawEllipse( -15, -15, 25, 25 );
}

void ConnectorGI::setup_output()
{
     QGroupBox* gb = new QGroupBox( "Output:" );
     gb->setFixedWidth( 200 );
     QVBoxLayout* layout = new QVBoxLayout();
     QLabel* info = new QLabel( gb );
     info->setText( "Automaton " + QString::number( automaton_->get_automaton_index() ) + " output" );
     layout->addWidget( info );
     gb->setLayout( layout );

     output_info_ = scene()->addWidget( gb );
     output_info_->setPos(
          scenePos().x() - 100, scenePos().y() + 20
     );
}


void ConnectorGI::hoverEnterEvent( QGraphicsSceneHoverEvent * )
{
     if ( output_info_ )
          return;
     setup_output();
}


void ConnectorGI::hoverLeaveEvent( QGraphicsSceneHoverEvent * )
{
     if ( !output_fixed_ && output_info_ && scene() )
     {
          scene()->removeItem( output_info_ );
          delete output_info_;
          output_info_ = nullptr;
     }
}


void ConnectorGI::mousePressEvent( QGraphicsSceneMouseEvent * )
{
     output_fixed_ = !output_fixed_;
}

