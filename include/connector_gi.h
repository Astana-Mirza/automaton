#ifndef CONNECTOR_GI_H
#define CONNECTOR_GI_H

#include <QGraphicsProxyWidget>
#include <QGraphicsItem>
#include <QLabel>

class AutomatonGI;

class ConnectorGI : public QGraphicsItem
{
public:
    ConnectorGI( AutomatonGI* automaton );
    void updateLabel( const QString& new_data );
    QRectF boundingRect() const;

protected:
     void hoverEnterEvent( QGraphicsSceneHoverEvent *event );
     void hoverLeaveEvent( QGraphicsSceneHoverEvent *event );
     void mousePressEvent( QGraphicsSceneMouseEvent *event );
     void setup_output();

private:
     void paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget );

     AutomatonGI* automaton_;
     QGraphicsProxyWidget* output_info_;
     QLabel *info_label_;
     bool output_fixed_;
};

#endif // CONNECTOR_GI_H
