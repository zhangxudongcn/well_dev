#include "stdafx.h"
#include "lccurvetitle.h"
#include "lcmainwindow.h"
#include "lcrulerwidget.h"
#include "lcdefine.h"
#include "lcupdatenotifier.h"
#include "lclinearaxis.h"
#include "lccurvecontainer.h"
#include "lccurvewidget.h"
#include "lcgraphicsview.h"
#include <QLabel>
#include <QVBoxLayout>
LCCurveTitle::LCCurveTitle(QWidget *parent) : QWidget(parent)
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	QSettings &options = LCENV::MW->lcOptions();
	setFixedHeight( options.value( "WorkTitleHeight" ).toFloat() * LCENV::PixelPerCM );
	QVBoxLayout *layout = new QVBoxLayout();	
	layout->setContentsMargins(QMargins());
	layout->setSpacing(0);

	_title_widget = new LCGraphicsView( this);
	_title_widget->setScene(new QGraphicsScene());
	_title_widget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	_title_widget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	layout->addWidget( _title_widget);
	setLayout(layout);
}
LCCurveTitle::~LCCurveTitle()
{}

void LCCurveTitle::onUpdate(const LCUpdateNotifier &update_notifier)
{
	if (update_notifier.dataChangedFlag() & LCENV::CurrentWellChanged) {
		_title_widget->scene()->clear();
		QRectF scene_rect( 0, 0, width(), height() );
		_title_widget->scene()->setSceneRect(scene_rect);
		QPainterPath path(QPointF(scene_rect.left(), scene_rect.bottom()) );
		path.lineTo(QPointF(scene_rect.left(), scene_rect.bottom() - 10));
		path.lineTo(QPointF(scene_rect.right(), scene_rect.bottom() - 10));
		path.lineTo(QPointF(scene_rect.right(), scene_rect.bottom()));


		QGraphicsPathItem *data_range_item = new QGraphicsPathItem();
		data_range_item->setPath(path);
		data_range_item->setPen(QPen(Qt::red, 0) );
		_title_widget->scene()->addItem(data_range_item);
		/*
		LCLinearAxis *axis = _title_widget->axis();
		axis->setRange(curveContainer()->curveWidget()->scene()->sceneRect().left(), curveContainer()->curveWidget()->scene()->sceneRect().right());
		axis->setTick(curveContainer()->curveWidget()->minValue(), curveContainer()->curveWidget()->maxValue(), curveContainer()->curveWidget()->maxValue() - curveContainer()->curveWidget()->minValue());
		_title_widget->setRuler();
		*/
	}
}
void LCCurveTitle::optionsChanged()
{

}