#ifndef DIALOG_GRAPH_H
#define DIALOG_GRAPH_H

#include <qgraphicsview_nowheel.h>

#include <QPainter>
#include <QGraphicsScene>
#include <QDialog>

namespace Ui {
class Dialog_Graph;
}

class Dialog_Graph : public QDialog
{
    Q_OBJECT


private:
    bool            isInit;
    bool            toggle_D_Graph;
    QRect           d_Position;

    QGraphicsScene  *sceneAxial;
    QGraphicsScene  *sceneRadial;

    QImage          *imageAxial;
    QImage          *imageRadial;
    QPainter        *painterAxial;
    QPainter        *painterRadial;

    QPen            blackPen1;
    QPen            blackPen2;
    QPen            blackPen3;
    QPen            blackPen20;
    QPen            redPen1;
    QPen            redPenDash;
    QPen            bluePen1;
    QPen            bluePenDash;
    QPen            grayDash;

public:
    explicit Dialog_Graph(QWidget *parent = 0);
    ~Dialog_Graph();

    void            traceSpoke(int flange , int nHub , float xHub , float yHub , float xRim, float yRim, float radialO , bool SPL, bool SPR);
    void            traceHubRim(float dL , float dR ,float wL , float wR , float old , float erd , float zL , float zR);
    void            clearGraph(void);
    void            fitGraph(void);
    void            setToggle_D_Graph();
    QImage          *getWheelAxial() const;
    QImage          *getWheelRadial() const;

private:
    Ui::Dialog_Graph *ui;


protected:
    virtual void    resizeEvent(QResizeEvent* event);
    void            closeEvent(QCloseEvent *event);

public slots:
    void            imageCalculate(void);
};

#endif // DIALOG_GRAPH_H
