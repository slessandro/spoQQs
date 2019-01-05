#include <dialog_graph.h>
#include <ui_dialog_graph.h>

#include <QWheelEvent>
#include <QCloseEvent>
#include <QResizeEvent>
#include <QDebug>





Dialog_Graph::Dialog_Graph(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Graph)
{
    ui->setupUi(this);

    isInit = true;
    d_Position = this->geometry();
    toggle_D_Graph = true;

    sceneAxial = new QGraphicsScene (this);
    ui->graphicsViewAxial->setScene(sceneAxial);

    sceneRadial = new QGraphicsScene (this);
    ui->graphicsViewRadial->setScene(sceneRadial);

    imageAxial   = new QImage(2400,2400,QImage::Format_ARGB32_Premultiplied);
    imageRadial  = new QImage( 600,2400,QImage::Format_ARGB32_Premultiplied);

    imageAxial->fill(Qt::transparent);
    imageRadial->fill(Qt::transparent);

    painterAxial  = new QPainter(imageAxial);
    painterAxial->setRenderHint(QPainter::Antialiasing,true);
    painterAxial->setPen(Qt::NoPen);
    painterAxial->setBrush(QBrush(Qt::white));

    painterRadial = new QPainter(imageRadial);
    painterRadial->setRenderHint(QPainter::Antialiasing,true);
    painterRadial->setPen(Qt::NoPen);
    painterRadial->setBrush(QBrush(Qt::white));

    blackPen1.setColor(Qt::black);
    blackPen1.setWidthF(1);

    blackPen2.setColor(Qt::black);
    blackPen2.setWidthF(2);

    blackPen3.setColor(Qt::black);
    blackPen3.setWidthF(3);

    blackPen20.setColor(Qt::black);
    blackPen20.setWidthF(20);

    redPen1.setColor(Qt::red);
    redPen1.setWidthF(1);
    redPen1.setCapStyle(Qt::RoundCap);

    redPenDash.setColor(Qt::red);
    redPenDash.setWidthF(1);
    redPenDash.setCapStyle(Qt::RoundCap);
    redPenDash.setDashPattern({5,5});

    bluePen1.setColor(Qt::blue);
    bluePen1.setWidthF(1);
    bluePen1.setCapStyle(Qt::RoundCap);

    bluePenDash.setColor(Qt::blue);
    bluePenDash.setWidthF(1);
    bluePenDash.setCapStyle(Qt::RoundCap);
    bluePenDash.setDashPattern({5,5});

    grayDash.setColor(Qt::gray);
    grayDash.setWidthF(1);
    grayDash.setCapStyle(Qt::RoundCap);
    grayDash.setDashPattern({5,5});
}





Dialog_Graph::~Dialog_Graph()
{
    delete ui;
}





void Dialog_Graph::traceSpoke(int flange, int nHub, float xHub, float yHub, float xRim, float yRim, float radialO , bool SPL, bool SPR)
{
    float   scale  = 2.0;
    float   diam   = 2.4;
    float   sinangle;
    float   cosangle;

    xHub = +xHub*scale;
    xRim = +xRim*scale;

    yHub = -yHub*scale;
    yRim = -yRim*scale;

    radialO = radialO*scale;

    sinangle = (yRim-yHub) / sqrt((xRim-xHub)*(xRim-xHub) + (yRim-yHub)*(yRim-yHub));
    cosangle = (xRim-xHub) / sqrt((xRim-xHub)*(xRim-xHub) + (yRim-yHub)*(yRim-yHub));

    if (flange == 0)
        {
        if (SPL)
            {
            xHub = xHub + radialO*cosangle;
            yHub = yHub + radialO*sinangle;
            sceneAxial->addLine(xHub-diam*sinangle,yHub+diam*cosangle,xHub+diam*sinangle,yHub-diam*cosangle,redPen1);
            }
        else
            sceneAxial->addEllipse(xHub-(diam*scale/2),yHub-(diam*scale/2),diam*scale,diam*scale,blackPen1);
        if (nHub == 0)
            {
            sceneAxial->addLine(xHub,yHub,xRim,yRim,redPenDash);
            }
        else
            {
            sceneAxial->addLine(xHub,yHub,xRim,yRim,redPen1);
            }
        }
    else
        {
        if (SPR)
            {
            xHub = xHub + radialO*cosangle;
            yHub = yHub + radialO*sinangle;
            sceneAxial->addLine(xHub-diam*sinangle,yHub+diam*cosangle,xHub+diam*sinangle,yHub-diam*cosangle,bluePen1);
            }
        else
            sceneAxial->addEllipse(xHub-(diam*scale/2),yHub-(diam*scale/2),diam*scale,diam*scale,blackPen1);
        if (nHub == 0)
            {
            sceneAxial->addLine(xHub,yHub,xRim,yRim,bluePenDash);
            }
        else
            {
            sceneAxial->addLine(xHub,yHub,xRim,yRim,bluePen1);
            }
        }
}





void Dialog_Graph::traceHubRim(float dL, float dR, float wL, float wR, float old , float erd, float zL, float zR)
{
    float scale = 2.0;
    float offst = 5.0;
    float width;

    dL    = dL*scale;
    dR    = dR*scale;
    wL    = wL*scale;
    wR    = wR*scale;
    old   = old*scale;
    erd   = erd*scale;
    zL    = zL*scale;
    zR    = zR*scale;
    offst = offst*scale;

    width = blackPen3.width();
    blackPen3.setWidthF(width*scale);
    width = blackPen20.width();
    blackPen20.setWidthF(width*scale);


    sceneRadial->addLine(0.0,-erd/2.0,0.0,+erd/2.0,grayDash);

    sceneRadial->addLine(-wL,+dL/2.0,-wL+zL,+erd/2.0,redPen1);
    sceneRadial->addLine(+wR,+dR/2.0,+wR-zR,+erd/2.0,bluePen1);

    sceneRadial->addLine(-wL,-dL/2.0,-wL+zL,-erd/2.0,redPen1);
    sceneRadial->addLine(+wR,-dR/2.0,+wR-zR,-erd/2.0,bluePen1);

    sceneAxial->addEllipse((-dL-offst)/2.0,(-dL-offst)/2.0,dL+offst,dL+offst,blackPen2);
    sceneAxial->addEllipse((-dR-offst)/2.0,(-dR-offst)/2.0,dR+offst,dR+offst,blackPen2);
    sceneRadial->addLine(-wL,-dL/2.0,-wL,dL/2.0,blackPen3);
    sceneRadial->addLine(+wR,-dR/2.0,+wR,dR/2.0,blackPen3);
    sceneRadial->addLine(-old/2+2*offst,0,+old/2-2*offst,0,blackPen20);

    sceneAxial->addEllipse(-erd/2.0,-erd/2.0,erd,erd,blackPen3);
    sceneRadial->addLine(-wL+zL,+erd/2.0,+wR-zR,+erd/2.0,blackPen3);
    sceneRadial->addLine(-wL+zL,-erd/2.0,+wR-zR,-erd/2.0,blackPen3);

    width = blackPen3.width();
    blackPen3.setWidthF(width/scale);
    width = blackPen20.width();
    blackPen20.setWidthF(width/scale);
}





void Dialog_Graph::clearGraph()
{
    sceneAxial->clear();
    sceneRadial->clear();
}





void Dialog_Graph::fitGraph()
{
    ui->graphicsViewAxial->fitInView(sceneAxial->sceneRect() , Qt::KeepAspectRatio);
    ui->graphicsViewRadial->fitInView(sceneRadial->sceneRect() , Qt::KeepAspectRatio);
}





void Dialog_Graph::setToggle_D_Graph()
{
    if (toggle_D_Graph)
        {
        this->setGeometry(d_Position);
        this->show();
        }
    else
        {
        d_Position = this->geometry();
        this->hide();
        }
    toggle_D_Graph = !toggle_D_Graph;
}





QImage* Dialog_Graph::getWheelAxial() const
{
    return imageAxial;
}





QImage* Dialog_Graph::getWheelRadial() const
{
    return imageRadial;
}





void Dialog_Graph::resizeEvent(QResizeEvent *event)
{
    if (isInit)
        {
        isInit = false;
        ui->graphicsViewAxial->viewport()->resize(ui->graphicsViewAxial->size());
        ui->graphicsViewRadial->viewport()->resize(ui->graphicsViewRadial->size());
        }
    ui->graphicsViewAxial->fitInView(sceneAxial->sceneRect() , Qt::KeepAspectRatio);
    ui->graphicsViewRadial->fitInView(sceneRadial->sceneRect() , Qt::KeepAspectRatio);

    event->accept();
}





void Dialog_Graph::closeEvent(QCloseEvent *event)
{
    d_Position = this->geometry();
    toggle_D_Graph = true;
    event->accept();
}





void Dialog_Graph::imageCalculate()
{
    sceneAxial->render(painterAxial);
//    imageAxial->save("WheelA.png");

    sceneRadial->render(painterRadial);
//    imageRadial->save("WheelR.png");
}
