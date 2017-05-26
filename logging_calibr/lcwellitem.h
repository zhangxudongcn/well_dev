#pragma once
#include <QGraphicsWidget>
#include <QVector>
class LCUpdateNotifier;
class LCCurveItem;
class LCWellItem : public QGraphicsWidget {
public:
	LCWellItem(QGraphicsItem *parent = Q_NULLPTR, Qt::WindowFlags wFlags = Qt::WindowFlags());
	~LCWellItem();
	void onUpdate(const LCUpdateNotifier &update_notifier);
private:
	QVector<LCCurveItem*> _curve_vec;
};