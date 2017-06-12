#pragma once
#include <QGraphicsItemGroup>
#include <lcdefine.h>
class QGraphicsPathItem;
class LCTraceItem : public QGraphicsItemGroup {
public:
	LCTraceItem(QGraphicsItem *parent = Q_NULLPTR);
	~LCTraceItem();
	const QPolygonF &traceData() const { return _trace_data; }
	void setTraceData(const QPolygonF &trace_data);

	virtual int type() const override { return LCENV::TraceItem; }

private:
	QGraphicsPathItem *_fill_item;
	QGraphicsPathItem *_wiggle_item;
	QPolygonF _trace_data;
};