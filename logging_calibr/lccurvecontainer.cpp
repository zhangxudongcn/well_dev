#include "stdafx.h"
#include "lccurvecontainer.h"
#include "lccurvetitle.h"
#include "lccurvewidget.h"
#include "lcupdatenotifier.h"
#include "lcdefine.h"
#include "lcmainwindow.h"
#include <QLabel>
#include <QVBoxLayout>
LCCurveContainer::LCCurveContainer(QWidget *parent) : QWidget(parent)
{
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
	_curve_title = new LCCurveTitle(this);
	_curve_widget = new LCCurveWidget(this);
	_name_widget = new QLabel(this);
	_name_widget->setAlignment(Qt::AlignCenter);

	int curve_width_pixel = widthCM() * LCENV::PixelPerCM;
	setFixedWidth(curve_width_pixel );

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
float LCCurveContainer::widthCM() const
{
	QSettings &options = LCENV::MW->lcOptions();
	float ruler_width_cm = options.value("Curve/CurveWidth").toFloat();
	return ruler_width_cm;
}

void LCCurveContainer::setCurve(const QString &curve_name)
{
	_curve_name = curve_name;
}

void LCCurveContainer::onUpdate(const LCUpdateNotifier &update_notifier)
{
	_curve_widget->onUpdate(update_notifier);
	_name_widget->setText(_curve_name);
}

void LCCurveContainer::optionsChanged()
{

}