#include "lctraceitem.h"
#include <QGraphicsPathItem>
LCTraceItem::LCTraceItem(QGraphicsItem *parent) : QGraphicsItemGroup(parent)
{
	_fill_item = new QGraphicsPathItem(this);
	_wiggle_item = new QGraphicsPathItem(this);
}
LCTraceItem::~LCTraceItem()
{

}
void LCTraceItem::setTracePos(const QPointF &pos)
{
	QPointF offset_p = pos - _pos;
	_pos = pos;
	QPainterPath fill_path = _fill_item->path();
	fill_path.translate(offset_p);
	_fill_item->setPath(fill_path);
	QPainterPath wiggle_path = _wiggle_item->path();
	wiggle_path.translate(offset_p);
	_wiggle_item->setPath(wiggle_path);
}

void LCTraceItem::setTraceData(const QPolygonF &trace_data)
{
	_trace_data = trace_data;


}

