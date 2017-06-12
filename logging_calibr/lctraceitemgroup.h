#pragma once
#include <QGraphicsItemGroup>
#include "lcdefine.h"

class LCTraceItem;
class LCTraceItemGroup : public QGraphicsItemGroup {
public:
	LCTraceItemGroup(QGraphicsItem *parent = Q_NULLPTR);
	~LCTraceItemGroup();
	virtual int type() const override { return LCENV::TraceItemGroup; }

private:
};