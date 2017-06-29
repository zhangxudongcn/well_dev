#include "stdafx.h"
#include "lcsyntheticwidget.h"
#include "lcupdatenotifier.h"
#include "lctraceitem.h"
#include "lcdefine.h"
#include "lcdata.h"
#include "lcalgorithm.h"
#include "lcmainwindow.h"
#include "lctraceitemgroup.h"
#include "lctopitem.h"
#include "lcsyntheticcontainer.h"
#include "ai_data_include.h"
#include <math.h>
extern "C" void convolve_wavelet(int wavelet_type, int nx, int nt, float dt, float fpeak, float **wfieldx);
LCSyntheticWidget::LCSyntheticWidget(QWidget *parent) 
	: LCGraphicsView(parent), _scene(new QGraphicsScene()), _synthetic_group( nullptr ), _average_group( nullptr )
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setScene(_scene);
}
LCSyntheticWidget::~LCSyntheticWidget()
{}

void LCSyntheticWidget::onUpdate(const LCUpdateNotifier &update_notifier)
{
	if (update_notifier.dataChangedFlag() & LCENV::CurrentWellChanged) {
		_scene->clear();
		QRectF scene_rect;
		scene_rect.setTop(LCENV::MW->lcData()->timeMin() * 1000);
		scene_rect.setBottom(LCENV::MW->lcData()->timeMax() * 1000);
		scene_rect.setLeft(0);
		scene_rect.setRight(((LCSyntheticContainer*)parent())->widthCM() * LCENV::PixelPerCM);
		_scene->setSceneRect(scene_rect);

		/* set y scale */
		QSettings &options = LCENV::MW->lcOptions();
		float ms_per_cm = options.value("Seismic/MSPerCM").toFloat();
		float y_scale = LCENV::PixelPerCM / ms_per_cm;
		scale(1.0, y_scale);

		/* set seismic */
		setSyntheticSeismic();

		/* set average seismic */
		setAverageSeismic();

		/* set tops */
		setTops();
	}
	if (update_notifier.dataChangedFlag() & LCENV::TimeDepthCurveChanged) {
		setSyntheticSeismic();
	}
}

void LCSyntheticWidget::optionsChanged()
{

}


void LCSyntheticWidget::reset()
{
	if (_synthetic_group != nullptr) {
		delete _synthetic_group;
		_synthetic_group = nullptr;
	}
	if (_average_group != nullptr) {
		delete _average_group;
		_average_group = nullptr;
	}
	for (auto top_item : _top_items) {
		delete top_item;
	}
	_top_items.clear();

}
void LCSyntheticWidget::setSyntheticSeismic()
{
	if (_synthetic_group != nullptr) {
		delete _synthetic_group;
		_synthetic_group = nullptr;
	}
	QSettings &options = LCENV::MW->lcOptions();
	QPair<QVector<float>, QVector<float>> synthetic_trace = syntheticTrace();

	float max_abs_value = FLT_MIN;
	for (const auto &value : synthetic_trace.second) {
		if (fabs(value) > max_abs_value) {
			max_abs_value = fabs(value);
		}
	}

	float ext_trace = options.value("Seismic/MaxExtTrace").toFloat();
	float trace_step = 1.f / options.value("Seismic/TracesPerCM").toFloat();
	for (int index = 0; index < synthetic_trace.first.size(); index++) {
		synthetic_trace.second[index] = synthetic_trace.second[index] / max_abs_value * ext_trace * trace_step * LCENV::PixelPerCM;
		if (fabs(synthetic_trace.second[index]) < 1) {
			synthetic_trace.second[index] = 0.0;
		}
		synthetic_trace.first[index] *= 1000.f; /* m -> ms */
	}
	synthetic_trace.second.first() = 0.f;
	synthetic_trace.second.back() = 0.f;

	int synthetic_trace_num = options.value("Synthetic/TraceNum").toInt();
	float margin = options.value("Seismic/Margin").toFloat();
	float trace_per_cm = options.value("Seismic/TracesPerCM").toFloat();

	QColor fill_color = options.value("Synthetic/Color").toInt();

	_synthetic_group = new LCTraceItemGroup();
	for (int index = 0; index < synthetic_trace_num; index++) {
		LCTraceItem *trace_item = new LCTraceItem(_synthetic_group);
		trace_item->setPos(QPointF(LCENV::PixelPerCM * (margin + index / trace_per_cm), synthetic_trace.first.first()));

		trace_item->wiggleItem()->setPen(fill_color);
		trace_item->fillItem()->setBrush(fill_color);

		trace_item->setTraceData(synthetic_trace);
		trace_item->show();
	}	
	_scene->addItem(_synthetic_group);
}

void LCSyntheticWidget::setAverageSeismic()
{
	if (_average_group != nullptr) {
		delete _average_group;
		_average_group = nullptr;
	}
	QSettings &options = LCENV::MW->lcOptions();

	int il_num = options.value("WellSeismic/ILTraceNum").toInt();
	int xl_num = options.value("WellSeismic/XLTraceNum").toInt();
	QPair<QVector<float>, QVector<float>> trace_data = LCENV::MW->lcData()->wellSeismic(il_num, xl_num).back();
	float ext_trace = options.value("Seismic/MaxExtTrace").toFloat();
	float trace_step = 1.f / options.value("Seismic/TracesPerCM").toFloat();
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

	float margin = options.value("Seismic/Margin").toFloat();
	float trace_per_cm = options.value("Seismic/TracesPerCM").toFloat();

	QColor average_color = QColor(options.value("AverageTrace/Color").toInt());
	int synthetic_trace_num = options.value("Synthetic/TraceNum").toInt();
	_average_group = new LCTraceItemGroup();	
	float group_x = margin + synthetic_trace_num / trace_per_cm + options.value("Synthetic/Gap").toFloat();
	for (int index = 0; index < synthetic_trace_num; index++) {
		LCTraceItem *trace_item = new LCTraceItem(_average_group);
		trace_item->setPos(QPointF(LCENV::PixelPerCM * (group_x + index / trace_per_cm), trace_data.first.first()));

		trace_item->setTraceData( trace_data );
		trace_item->wiggleItem()->setPen(average_color);
		trace_item->fillItem()->setBrush(average_color);

		trace_item->show();
	}

	_scene->addItem(_average_group);

}

QPair<QVector<float>, QVector<float>>  LCSyntheticWidget::syntheticTrace() const
{
	aiDataWell *well_data = LCENV::MW->lcData()->wellData();

	QVector<float> imped = fillInvalid(well_data->GetImpedance());
	if (imped.size() == 0) {
		QVector<float> sonic = fillInvalid(well_data->GetSonic());
		QVector<float> rhob = well_data->GetDensity(); /* kg/m3 */
		for (auto &item : rhob) {
			if (isnan(item) == false) {
				item /= 1000.f;
			}
		}
		imped = impedance(sonic, rhob);
	}
	
	/* 进行均匀采样 */
	aiDataSeismic *seis_data = LCENV::MW->lcData()->seismicData();
	aiSampleRange sample_range = seis_data->GetSampleRange();
	float sample_interval = sample_range.GetStep() / 1000.f; /* ms->s */
	QPair<QVector<float>, QVector<float>> time_depth_curve = LCENV::MW->lcData()->timeDepthCurve();
	QPair<QVector<float>, QVector<float >> resample_imped = uniformResampleTimes(time_depth_curve.first, imped, sample_interval);

	QVector<float> resample_refl = reflectivities(resample_imped.second);

	float *buffer = new float[resample_refl.size()];
	memcpy(buffer, resample_refl.data(), sizeof(float) * resample_refl.size());
	convolve_wavelet(2, 1, resample_refl.size(), sample_interval, 30, &buffer);
	memcpy(resample_refl.data(), buffer, sizeof(float) * resample_refl.size());
	delete[]buffer;
	resample_refl.first() = 0.f;
	resample_refl.back() = 0.f;
	return QPair<QVector<float>, QVector<float>>(resample_imped.first, resample_refl);
}

void LCSyntheticWidget::setTops()
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