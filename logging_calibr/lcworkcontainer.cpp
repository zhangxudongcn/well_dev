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
#include <QHBoxLayout>
#include <QResizeEvent>
#include <QScrollBar>
LCWorkContainer::LCWorkContainer(QWidget *parent) 
	: QScrollArea(parent)
{	
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	//setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	QWidget *scroll_widget = new QWidget(this);	
	scroll_widget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	_tops_container = new LCTopsContainer(scroll_widget);
	_well_container = new LCWellContainer(scroll_widget);
	_synthetic_container = new LCSyntheticContainer(scroll_widget);
	_il_seismic_container = new LCSeismicContainer(scroll_widget);
	_xl_seismic_container = new LCSeismicContainer(scroll_widget);
	QHBoxLayout *layout = new QHBoxLayout();
	layout->setContentsMargins(QMargins());
	layout->setSpacing(0);
	layout->addWidget(_tops_container);
	layout->addWidget(_well_container);
	layout->addWidget(_synthetic_container);
	layout->addWidget(_il_seismic_container);
	layout->addWidget(_xl_seismic_container);
	scroll_widget->setLayout(layout);
	setWidget(scroll_widget);
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
	width += _il_seismic_container->widthCM();
	width += _xl_seismic_container->widthCM();
	return width;
}
void LCWorkContainer::onUpdate(const LCUpdateNotifier &update_notifier)
{
	_tops_container->onUpdate(update_notifier);
	_well_container->onUpdate(update_notifier);
	_synthetic_container->onUpdate(update_notifier);
	_il_seismic_container->onUpdate(update_notifier);
	_xl_seismic_container->onUpdate(update_notifier);
	float width = scrollWidthCM();
	widget()->setFixedWidth(width * LCENV::PixelPerCM);
}

void LCWorkContainer::optionsChanged()
{

}
void LCWorkContainer::resizeEvent(QResizeEvent *event)
{
	widget()->setFixedHeight(height());
}

void LCWorkContainer::setDeviceYValue(int value)
{
	_tops_container->topsWidget()->verticalScrollBar()->setValue(value);
	_well_container->setDeviceYValue(value);
	_synthetic_container->syntheticWidget()->verticalScrollBar()->setValue(value);
	_il_seismic_container->seismicWidget()->verticalScrollBar()->setValue(value);
	_xl_seismic_container->seismicWidget()->verticalScrollBar()->setValue(value);
}