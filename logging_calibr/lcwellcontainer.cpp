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
	return options.value("CurveWidth").toFloat() * _curve_containers.size();
}


void LCWellContainer::onUpdate(const LCUpdateNotifier &update_notifier)
{
	if (update_notifier.dataChangedFlag() & LCENV::CurrentWellChanged) {
		aiDataWell *well_data = LCENV::MW->lcData()->wellData();
		// remove curve
		for (auto &curve : _curve_containers) {
			delete curve;
		}
		_curve_containers.clear();
		if (layout() != nullptr) {
			delete layout();
		}
		QHBoxLayout *layout = new QHBoxLayout();
		layout->setContentsMargins(QMargins());
		layout->setSpacing(0);

		// create curve container
		QStringList curve_names = well_data->GetCurveNames();
		for (const auto &name : curve_names) {
			if (well_data->GetCurve(name).size() > 0) { /* 只绘制系统预定义的曲线 */
				LCCurveContainer *curve_container = new LCCurveContainer();
				_curve_containers.push_back(curve_container);
				layout->addWidget(curve_container);
				curve_container->setCurve( name );
				curve_container->onUpdate(update_notifier);
			}
		}
		setLayout(layout);
	}
	if (update_notifier.dataChangedFlag() & LCENV::TimeDepthCurveChanged) {
		for (auto &well_container : _curve_containers) {
			well_container->onUpdate(update_notifier);
		}
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
	for (auto &curve : _curve_containers) {
		curve->curveWidget()->verticalScrollBar()->setValue(value);
	}
}


