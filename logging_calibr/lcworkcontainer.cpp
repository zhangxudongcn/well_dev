#include "stdafx.h"
#include "lcworkcontainer.h"
#include "lctopscontainer.h"
#include "lctopswidget.h"
#include "lcwellcontainer.h"
#include "lcsyntheticcontainer.h"
#include "lcsyntheticwidget.h"
#include "lcseismiccontainer.h"
#include "lcseismicwidget.h"
#include "lcupdatenotifier.h"
#include "lcdefine.h"
#include "lcmainwindow.h"
#include "lcwellmainwidget.h"
#include <QHBoxLayout>
#include <QResizeEvent>
#include <QScrollBar>
LCWorkContainer::LCWorkContainer(QWidget *parent) 
	: QScrollArea(parent)
{	
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	QWidget *scroll_widget = new QWidget(this);	
	scroll_widget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	_tops_container = new LCTopsContainer(scroll_widget);
	_well_container = new LCWellContainer(scroll_widget);
	_synthetic_container = new LCSyntheticContainer(scroll_widget);
	_seismic_container = new LCSeismicContainer(scroll_widget);
	QHBoxLayout *layout = new QHBoxLayout();
	layout->setContentsMargins(QMargins());
	layout->setSpacing(0);
	layout->addWidget(_tops_container);
	layout->addWidget(_well_container);
	layout->addWidget(_synthetic_container);
	layout->addWidget(_seismic_container);
	scroll_widget->setLayout(layout);
	setWidget(scroll_widget);
	widget()->installEventFilter(this);
}
LCWorkContainer::~LCWorkContainer()
{

}
float LCWorkContainer::scrollWidthCM() const
{
	double width = 0.;
	width += _tops_container->widthCM();
	width += _well_container->widthCM();
	width += _synthetic_container->widthCM();
	width += _seismic_container->widthCM();
	return width;
}
void LCWorkContainer::onUpdate(const LCUpdateNotifier &update_notifier)
{
	_tops_container->onUpdate(update_notifier);
	_well_container->onUpdate(update_notifier);
	_synthetic_container->onUpdate(update_notifier);
	_seismic_container->onUpdate(update_notifier);
	float width = scrollWidthCM();
	widget()->setFixedWidth(width * LCENV::PixelPerCM);
}

void LCWorkContainer::optionsChanged()
{

}
void LCWorkContainer::resizeEvent(QResizeEvent *event)
{
	widget()->setFixedHeight(height());
	LCENV::MW->wellMainWidget()->setWorkScrollBar();
}

void LCWorkContainer::setDeviceYValue(int value)
{
	_tops_container->topsWidget()->verticalScrollBar()->setValue(value);
	_well_container->setDeviceYValue(value);
	_synthetic_container->syntheticWidget()->verticalScrollBar()->setValue(value);
	_seismic_container->seismicWidget()->verticalScrollBar()->setValue(value);
}

bool LCWorkContainer::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::Resize && obj == widget()) {
		LCENV::MW->wellMainWidget()->setWorkScrollBar();
	}
	return QObject::eventFilter(obj, event);
}
