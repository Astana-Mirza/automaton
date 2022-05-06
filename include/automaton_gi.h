#ifndef AUTOMATON_GI_H
#define AUTOMATON_GI_H

#include <QWidget>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QString>

class AutomatonGI: public QGraphicsItem
{
public:
    explicit AutomatonGI(uint32_t index = 0);
    ~AutomatonGI();

    void set_input ( AutomatonGI* input  = nullptr ) { this->input = input; }
    void set_output( AutomatonGI* output = nullptr ) { this->output = output; }

    bool is_input_set() const { return input; }
    bool is_output_set() const { return output; }

    AutomatonGI* get_input() const { return input; }
    AutomatonGI* get_output() const { return output; }

    QRectF boundingRect() const;
protected:
    void paint(
        QPainter *painter,
        const QStyleOptionGraphicsItem *option,
        QWidget *widget
    );

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    AutomatonGI* input  = nullptr;
    AutomatonGI* output = nullptr;
    uint32_t automaton_index;
};

#endif // AUTOMATON_GI_H
