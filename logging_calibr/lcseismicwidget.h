#pragma once
#include "lcgraphicsview.h"
#include <QList>
class LCUpdateNotifier;
class LCTopItem;
class LCSeismicWidget : public LCGraphicsView {
public:
	LCSeismicWidget(QWidget *parent = Q_NULLPTR);
	~LCSeismicWidget();

	virtual void onUpdate(const LCUpdateNotifier &update_notifier);
	virtual void optionsChanged();
protected:
	void reset();
	void setSeismic();
	void setTops();
private:
	QGraphicsScene *_scene;
	QList<LCTopItem*> _top_items;
};