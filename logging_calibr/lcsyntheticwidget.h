#pragma once
#include "lcgraphicsview.h"
class LCUpdateNotifier;
class LCSyntheticWidget : public LCGraphicsView {
public:
	LCSyntheticWidget(QWidget *parent = Q_NULLPTR);
	~LCSyntheticWidget();
	virtual void onUpdate(const LCUpdateNotifier &update_notifier);
	virtual void optionsChanged();
private:
	QGraphicsScene *_scene;
};

