#include "stdafx.h"
#include "lcapplication.h"
#include "lcmainwindow.h"
#include "lcupdatenotifier.h"
#include "lcrulercontainer.h"
#include "lcrulerwidget.h"
#include "lcworkcontainer.h"
#include "lcscrollbar.h"
#include "lcdata.h"
#include "lcupdatenotifier.h"
#include "lcdefine.h"
#include "lcrulerwidget.h"
#include "lcrulertitle.h"
#include "lcwellmainwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollBar>
LCMainWindow::LCMainWindow(QWidget *parent)
	: QMainWindow(parent), _lc_options("LC", "ZXD"), _global_label(nullptr), _well_main_widget(nullptr)
{
	LCENV::MW = this;
	ui.setupUi(this);
	_global_h_layout = new QHBoxLayout();		
	_global_label = new QLabel("No Well", this);
	_global_h_layout->addWidget(_global_label);
	ui._central_widget->setLayout(_global_h_layout);
	setDefaultOptions();
}

LCMainWindow::~LCMainWindow()
{
}
void LCMainWindow::setWidget()
{
	if (_global_label != nullptr) {
		_global_h_layout->removeWidget(_global_label);
		_global_label->hide();
	}
	if (_well_main_widget != nullptr) {
		_global_h_layout->removeWidget(_well_main_widget);
		delete _well_main_widget;
		_well_main_widget = nullptr;
	}
	_well_main_widget = new LCWellMainWidget(this);
	_global_h_layout->addWidget(_well_main_widget);
}
void LCMainWindow::resetWidget()
{
	if (_well_main_widget != nullptr) {
		_global_h_layout->removeWidget(_well_main_widget);
		delete _well_main_widget;
		_well_main_widget = nullptr;
	}
	_global_h_layout->addWidget(_global_label);
	_global_label->show();
}

void LCMainWindow::fileOpenSlot()
{	
	aiDataWellGroup well_group;
	_well_data = well_group.GetWell("well");
	LCUpdateNotifier notifier;
	notifier.setDataChangedFlag(LCENV::CurrentWellChanged);
	onUpdate( notifier );
	return;
}
void LCMainWindow::onUpdate(const LCUpdateNotifier &update_notifier)
{
	if (update_notifier.dataChangedFlag() | LCENV::CurrentWellChanged) {
		setWidget();
	}
	if (_well_main_widget) {
		_well_main_widget->onUpdate(update_notifier);
	}
}
void LCMainWindow::optionsChanged()
{
}
void LCMainWindow::setDefaultOptions()
{
	_lc_options.setValue("GlobalTitleHeight", 2.);
	_lc_options.setValue("WorkTitleHeight", 2.5);
	_lc_options.setValue("RulerWidth", 3.);
	_lc_options.setValue("CurveWidth", 3.);
}
