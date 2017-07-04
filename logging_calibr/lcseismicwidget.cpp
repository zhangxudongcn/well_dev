#include "stdafx.h"
#include "lcseismicwidget.h"
#include "lcupdatenotifier.h"
#include "lctraceitem.h"
#include "lcdefine.h"
#include "lcdata.h"
#include "lctopitem.h"
#include "lcmainwindow.h"
#include "lcseismiccontainer.h"
#include "ai_data_include.h"
#include "lctraceitemgroup.h"
#include "lctraceitem.h"
#include <math.h>

LCSeismicWidget::LCSeismicWidget(QWidget *parent) : LCGraphicsView(parent), _scene(new QGraphicsScene())
{
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setScene(_scene);
}
LCSeismicWidget::~LCSeismicWidget()
{}

void LCSeismicWidget::onUpdate(const LCUpdateNotifier &update_notifier)
{
	if (update_notifier.dataChangedFlag() & LCENV::CurrentWellChanged) {
		QSettings &options = LCENV::MW->lcOptions();

		_scene->clear();
		QRectF scene_rect;
		scene_rect.setTop(LCENV::MW->lcData()->timeMin() * 1000);
		scene_rect.setBottom(LCENV::MW->lcData()->timeMax() * 1000);
		scene_rect.setLeft(0);
		scene_rect.setRight(((LCSeismicContainer*)parent())->widthCM() * LCENV::PixelPerCM);
		_scene->setSceneRect(scene_rect);

		/* set y scale */
		float ms_per_cm = options.value("Seismic/MSPerCM").toFloat();
		float y_scale = LCENV::PixelPerCM / ms_per_cm;
		scale(1.0, y_scale);

		/* set seismic */
		setSeismic();

		/* set tops */
		setTops();
	}
}

void LCSeismicWidget::optionsChanged()
{

}


void LCSeismicWidget::reset()
{
	/*
	if (_curve_item != nullptr) {
		delete _curve_item;
		_curve_item = nullptr;
	}
	*/
	for (auto top_item : _top_items) {
		delete top_item;
	}
	_top_items.clear();
}
void LCSeismicWidget::setSeismic()
{
	QSettings &options = LCENV::MW->lcOptions();

	int il_num = options.value("WellSeismic/ILTraceNum").toInt();
	int xl_num = options.value("WellSeismic/XLTraceNum").toInt();
	QVector<QPair<QVector<float>, QVector<float>>> all_trace_data = LCENV::MW->lcData()->wellSeismic(il_num, xl_num);

	float ext_trace = options.value("Seismic/MaxExtTrace").toFloat();
	float trace_step = 1.f / options.value("Seismic/TracesPerCM").toFloat();
	for (auto &trace_data : all_trace_data) {
		float max_abs_value = FLT_MIN;
		for (const auto &value : trace_data.second) {
			if (fabs(value) > max_abs_value) {
				max_abs_value = fabs(value);
			}
		}
		for (auto &value : trace_data.second) {
			value = value / max_abs_value * ext_trace * trace_step * LCENV::PixelPerCM;
			if (fabs(value) < 1) {
				value = 0.f;
			}
		}
		trace_data.second.first() = 0.f;
		trace_data.second.back() = 0.f;
	}

	float margin = options.value("Seismic/Margin").toFloat();
	float trace_per_cm = options.value("Seismic/TracesPerCM").toFloat();

	QColor fill_color = QColor( options.value("WellSeismic/Color").toInt() );
	QColor average_color = QColor( options.value("AverageTrace/Color").toInt() );

	LCTraceItemGroup *trace_group = new LCTraceItemGroup();
	LCTraceItem *trace_item;
	for (int index = 0; index < all_trace_data.size(); index++) {
		trace_item = new LCTraceItem(trace_group);
		trace_item->setPos(QPointF(LCENV::PixelPerCM * (margin + index / trace_per_cm), all_trace_data[index].first.first()));

		trace_item->setTraceData(all_trace_data[index]);
		trace_item->wiggleItem()->setPen(fill_color);
		trace_item->fillItem()->setBrush( fill_color );

		trace_item->show();
	}
	trace_item->wiggleItem()->setPen(average_color);
	trace_item->fillItem()->setBrush(average_color);

	trace_group->setPos(QPointF(0, 0));
	_scene->addItem(trace_group);

}
void LCSeismicWidget::setTops()
{

	/* add top items */
	for (auto top_item : _top_items) {
		delete top_item;
	}
	_top_items.clear();
	aiDataWell *well_data = LCENV::MW->lcData()->wellData();
	for (const auto &name : well_data->GetTopNames()) {
		aiDataWell::Top top = well_data->GetTop(name);
		LCTopItem *top_item = new LCTopItem();
		_top_items.push_back(top_item);
		_scene->addItem(top_item);
		top_item->setTop(name);
	}
}
