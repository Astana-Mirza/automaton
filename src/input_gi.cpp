#include <automaton_gi.h>
#include <input_gi.h>
#include <QPainter>
#include <QCursor>
#include <QDialog>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QDialogButtonBox>
#include <QGraphicsSceneMouseEvent>

InputGI::InputGI( QGraphicsScene *scene ):
     ElementGI::ElementGI( scene ) {}


QRectF InputGI::boundingRect() const
{
     return QRectF( -25, -25, 50, 50 );
}


void InputGI::paint( QPainter *painter, const QStyleOptionGraphicsItem *, QWidget * )
{
     QPolygon polygon;
     polygon << QPoint( -25, -25 ) << QPoint( -25, 25 ) << QPoint( 25, 0 );
     painter->setPen( Qt::black );
     painter->setBrush( Qt::red );
     painter->drawPolygon( polygon );
}


bool InputGI::empty() const
{
     return data_.empty();
}


QString InputGI::popData()
{
     QString str = data_.at( 0 );
     data_.pop_front();
     return str;
}


void InputGI::mouseMoveEvent( QGraphicsSceneMouseEvent *event )
{
     setPos( event->scenePos().x(), event->scenePos().y() );
}


void InputGI::mousePressEvent( QGraphicsSceneMouseEvent *event )
{
     if ( event->button() == Qt::RightButton )
     {
          QDialog dialog;
          QVBoxLayout *layout = new QVBoxLayout( &dialog );
          QTextEdit *edit = new QTextEdit;
          QDialogButtonBox* buttonBox = new QDialogButtonBox( QDialogButtonBox::Ok | QDialogButtonBox::Cancel );
          dialog.connect( buttonBox, &QDialogButtonBox::accepted, &dialog, [ this, edit, &dialog ]() {
               data_ = edit->toPlainText().split("\n");
               dialog.done( 0 );
          } );
          dialog.connect( buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject );
          edit->setPlaceholderText( "Input data" );
          edit->setText( data_.join( "\n" ) );
          dialog.setWindowTitle( "Input" );
          layout->addWidget( edit );
          layout->addWidget( buttonBox );
          dialog.exec();
     }
     else
     {
          setCursor( QCursor( Qt::ClosedHandCursor ) );
     }
}


void InputGI::mouseReleaseEvent( QGraphicsSceneMouseEvent * )
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
          if ( !automaton )
          {
               continue;
          }
          if ( automaton->scenePos().x() >= scenePos().x() && !automaton->is_input_set() )
          {
               automaton->set_input( this );
               setPos( automaton->scenePos().x() - ( boundingRect().width() / 4 ) - ( automaton->boundingRect().width() / 2 ),
                       automaton->scenePos().y() );
               set_output( automaton );
               break;
          }
     }
     update();
}
