#include "auxcamgraphicsview.h"

//12-12-12
auxcamgraphicsview::auxcamgraphicsview(QWidget *parent): QGraphicsView(parent)
{
}
auxcamgraphicsview::~auxcamgraphicsview()
{
}


//void auxcamgraphicsview::setScene(QGraphicsScene * sc)
//{
//    this->s = sc;
//    this->setScene(sc);
//}

//void auxcamgraphicsview::show()
//{
//    this->show();
//}


void auxcamgraphicsview::mousePressEvent(QMouseEvent* e)
{
    string click;
    vector<int> v(2);
    if(e->buttons() & Qt::LeftButton)
    {
        //qDebug()<<"left button clicked " ;
        click = "left";
        v[0] = static_cast<int>(e->pos().x());
        v[1] = static_cast<int>(e->pos().y());
        emit sendMouseClickEvent(click, v);
    }
    if (e->buttons() & Qt::RightButton)
    {
        //qDebug()<<"right button clicked " ;
        click = "right";
        v[0] = static_cast<int>(e->pos().x());
        v[1] = static_cast<int>(e->pos().y());
        emit sendMouseClickEvent(click, v);
    }
}

//void auxcamgraphicsview::drawBackground(QPainter *painter, const QRectF &rect)
//{

//}

void auxcamgraphicsview::mouseMoveEvent(QMouseEvent* e)
{
    vector<int> v(2);
    v[0] = static_cast<int>(e->pos().x());
    v[1] = static_cast<int>(e->pos().y());
    //qDebug()<< "x-> " << v[0] << "y-> " << v[1];
    emit sendMouseMoveData(v);
}

void auxcamgraphicsview::mouseReleaseEvent(QMouseEvent * e)
{
    vector<int> v(2);
    //qDebug()<<"Mouse release event " ;
    v[0] = static_cast<int>(e->pos().x());
    v[1] = static_cast<int>(e->pos().y());
    //qDebug()<< "x-> " << v[0] << "y-> " << v[1];
    emit sendMouseReleaseEvent(v);
}







