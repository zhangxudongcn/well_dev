#include "stdafx.h"
#include "lccurvewidget.h"
#include "lcdefine.h"
#include "lcdata.h"
#include "lccurvecontainer.h"
#include "lcupdatenotifier.h"
#include "lcmainwindow.h"
#include "lccurveitem.h"
#include "lctopitem.h"
#include "ai_data_include.h"
#include <QPainterPath>
#include <QOpenGLWidget>
LCCurveWidget::LCCurveWidget(QWidget *parent)
	: LCGraphicsView(parent), _scene(new QGraphicsScene()), _curve_item(nullptr), _mouse_press( false )
{
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setScene(_scene); 
	setMouseTracking(true);
	//setViewport(new QOpenGLWidget(this));
}
LCCurveWidget::~LCCurveWidget()
{
	reset();
}
void LCCurveWidget::reset()
{
	if (_curve_item != nullptr) {
		delete _curve_item;
		_curve_item = nullptr;
	}
	for (auto top_item : _top_items) {
		delete top_item;
	}
	_top_items.clear();
}

void LCCurveWidget::setCurvePoints(const QPolygonF &curve_points)
{

}
void LCCurveWidget::setVertAxis(const LCValueAxis &axis)
{

}
void LCCurveWidget::setHoriAxis(const LCValueAxis &axis)
{

}
void LCCurveWidget::onUpdate(const LCUpdateNotifier &update_notifier)
{
	if (update_notifier.dataChangedFlag() & LCENV::CurrentWellChanged) {
		reset();
		// set scene
		QSettings &options = LCENV::MW->lcOptions();
		QRectF scene_rect;
		scene_rect.setTop( LCENV::MW->lcData()->timeMin() * 1000 ); /* to ms */
		scene_rect.setBottom(LCENV::MW->lcData()->timeMax() * 1000); /* to ms */
		scene_rect.setLeft( 0 );
		float scene_width = ((LCCurveContainer*)parent())->widthCM() * LCENV::PixelPerCM;
		scene_rect.setRight(scene_width);
		_scene->setSceneRect(scene_rect);

		// set y scale
		float ms_per_cm = options.value("Seismic/MSPerCM").toFloat();
		float y_scale = LCENV::PixelPerCM / ms_per_cm;
		scale(1.0, y_scale);

		/* get curve min and max */
		aiDataWell *well_data = LCENV::MW->lcData()->wellData();
		QString curve_name = ((LCCurveContainer*)parent())->curveName();
		QVector<float> curve_data = well_data->GetCurve(curve_name);
		_min_value = FLT_MAX, _max_value = FLT_MIN;
		for (const auto &value : curve_data) {
			if (isnan(value) == false) {
				if (value > _max_value) {
					_max_value = value;
				}
				if (value < _min_value) {
					_min_value = value;
				}
			}
		}
		/* set curve */
		setCurve();
		/* set tops */
		setTops();
		/* add axis */
	}
	if(update_notifier.dataChangedFlag() & LCENV::TimeDepthCurveChanged) {
		setCurve();
	}
	if (update_notifier.dataChangedFlag() & LCENV::TopChanged) {
		setTops();
	}
}

void LCCurveWidget::setCurve()
{
	if (_curve_item != nullptr) {
		delete _curve_item;
		_curve_item = nullptr;
	}
	QPair<QVector<float>, QVector<float>> time_depth_curve = LCENV::MW->lcData()->timeDepthCurve();
	aiDataWell *well_data = LCENV::MW->lcData()->wellData();
	QString curve_name = ((LCCurveContainer*)parent())->curveName();
	QVector<float> curve_data = well_data->GetCurve(curve_name);
	QPolygonF curve_points;
	for (int index = 0; index < curve_data.size(); index++) {
		if (isnan(curve_data[index]) == false) {
			curve_points.push_back(QPointF(curve_data[index], time_depth_curve.first[index] * 1000)); /* to time domain ms*/
		}
	}
	QTransform map_to_scene_matrix = mapToSceneTransform();
	_curve_points = map_to_scene_matrix.map(curve_points);

	QPainterPath path(_curve_points.first());
	for (auto &p : _curve_points) {
		path.lineTo(p);
	}
	_curve_item = new LCCurveItem();
	_curve_item->setPath(path);
	_curve_item->setPen(QPen(QColor(LCENV::MW->lcData()->wellGroup()->GetCurveColor(curve_name)), 0));
	_scene->addItem(_curve_item);
}
void LCCurveWidget::setTops()
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
QTransform LCCurveWidget::mapToSceneTransform() const
{
	QRectF scene_rect = _scene->sceneRect();

	QSettings &options = LCENV::MW->lcOptions();
	float range_ext_prec = options.value("Curve/CurveRangeExt").toFloat();


	QTransform map_to_scene_matrix;
	map_to_scene_matrix.reset();
	// set X coord matrix
	map_to_scene_matrix *= QTransform::fromTranslate(-_min_value, 0);
	map_to_scene_matrix *= QTransform::fromScale(1.0 / (_max_value - _min_value) * (scene_rect.width() - scene_rect.width() * range_ext_prec * 2), 1.0);
	map_to_scene_matrix *= QTransform::fromTranslate(scene_rect.width() * range_ext_prec, 0);

	return map_to_scene_matrix;

}

void LCCurveWidget::optionsChanged()
{

}


void LCCurveWidget::mousePressEvent(QMouseEvent *event)
{
	QPoint pos = event->pos();
	QPointF scene_pos = mapToScene(pos);
	_mouse_press = true;
	if (event->modifiers() == Qt::ControlModifier) {
		_prev_pos = scene_pos;
	}
}
void LCCurveWidget::mouseReleaseEvent(QMouseEvent *event)
{
	_mouse_press = false;
}
void LCCurveWidget::mouseMoveEvent(QMouseEvent *event)
{
	QPoint pos = event->pos();
	QPointF scene_pos = mapToScene(pos);
	QTransform matrix = mapToSceneTransform().inverted();
	QPointF curve_pos = matrix.map(scene_pos);
	aiDataSeismic *seis_data = LCENV::MW->lcData()->seismicData();
	aiSampleRange sample_range = seis_data->GetSampleRange();
	float time = curve_pos.y();
	float value = curve_pos.x();
	if (value >= _min_value && value <= _max_value) {
		QString message;
		message += "Time: " + QString::number(time) + " Value: " + QString::number(value);
		LCENV::MW->statusBar()->showMessage(message);
	}
	if (event->modifiers() == Qt::ControlModifier && _mouse_press ) {
		float time_offset_ms = scene_pos.y() - _prev_pos.y();
		QPair<QVector<float>, QVector<float>> time_depth_curve = LCENV::MW->lcData()->timeDepthCurve();
		for (auto &time : time_depth_curve.first) {
			time += time_offset_ms / 1000.f;
		}
		LCENV::MW->lcData()->setTimeDepthCurve(time_depth_curve);
		_prev_pos = scene_pos;
	}
	else {
	}
}