#pragma once
#include "lcdefine.h"
#include <QGraphicsPathItem>
class LCCurveItem : public QGraphicsPathItem {
public:
	LCCurveItem(QGraphicsItem *parent = Q_NULLPTR);
	~LCCurveItem() {};
	virtual int type() const override { return LCENV::CurveItem; }
};