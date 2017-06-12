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
#include "ai_data_include.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollBar>
#include "ai_data_include.h"

LCMainWindow::LCMainWindow(QWidget *parent)
	: QMainWindow(parent), _lc_options("LC", "ZXD"), _global_label(nullptr), _well_main_widget(nullptr), _lc_data( nullptr )
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
	_lc_data = new LCData();
	if (_lc_data->setWorkData("H:/workspace/well_test/Project1.paip", "WellGroup1", "F02-1", "Survey1", "F3", 2000)) {
		LCUpdateNotifier notifier;
		notifier.setDataChangedFlag(LCENV::CurrentWellChanged);
		onUpdate(notifier);
	}
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
	_lc_options.setValue("WorkTitleHeight", 4);
	_lc_options.setValue("TimeAxisExt", 0.4); /* s */

	_lc_options.setValue("Ruler/RulerWidth", 3.);

	_lc_options.setValue("Tops/TopsWidth", 2.);

	_lc_options.setValue("Curve/CurveWidth", 3.);	
	_lc_options.setValue("Curve/CurveRangeExt", 0.05);

	_lc_options.setValue("Seismic/DrawWiggle", true);
	_lc_options.setValue("Seismic/FillWiggle", 1);
	_lc_options.setValue("Seismic/TracesPerCM", 10);
	_lc_options.setValue("Seismic/MSPerCM", 100);
	_lc_options.setValue("Seismic/MaxExtTrace", 1.5);

	_lc_options.setValue("Synthetic/TraceNum", 20);
	_lc_options.setValue("Synthetic/Gap", 2);
	_lc_options.setValue("Synthetic/Margin", 0.5);

	_lc_options.setValue("WellSeismic/TraceNum", 5);
	_lc_options.setValue("WellSeismic/Margin", 0.5);

}
