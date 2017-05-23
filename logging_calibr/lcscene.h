#pragma once
#include "ui_lcmainwindow.h"
#include <QtWidgets/QGraphicsScene>
class LCScene : public QGraphicsScene
{
public:
    LCScene(QObject *parent = Q_NULLPTR ) : QGraphicsScene( parent ) {}
    LCScene(const QRectF &sceneRect, QObject *parent = Q_NULLPTR) : QGraphicsScene( sceneRect, parent ) {}
    LCScene(qreal x, qreal y, qreal width, qreal height, QObject *parent = Q_NULLPTR) : QGraphicsScene( x,y,width,height,parent) {}
    virtual void modelChanged();
private:

};

