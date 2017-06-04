#include "lcseismicwidget.h"
#include "lcupdatenotifier.h"
#include "lcdefine.h"
#include "lcdata.h"

LCSeismicWidget::LCSeismicWidget(QWidget *parent) : LCGraphicsView(parent), _scene(new QGraphicsScene())
{
	//setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setScene(_scene);
	return;
	_scene->setSceneRect(QRectF(0, 0, 500, 500));
	QPainterPath path(QPointF( 50, 20) );
	path.lineTo(70, 40);
	path.lineTo(30, 60);
	path.lineTo(50, 60);
	_scene->addPath(path, QPen(Qt::red), QBrush(Qt::blue ) );
}
LCSeismicWidget::~LCSeismicWidget()
{}

void LCSeismicWidget::onUpdate(const LCUpdateNotifier &update_notifier)
{
	if (update_notifier.dataChangedFlag() | LCENV::CurrentWellChanged) {
		_scene->clear();
#if 0
		aiDataWell *well_data = LCENV::WellData->GetWell("F0");
		QString curve_name = ((LCCurveContainer*)parent())->curveName();
		QVector<float> depth_data = well_data->GetCurve(0);
		QVector<float> curve_data = well_data->GetCurve(curve_name);
		QPolygonF curve_points;
		double min_value = DBL_MAX, max_value = DBL_MIN;
		for (int index = 0; index < depth_data.size(); index++) {
			if (curve_data[index] != well_data->nullValue()) {
				curve_points.push_back(QPointF(curve_data[index], depth_data[index]));
				if (curve_data[index] > max_value) {
					max_value = curve_data[index];
				}
				if (curve_data[index] < min_value) {
					min_value = curve_data[index];
				}
			}
		}
		// set scene
		QRectF scene_rect;
		scene_rect.setTop(depth_data.first());
		scene_rect.setBottom(depth_data.back());
		scene_rect.setLeft(min_value - (max_value - min_value) * rangeExtPrec());
		scene_rect.setRight(max_value + (max_value - min_value) * rangeExtPrec());
		scene_rect.setLeft(min_value);
		scene_rect.setRight(max_value);
		scale((curveContainer()->widthCM() * LCENV::PixelPerCm) / fabs(scene_rect.width()), 1.0);
		_scene->setSceneRect(scene_rect);
		QPainterPath path(curve_points.first());
		for (auto &p : curve_points) {
			path.lineTo(p);
		}
		_scene->addPath(path, QPen(Qt::red));
#endif
	}
}

void LCSeismicWidget::optionsChanged()
{

}