#include <automaton_gi.h>

AutomatonGI::AutomatonGI(uint32_t index):
        QGraphicsItem(),
        automaton_index(index)
{

}

AutomatonGI::~AutomatonGI()
{

}

QRectF AutomatonGI::boundingRect() const
{
    return QRectF(-60, -35, 120, 70);
}

void AutomatonGI::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPolygon polygon;

    polygon << QPoint(-35, -35) << QPoint(-35, 35)
            << QPoint(35, 35) << QPoint(35, -35);
    painter->setPen(Qt::black);
    painter->drawText(
        QRect{-20, -20, 40, 40},
        Qt::AlignHCenter | Qt::AlignVCenter,
        QString::number(this->automaton_index)
    );

    QFont in_out_font = painter->font();
    in_out_font.setPixelSize(10);
    painter->setFont(in_out_font);
    painter->drawText(
        QRect{-50, -15, 13, 15},
        Qt::AlignRight | Qt::AlignVCenter,
        "in"
    );
    painter->drawText(
        QRect{38, -15, 15, 15},
        Qt::AlignLeft | Qt::AlignVCenter,
        "out"
    );

    painter->setBrush(QBrush(Qt::NoBrush));
    painter->drawPolygon(polygon);
    painter->drawLine(!input ? -60 : -45, 0, -35, 0);
    painter->drawLine(!output ? 60 :  45, 0,  35, 0);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}


void AutomatonGI::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    this->setPos(
        event->scenePos().x(),
        event->scenePos().y()
    );
}

void AutomatonGI::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ClosedHandCursor));
}

void AutomatonGI::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ArrowCursor));
}
