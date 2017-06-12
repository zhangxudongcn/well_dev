#include "lcseismicwidget.h"
#include "lcupdatenotifier.h"
#include "lctraceitem.h"
#include "lcdefine.h"
#include "lcdata.h"
#include "lctopitem.h"
#include "lcmainwindow.h"
#include "lcseismiccontainer.h"
#include "ai_data_include.h"
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
	if (update_notifier.dataChangedFlag() | LCENV::CurrentWellChanged) {
		_scene->clear();
		QRectF scene_rect;
		scene_rect.setTop(LCENV::MW->lcData()->timeMin() * 1000);
		scene_rect.setBottom(LCENV::MW->lcData()->timeMax() * 1000);
		scene_rect.setLeft(0);
		scene_rect.setRight(((LCSeismicContainer*)parent())->widthCM() * LCENV::PixelPerCM);
		_scene->setSceneRect(scene_rect);

		QPair<QVector<float>, QVector<float>> time_depth_curve = LCENV::MW->lcData()->timeDepthCurve();

		aiDataWell *well_data = LCENV::MW->lcData()->wellData();
		aiGridCrd grid_coord = LCENV::MW->lcData()->survey()->Convert(well_data->GetPos()/100);

		GPoint pos = well_data->GetPos();

	}
}

void LCSeismicWidget::optionsChanged()
{

}