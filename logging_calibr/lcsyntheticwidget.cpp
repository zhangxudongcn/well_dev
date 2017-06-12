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
LCSyntheticWidget::LCSyntheticWidget(QWidget *parent) : LCGraphicsView(parent), _scene(new QGraphicsScene())
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
	if (update_notifier.dataChangedFlag() | LCENV::CurrentWellChanged) {
		_scene->clear();
		QRectF scene_rect;
		scene_rect.setTop(LCENV::MW->lcData()->timeMin() * 1000);
		scene_rect.setBottom(LCENV::MW->lcData()->timeMax() * 1000);
		scene_rect.setLeft(0);
		scene_rect.setRight(((LCSyntheticContainer*)parent())->widthCM() * LCENV::PixelPerCM);
		_scene->setSceneRect(scene_rect);


		aiDataWell *well_data = LCENV::MW->lcData()->wellData();
		QVector<float> depth_data = well_data->GetDepth();
		QVector<float> sonic = fillInvalid( well_data->GetCurve( "DT" ) );
		QVector<float> rhob = well_data->GetCurve("RHOB"); /* kg/m3 */

		for (auto &item : rhob) {
			if (isnan(item) == false) {
				item /= 1000.f;
			}
		}

		QPair<QVector<float>,QVector<float>> time_depth_curve =  LCENV::MW->lcData()->timeDepthCurve();
		//QVector<float> imped = impedance(sonic, rhob );
		QVector<float> imped = fillInvalid( well_data->GetCurve( "AI" ) );

		QVector<float> refl = reflectivities(imped);
		QVector<float> new_refl;
		new_refl.push_back(refl.first());
		new_refl += refl;

		/* 进行均匀采样 */
		float sample_interval = 0.004f;
		QPair<QVector<float>, QVector<float >> resample_refl = uniformResampleTimes(time_depth_curve.first, new_refl, sample_interval);
		QVector<float> resample_refl_times = resample_refl.first;
		QVector<float> resample_refl_values = resample_refl.second;

		QSettings &options = LCENV::MW->lcOptions();
/*
		float ms_per_cm = options.value("Seismic/MSPerCM").toFloat();

		double time_pixel = ((time_depth_curve.first.back() - time_depth_curve.first.first()) * 1000 / ms_per_cm * LCENV::PixelPerCM);		
		QTransform matrix;
		matrix.scale(1.0, time_pixel / (time_depth_curve.first.back() * 1000 - time_depth_curve.first.first() * 1000));
		setTransform(matrix);
*/
		float *buffer = new float[resample_refl_values.size()];
		memcpy(buffer, (resample_refl_values.data()), sizeof( float) * resample_refl_values.size());
		convolve_wavelet(2, 1, resample_refl_values.size(), sample_interval, 20, &buffer );
		memcpy((resample_refl_values.data()), buffer, sizeof(float) * resample_refl_values.size());
		delete[]buffer;
		resample_refl_values.first() = 0.f;
		resample_refl_values.back() = 0.f;

		QPolygonF trace_data(resample_refl_times.size());
		float max_abs_value = FLT_MIN;

		for( const auto &item : resample_refl_values ) {
			if (fabs( item ) > max_abs_value) {
				max_abs_value = fabs(item );
			}
		}
		
		float ext_trace =  options.value("Seismic/MaxExtTrace").toFloat();
		float trace_step = 1.f / options.value("Seismic/TracesPerCM").toFloat();
		for (int index = 0; index < resample_refl_times.size(); index++) {
			float x_value = resample_refl_values[index] / max_abs_value * ext_trace * trace_step * LCENV::PixelPerCM;
			if (fabs(x_value) < 1) {
				x_value = 0.0;
			}
			trace_data[index].setX(x_value);
			trace_data[index].setY(resample_refl_times[index]*1000);
		}

		int synthetic_trace_num = options.value("Synthetic/TraceNum").toInt();
		LCTraceItemGroup *trace_group = new LCTraceItemGroup();
		for (int index = 0; index < synthetic_trace_num; index++) {
			LCTraceItem *trace_item = new LCTraceItem( trace_group );
			trace_item->setPos(QPointF( ( index + 1 ) * LCENV::PixelPerCM / 10, resample_refl_times.first()));

			trace_item->setTraceData(trace_data);
			trace_item->show();
		}
		trace_group->setPos(QPointF(0, 0));
		_scene->addItem(trace_group);

		for (const auto &name : well_data->GetTopNames()) {
			aiDataWell::Top top = well_data->GetTop(name);
			top.fDepth = LCENV::MW->lcData()->getTime(top.fDepth) * 1000;
			LCTopItem *top_item = new LCTopItem();
			_scene->addItem(top_item);
			top_item->setTop(name);
		}
	}
}

void LCSyntheticWidget::optionsChanged()
{

}