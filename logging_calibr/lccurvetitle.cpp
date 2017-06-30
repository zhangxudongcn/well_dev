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