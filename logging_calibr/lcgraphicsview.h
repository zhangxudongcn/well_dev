#pragma once
#include <QGraphicsView>

class LCGraphicsView : public QGraphicsView
{
public:
	LCGraphicsView(QWidget *parent = Q_NULLPTR);
	~LCGraphicsView(); 
protected:
	void wheelEvent(QWheelEvent *event) override;

};