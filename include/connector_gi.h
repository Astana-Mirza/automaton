#ifndef CONNECTOR_GI_H
#define CONNECTOR_GI_H

#include <QGraphicsItem>

class AutomatonGI;

class ConnectorGI : public QGraphicsItem
{
public:
    ConnectorGI( AutomatonGI* automaton );
    ~ConnectorGI() = default;

    QRectF boundingRect() const;
private:
    void paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget );

    AutomatonGI* automaton_;
};

#endif // CONNECTOR_GI_H
