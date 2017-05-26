#pragma once
#include "lcbaseitem.h"
#include <QVector>
class LCUpdateNotifier;
class LCCurveItem;
class LCWellItem : public LCBaseItem {
public:
	LCWellItem(QGraphicsItem *parent = Q_NULLPTR, Qt::WindowFlags wFlags = Qt::WindowFlags());
	~LCWellItem();
	void onUpdate(const LCUpdateNotifier &update_notifier) override;
private:
	QVector<LCCurveItem*> _curve_vec;
};