#include "stdafx.h"

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

void LCTraceItem::setTraceData(const QPair<QVector<float>, QVector<float>> &trace_data)
{
	_trace_data = trace_data;

	QSettings &options = LCENV::MW->lcOptions();
	bool draw_wiggle = options.value("Seismic/DrawWiggle").toBool();

	QPainterPath wiggle_path;
	if (draw_wiggle == true) {
		wiggle_path.moveTo(trace_data.second.first(), trace_data.first.first());
		for (int sample_index = 1; sample_index < trace_data.first.size(); sample_index++) {
			wiggle_path.lineTo(trace_data.second[sample_index], trace_data.first[sample_index]);
		}
	}
	//wiggle_path.translate(_pos.x(), 0);
	_wiggle_item->setBrush(Qt::NoBrush );
	_wiggle_item->setPath(wiggle_path);

	int fill_wiggle = options.value("Seismic/FillWiggle").toInt();
	float trace_ext_pixel = 1.0f / options.value("Seismic/TracesPerCM").toFloat() * options.value("Seismic/MaxExtTrace").toFloat() * LCENV::PixelPerCM;

	QPainterPath fill_path = wiggle_path;

	switch (fill_wiggle) {
	case LCENV::FillPositive | LCENV::FillNegative: {
		break;
	}
	case LCENV::FillPositive: {
		QPainterPath clip_path;
		clip_path.addRect(QRectF(0, trace_data.first.first(), trace_ext_pixel, trace_data.first.back() - trace_data.first.first()));
		fill_path = fill_path.intersected(clip_path);
		break;
	}
	case LCENV::FillNegative: {
		QPainterPath clip_path;
		clip_path.addRect(QRectF(-trace_ext_pixel, trace_data.first.first(), trace_ext_pixel, trace_data.first.back() - trace_data.first.first()));
		fill_path = fill_path.intersected(clip_path);
		break;
	}
	default: {
		fill_path = QPainterPath();
	}
	}	

	_fill_item->setPen(Qt::NoPen);
	_fill_item->setPath(fill_path);
}

