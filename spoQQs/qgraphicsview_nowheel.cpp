#include <qgraphicsview_nowheel.h>





QGraphicsView_nowheel::QGraphicsView_nowheel(QWidget * parent)
: QGraphicsView(parent) {}





QGraphicsView_nowheel::QGraphicsView_nowheel(QGraphicsScene * scene, QWidget * parent)
: QGraphicsView(scene, parent) {}





void QGraphicsView_nowheel::wheelEvent(QWheelEvent * event)
{
    if (event->modifiers() & Qt::ControlModifier)
        {
        QGraphicsView::wheelEvent(event);
        }
    else
        {
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        double scaleFactor = 1.15;
        if(event->delta() > 0)
            {
            scale(scaleFactor, scaleFactor);
            }
        else
            {
            scale(1.0 / scaleFactor, 1.0 / scaleFactor);
            }
        }
}
