#pragma once
#include "lcgraphicsview.h"
#include <QList>
class LCUpdateNotifier;
class LCTopItem;
class LCTraceItemGroup;
class LCSyntheticWidget : public LCGraphicsView {
public:
	LCSyntheticWidget(QWidget *parent = Q_NULLPTR);
	~LCSyntheticWidget();
	virtual void onUpdate(const LCUpdateNotifier &update_notifier);
	virtual void optionsChanged();
protected:
	void reset();
	void setSyntheticSeismic();
	void setAverageSeismic();

	void setTops();
	QPair<QVector<float>, QVector<float>>  syntheticTrace() const;
private:
	QGraphicsScene *_scene;	
	LCTraceItemGroup *_synthetic_group;
	LCTraceItemGroup *_average_group;
	QList<LCTopItem*> _top_items;

};

