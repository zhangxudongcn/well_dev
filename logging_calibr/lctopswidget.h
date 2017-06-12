#pragma once
#include <QGraphicsItemGroup>
#include "lcgraphicsview.h"
#include "lcvalueaxis.h"
class LCTopsContainer;
class LCUpdateNotifier;
class LCTopsWidget : public LCGraphicsView {
public:
	LCTopsWidget(QWidget *parent = Q_NULLPTR);
	~LCTopsWidget() {};

	LCTopsContainer *topsContainer() const { return (LCTopsContainer*)parent(); }
	virtual void onUpdate(const LCUpdateNotifier &update_notifier);
	virtual void optionsChanged();
private:
	QGraphicsScene *_scene;

};
