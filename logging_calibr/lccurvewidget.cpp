#include "stdafx.h"
#include "lccurvewidget.h"
#include "lcdefine.h"
#include "lcdata.h"
#include "lccurvecontainer.h"
#include "lcupdatenotifier.h"
#include "lcmainwindow.h"
#include "lctopitem.h"
#include "ai_data_include.h"
#include <QPainterPath>
#include <QOpenGLWidget>
LCCurveWidget::LCCurveWidget(QWidget *parent) 
	: LCGraphicsView(parent), _scene( new QGraphicsScene()), _range_ext_prec( 0.1 )
{
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setScene(_scene); 
	//setViewport(new QOpenGLWidget(this));
}

void LCCurveWidget::setValueRangeExt(double perc)
{
	_range_ext_prec = perc;
}

void LCCurveWidget::setCurves(const QList<QPolygonF> &curves)
{

}
void LCCurveWidget::setVertAxis(const QList<LCValueAxis> &axis)
{

}
void LCCurveWidget::setHoriAxis(const QList<LCValueAxis> &axis)
{

}
void LCCurveWidget::onUpdate(const LCUpdateNotifier &update_notifier)
{
	if (update_notifier.dataChangedFlag() | LCENV::CurrentWellChanged) {
		// set scene
		QSettings &options = LCENV::MW->lcOptions();
		float range_ext_prec = options.value("Curve/CurveRangeExt").toFloat();
		QRectF scene_rect;
		scene_rect.setTop( LCENV::MW->lcData()->timeMin() * 1000 ); /* to ms */
		scene_rect.setBottom(LCENV::MW->lcData()->timeMax() * 1000); /* to ms */
		scene_rect.setLeft( 0 );
		float scene_width = ((LCCurveContainer*)parent())->widthCM() * LCENV::PixelPerCM;
		scene_rect.setRight(scene_width + scene_width * range_ext_prec * 2);
		_scene->setSceneRect(scene_rect);


		QPair<QVector<float>, QVector<float>> time_depth_curve = LCENV::MW->lcData()->timeDepthCurve();
		aiDataWell *well_data = LCENV::MW->lcData()->wellData();
		QString curve_name = ((LCCurveContainer*)parent())->curveName();
		QVector<float> curve_data = well_data->GetCurve(curve_name);
		QPolygonF curve_points;
		double min_value = DBL_MAX, max_value = DBL_MIN;
		for (int index = 0; index < curve_data.size(); index++) {
			if ( isnan( curve_data[index] ) == false ) {
				curve_points.push_back(QPointF(curve_data[index], time_depth_curve.first[index] * 1000 )); /* to time domain ms*/
				if (curve_data[index] > max_value) {
					max_value = curve_data[index];
				}
				if (curve_data[index] < min_value) {
					min_value = curve_data[index];
				}
			}
		}
		_map_to_device_matrix.reset();
		_map_to_device_matrix *= QTransform::fromTranslate(-min_value, 0);
		_map_to_device_matrix *= QTransform::fromScale(1.0 / (max_value - min_value) * (scene_width - scene_width * range_ext_prec * 2), 1.0);
		_map_to_device_matrix *= QTransform::fromTranslate(scene_width * range_ext_prec, 0);

		curve_points = _map_to_device_matrix.map(curve_points);

		QPainterPath path(curve_points.first());
		for (auto &p : curve_points) {
			path.lineTo(p);
		}
		_scene->addPath(path, QPen(QColor(LCENV::MW->lcData()->wellGroup()->GetCurveColor(curve_name)), 0 ) );
		for (const auto &name : well_data->GetTopNames()) {
			aiDataWell::Top top = well_data->GetTop(name);
			LCTopItem *top_item = new LCTopItem();
			_scene->addItem(top_item);
			top_item->setTop(name);
		}
	}
}

void LCCurveWidget::optionsChanged()
{

}