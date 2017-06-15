#include "stdafx.h"

#include "lctopswidget.h"
#include "lcdefine.h"
#include "lcdata.h"
#include "lctopscontainer.h"
#include "lcupdatenotifier.h"
#include "lcmainwindow.h"
#include "lcdata.h"
#include "lctopitem.h"
#include "ai_data_include.h"
#include <QPainterPath>
#include <QOpenGLWidget>
LCTopsWidget::LCTopsWidget(QWidget *parent)
	: LCGraphicsView(parent), _scene( new QGraphicsScene())
{
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setScene(_scene); 
	//setViewport(new QOpenGLWidget(this));
}

void LCTopsWidget::onUpdate(const LCUpdateNotifier &update_notifier)
{
	if (update_notifier.dataChangedFlag() | LCENV::CurrentWellChanged) {
		QPair<QVector<float>, QVector<float>> time_depth_curve = LCENV::MW->lcData()->timeDepthCurve();
		QSettings &options = LCENV::MW->lcOptions();
		float ms_per_cm = options.value("Seismic/MSPerCM").toFloat();
		double time_pixel = ((time_depth_curve.first.back() - time_depth_curve.first.first()) * 1000 / ms_per_cm * LCENV::PixelPerCM);
		aiDataWell *well_data = LCENV::MW->lcData()->wellData();
		QVector<float> depth_data = well_data->GetDepth();
		QRectF scene_rect;
		scene_rect.setTop(time_depth_curve.second.first());
		scene_rect.setBottom(time_depth_curve.second.back());
		scene_rect.setLeft(0);
		scene_rect.setRight(((QWidget*)parent())->width());
		_scene->setSceneRect(scene_rect);

		QTransform matrix;
		matrix.scale(1.0, time_pixel / (time_depth_curve.second.back() - time_depth_curve.second.first()));
		setTransform(matrix);
		for (const auto &name : well_data->GetTopNames()) {
			aiDataWell::Top top = well_data->GetTop(name);
			LCTopItem *top_item = new LCTopItem();			
			_scene->addItem(top_item);
			top_item->setTop(name);
		}
	}
}

void LCTopsWidget::optionsChanged()
{

}