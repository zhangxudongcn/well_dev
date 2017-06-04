#include "lcseismiccontainer.h"
#include "lcupdatenotifier.h"
#include "lcseismictitle.h"
#include "lcseismicwidget.h"
#include "lcdefine.h"
#include <QLabel>
#include <QVBoxLayout>
#define DefaultSeismicWidthCM 3.0
LCSeismicContainer::LCSeismicContainer(QWidget *parent ) 
	: QWidget(parent), _width_cm( DefaultSeismicWidthCM)
{
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
	setFixedWidth(_width_cm * LCENV::PixelPerCm);
	LCSeismicTitle *_seismic_title = new LCSeismicTitle(this);
	LCSeismicWidget *_seismic_widget = new LCSeismicWidget(this);
	QLabel *_name_widget = new QLabel("Seismic", this);
	_name_widget->setAlignment(Qt::AlignCenter);


	QVBoxLayout *layout = new QVBoxLayout();
	layout->setContentsMargins(QMargins());
	layout->setSpacing(0);
	layout->addWidget(_seismic_title);
	layout->addWidget(_seismic_widget);
	layout->addWidget(_name_widget);
	setLayout(layout);
}
LCSeismicContainer::~LCSeismicContainer()
{}

double LCSeismicContainer::widthCM() const
{ 
	return _width_cm; 
}

void LCSeismicContainer::setWidthCM(double width)
{
	_width_cm = width;
}

void LCSeismicContainer::onUpdate(const LCUpdateNotifier &update_notifier)
{
	return;
	_seismic_title->onUpdate(update_notifier);
	_seismic_widget->onUpdate(update_notifier);
}
void LCSeismicContainer::optionsChanged()
{}