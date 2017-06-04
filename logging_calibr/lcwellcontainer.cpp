#include "lcwellcontainer.h"
#include "lcdata.h"
#include "lcupdatenotifier.h"
#include "lccurvecontainer.h"
#include "lccurvewidget.h"
#include "lcdefine.h"
#include <QHBoxLayout>
#include <QScrollBar>

LCWellContainer::LCWellContainer(QWidget *parent) 
	: QWidget(parent), _title_height_cm(LCENV::DefaultTitleHeightCM)
{
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
}
LCWellContainer::~LCWellContainer()
{

}
double LCWellContainer::widthCM() const
{
	double width = 0.;
	for (const auto &item : _curves) {
		width += item->widthCM();
	}
	return width;
}

void LCWellContainer::setTitleHeightCM(double height)
{
	_title_height_cm = height;
}

void LCWellContainer::onUpdate(const LCUpdateNotifier &update_notifier)
{
	if (update_notifier.dataChangedFlag() | LCENV::CurrentWellChanged) {
		aiDataWell *well_data = LCENV::WellData->GetWell("F0");
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


