#ifndef CONNECTOR_GI_H
#define CONNECTOR_GI_H

#include <QGraphicsItem>

class AutomatonGI;

class ConnectorGI : public QGraphicsItem
{
public:
    ConnectorGI( AutomatonGI* result_automaton );
    ~ConnectorGI();

    QRectF boundingRect() const;
private:
    void paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget );

    AutomatonGI* result_automaton_; // Автомат, из которого получаем промежуточный результат
};

#endif // CONNECTOR_GI_H
