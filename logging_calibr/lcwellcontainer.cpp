#include "stdafx.h"
#include "lcwellcontainer.h"
#include "lcdata.h"
#include "lcupdatenotifier.h"
#include "lccurvecontainer.h"
#include "lccurvewidget.h"
#include "lcdefine.h"
#include "lcmainwindow.h"
#include "ai_data_include.h"
#include <QHBoxLayout>
#include <QScrollBar>

LCWellContainer::LCWellContainer(QWidget *parent) 
	: QWidget(parent)
{
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
}
LCWellContainer::~LCWellContainer()
{

}
float LCWellContainer::widthCM() const
{
	QSettings &options = LCENV::MW->lcOptions();
	return options.value("CurveWidth").toFloat() * _curves.size();
}


void LCWellContainer::onUpdate(const LCUpdateNotifier &update_notifier)
{
	if (update_notifier.dataChangedFlag() | LCENV::CurrentWellChanged) {
		aiDataWell *well_data = LCENV::MW->lcData()->wellData();
		// remove curve
		for (auto &curve : _curves) {
			delete curve;
		}
		_curves.clear();
		if (layout() != nullptr) {
			delete layout();
		}
		QHBoxLayout *layout = new QHBoxLayout();
		layout->setContentsMargins(QMargins());
		layout->setSpacing(0);

		// create curve container
		QStringList names = well_data->GetCurveNames();
		for (int index = 1; index < names.size(); index++) {
			LCCurveContainer *curve_container = new LCCurveContainer();
			_curves.push_back(curve_container);
			layout->addWidget(curve_container);
			curve_container->setCurve(names[index]);			
			curve_container->onUpdate(update_notifier);
		}
		setLayout(layout);
	}
}

void LCWellContainer::optionsChanged()
{

}
void LCWellContainer::setWell()
{
}

void LCWellContainer::setDeviceYValue(int value)
{
	for (auto &curve : _curves) {
		curve->curveWidget()->verticalScrollBar()->setValue(value);
	}
}


