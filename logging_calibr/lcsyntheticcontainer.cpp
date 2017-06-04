#include "lcsyntheticcontainer.h"
#include "lcupdatenotifier.h"
#include "lcsynthetictitle.h"
#include "lcsyntheticwidget.h"
#include "lcdefine.h"
#include <QLabel>
#include <QVBoxLayout>
#define DefaultSyntheticWidthCM 5.0
LCSyntheticContainer::LCSyntheticContainer(QWidget *parent) 
	: QWidget(parent), _width_cm( DefaultSyntheticWidthCM)
{
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);	
	setFixedWidth(_width_cm * LCENV::PixelPerCm);

	_synthetic_title = new LCSyntheticTitle(this);
	_synthetic_widget = new LCSyntheticWidget(this);
	QLabel *_name_widget = new QLabel("Synthetic", this);
	_name_widget->setAlignment(Qt::AlignCenter);


	QVBoxLayout *layout = new QVBoxLayout();
	layout->setContentsMargins(QMargins());
	layout->setSpacing(0);
	layout->addWidget(_synthetic_title);
	layout->addWidget(_synthetic_widget);
	layout->addWidget(_name_widget);
	setLayout(layout);
}
LCSyntheticContainer::~LCSyntheticContainer()
{}
void LCSyntheticContainer::setWidthCM(double width)
{
	_width_cm = width;
}

void LCSyntheticContainer::onUpdate(const LCUpdateNotifier &update_notifier)
{}
void LCSyntheticContainer::optionsChanged()
{}