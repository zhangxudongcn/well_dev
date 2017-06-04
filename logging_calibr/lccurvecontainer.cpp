#include "lccurvecontainer.h"
#include "lccurvetitle.h"
#include "lccurvewidget.h"
#include "lcupdatenotifier.h"
#include "lcdefine.h"
#include <QLabel>
#include <QVBoxLayout>
#define DefaultCurveWidthCM 3.0
LCCurveContainer::LCCurveContainer(QWidget *parent) 
	: QWidget(parent), _width_cm(DefaultCurveWidthCM)
{
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
	setFixedWidth(_width_cm * LCENV::PixelPerCm);
	_curve_title = new LCCurveTitle(this);
	_curve_widget = new LCCurveWidget(this);
	_name_widget = new QLabel(this);

	_name_widget->setAlignment(Qt::AlignCenter);

	QVBoxLayout *layout = new QVBoxLayout();
	layout->setContentsMargins(QMargins());
	layout->setSpacing(0);
	layout->addWidget(_curve_title);
	layout->addWidget(_curve_widget);
	layout->addWidget(_name_widget);
	setLayout(layout);
}
LCCurveContainer::~LCCurveContainer()
{

}
void LCCurveContainer::setCurve(const QString &curve_name)
{
	_curve_name = curve_name;
}
void LCCurveContainer::setWidthCM(double width)
{
	_width_cm = width;
}

void LCCurveContainer::onUpdate(const LCUpdateNotifier &update_notifier)
{
	_curve_widget->onUpdate(update_notifier);
	_name_widget->setText(_curve_name);
}

void LCCurveContainer::optionsChanged()
{

}