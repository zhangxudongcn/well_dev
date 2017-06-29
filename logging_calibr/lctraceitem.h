#pragma once
#include <QGraphicsItemGroup>
#include <lcdefine.h>
class QGraphicsPathItem;
class LCTraceItem : public QGraphicsItemGroup {
public:
	LCTraceItem(QGraphicsItem *parent = Q_NULLPTR);
	~LCTraceItem();
	QGraphicsPathItem *fillItem() const { return _fill_item; }
	QGraphicsPathItem *wiggleItem() const { return _wiggle_item; }
	const QPair<QVector<float>, QVector<float>> &traceData() const { return _trace_data; }
	void setTraceData(const QPair<QVector<float>, QVector<float>> &trace_data);

	virtual int type() const override { return LCENV::TraceItem; }

private:
	QGraphicsPathItem *_fill_item;
	QGraphicsPathItem *_wiggle_item;
	QPair<QVector<float>, QVector<float>> _trace_data;
};