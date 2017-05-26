#pragma once
#include <QGraphicsScene>
class LCUpdateNotifier;
class LCWellItem;
class LCScene : public QGraphicsScene
{
public:
    LCScene(QObject *parent = Q_NULLPTR ) : QGraphicsScene( parent ), _well_item(nullptr) {}
    LCScene(const QRectF &sceneRect, QObject *parent = Q_NULLPTR) : QGraphicsScene( sceneRect, parent ), _well_item(nullptr) {}
    LCScene(qreal x, qreal y, qreal width, qreal height, QObject *parent = Q_NULLPTR) : QGraphicsScene( x,y,width,height,parent), _well_item(nullptr) {}
	virtual void onUpdate(const LCUpdateNotifier &update_notifier);
private:
	LCWellItem *_well_item;
};

