#include <automaton_gi.h>
#include <connector_gi.h>
#include <QPainter>
#include <QGraphicsScene>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QLabel>

ConnectorGI::ConnectorGI( AutomatonGI* automaton ):
     automaton_{ automaton }, output_info_{ nullptr },
     info_label_{ nullptr }, output_fixed_{ false }
{
     setAcceptHoverEvents(true);
     setParentItem( automaton_ );
     setup_output();
}


void ConnectorGI::updateLabel( const QString& new_data )
{
     info_label_->setText( new_data );
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
     info_label_ = new QLabel( gb );
     layout->addWidget( info_label_ );
     gb->setLayout( layout );

     output_info_ = scene()->addWidget( gb );
     output_info_->setPos(
          scenePos().x() - 100, scenePos().y() + 20
     );
     output_info_->setParentItem( this );
     output_info_->hide();
}


void ConnectorGI::hoverEnterEvent( QGraphicsSceneHoverEvent * )
{
     output_info_->show();
}


void ConnectorGI::hoverLeaveEvent( QGraphicsSceneHoverEvent * )
{
     if ( !output_fixed_ )
     {
          output_info_->hide();
     }
}


void ConnectorGI::mousePressEvent( QGraphicsSceneMouseEvent * )
{
     output_fixed_ = !output_fixed_;
}

