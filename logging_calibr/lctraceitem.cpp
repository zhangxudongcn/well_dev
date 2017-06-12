#include "lctraceitem.h"
#include "lcmainwindow.h"
#include "lcdefine.h"
#include <QGraphicsPathItem>
#include <QPen>

LCTraceItem::LCTraceItem(QGraphicsItem *parent) : QGraphicsItemGroup(parent)
{
	_fill_item = new QGraphicsPathItem(this);
	_wiggle_item = new QGraphicsPathItem(this);
	_wiggle_item->setZValue(1);
}
LCTraceItem::~LCTraceItem()
{

}

void LCTraceItem::setTraceData(const QPolygonF &trace_data)
{
	_trace_data = trace_data;

	QSettings &options = LCENV::MW->lcOptions();
	bool draw_wiggle = options.value("Seismic/DrawWiggle").toBool();

	QPainterPath wiggle_path;
	if (draw_wiggle == true) {
		wiggle_path.moveTo(trace_data.first());
		for (const auto &p : trace_data) {
			wiggle_path.lineTo(p);
		}
	}
	//wiggle_path.translate(_pos.x(), 0);
	_wiggle_item->setPen(QPen(Qt::black, 0));
	_wiggle_item->setPath(wiggle_path);

	int fill_wiggle = options.value("Seismic/FillWiggle").toInt();

	QPainterPath fill_path;
	fill_path.moveTo(0, trace_data.first().y());
	for (const auto &p : trace_data) {
		fill_path.lineTo(p);
	}
	fill_path.moveTo(0, trace_data.back().y());

	switch (fill_wiggle) {
	case LCENV::FillPositive | LCENV::FillNegative: {
		break;
	}
	case LCENV::FillPositive: {
		QPainterPath clip_path;
		clip_path.addRect(QRectF(0, trace_data.first().y(), 10, trace_data.back().y() - trace_data.first().y()));
		fill_path = fill_path.intersected(clip_path);
		break;
	}
	case LCENV::FillNegative: {
		QPainterPath clip_path;
		clip_path.addRect(QRectF(-10, trace_data.first().y(), 10, trace_data.back().y() - trace_data.first().y()));
		fill_path = fill_path.intersected(clip_path);
		break;
	}
	default: {
		fill_path = QPainterPath();
	}
	}
	_fill_item->setPen(Qt::NoPen);
	_fill_item->setBrush(Qt::blue);
	_fill_item->setPath(fill_path);
}

