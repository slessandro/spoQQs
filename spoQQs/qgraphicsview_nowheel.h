#ifndef QGRAPHICSVIEW_NOWHEEL_H
#define QGRAPHICSVIEW_NOWHEEL_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWheelEvent>
#include <QWidget>

class QGraphicsView_nowheel : public QGraphicsView
{
public:
    QGraphicsView_nowheel(QWidget * parent = nullptr);
    QGraphicsView_nowheel(QGraphicsScene * scene, QWidget * parent = nullptr);

protected:
    virtual void wheelEvent(QWheelEvent * event);
};

#endif // QGRAPHICSVIEW_NOWHEEL_H
