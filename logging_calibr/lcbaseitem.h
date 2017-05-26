#pragma once
#include <QtCharts>
using namespace QtCharts;
class LCUpdateNotifier;
class LCBaseItem : public QChart {
public:
	LCBaseItem(QGraphicsItem *parent = Q_NULLPTR, Qt::WindowFlags wFlags = Qt::WindowFlags()) : QChart(parent, wFlags) {};
	virtual ~LCBaseItem() {};
	virtual void onUpdate(const LCUpdateNotifier &update_notifier) = 0;
};