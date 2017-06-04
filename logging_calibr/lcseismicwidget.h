#pragma once
#include "lcgraphicsview.h"
#include <QList>
class LCUpdateNotifier;
class LCSeismicWidget : public LCGraphicsView {
public:
	LCSeismicWidget(QWidget *parent = Q_NULLPTR);
	~LCSeismicWidget();

	virtual void onUpdate(const LCUpdateNotifier &update_notifier);
	virtual void optionsChanged();
private:
	QGraphicsScene *_scene;
};