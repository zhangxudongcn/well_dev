#include "stdafx.h"
#include "lcxorcontainer.h"
#include "lcupdatenotifier.h"
#include "lcdefine.h"
LCXorContainer::LCXorContainer( QWidget *parent, Qt::WindowFlags f ) : QWidget( parent, f )
{
	ui.setupUi(this);
}

LCXorContainer::~LCXorContainer()
{}


void LCXorContainer::onUpdate(const LCUpdateNotifier &update_notifier)
{
	if (update_notifier.dataChangedFlag() & LCENV::CurrentWellChanged) {
	}

	if (update_notifier.dataChangedFlag() & LCENV::TimeDepthCurveChanged) {
	}
}
void LCXorContainer::optionsChanged()
{

}