#pragma once
#include <QGraphicsItemGroup>
class QGraphicsPathItem;
class LCTraceItem : public QGraphicsItemGroup {
public:
	LCTraceItem(QGraphicsItem *parent = Q_NULLPTR);
	~LCTraceItem();
	QPointF tracePos() const { return _pos; }
	void setTracePos(const QPointF &pos);
	const QPolygonF &traceData() const { return _trace_data; }
	void setTraceData(const QPolygonF &trace_data);
private:
	QPointF _pos;
	QGraphicsPathItem *_fill_item;
	QGraphicsPathItem *_wiggle_item;
	QPolygonF _trace_data;
};