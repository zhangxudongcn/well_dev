#pragma once
#include "lcgraphicsview.h"
#include <QList>
class LCValueAxis;
class LCLinearAxis;
class LCLinearAxis;
class LCUpdateNotifier;
class LCRulerContainer;
class LCRulerWidget : public LCGraphicsView {
public:
	LCRulerWidget(Qt::Alignment align, QWidget *parent = Q_NULLPTR);
	~LCRulerWidget();
	LCRulerContainer *container() const { (LCRulerContainer*)parent(); }
	Qt::Alignment alignment() const { return _align; }
	LCLinearAxis *axis() const { return _axis; }
	void setAxis(LCLinearAxis *axis);
	virtual void onUpdate(const LCUpdateNotifier &update_notifier);
	virtual void optionsChanged();
	virtual void setRuler();
private:
	Qt::Alignment _align;
	QGraphicsScene *_scene;
	LCLinearAxis *_axis;
};
