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
#include "lcxorcontainer.h"
#include "ai_data_include.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollBar>
#include "ai_data_include.h"

LCMainWindow::LCMainWindow(QWidget *parent)
	: QMainWindow(parent), _lc_options("LC", "ZXD"), _global_label(nullptr), _well_main_widget(nullptr), _lc_data(nullptr), _xor_container( nullptr )
{

	LCENV::MW = this;
	ui.setupUi(this);
	setDefaultOptions();

	_global_h_layout = new QHBoxLayout();
	_global_label = new QLabel("No Well", this);


	_global_h_layout->addWidget(_global_label);
	ui._central_widget->setLayout(_global_h_layout);
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
	// set dock workarea 
	_xor_container = new LCXorContainer();
	QDockWidget *dockWidget = new QDockWidget(tr("Correlation"), this);
	dockWidget->setAllowedAreas(Qt::RightDockWidgetArea);
	dockWidget->setWidget(_xor_container);
	addDockWidget(Qt::RightDockWidgetArea, dockWidget);

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
	if (update_notifier.dataChangedFlag() & LCENV::CurrentWellChanged) {
		setWidget();
	}
	if (_well_main_widget) {
		_well_main_widget->onUpdate(update_notifier);
	}
	if (_xor_container) {
		_xor_container->onUpdate(update_notifier);
	}
}

void LCMainWindow::optionsChanged()
{
}

void LCMainWindow::setDefaultOptions()
{
	_lc_options.setValue("GlobalTitleHeight", 1.);
	_lc_options.setValue("WorkTitleHeight", 3);
	_lc_options.setValue("TimeAxisExt", 0.4); /* s */

	_lc_options.setValue("Ruler/RulerWidth", 2.);

	_lc_options.setValue("Tops/TopsWidth", 2.);

	_lc_options.setValue("Curve/CurveWidth", 3.);	
	_lc_options.setValue("Curve/CurveRangeExt", 0.05);

	_lc_options.setValue("Seismic/DrawWiggle", true);
	_lc_options.setValue("Seismic/FillWiggle", 1);
	_lc_options.setValue("Seismic/TracesPerCM", 5);
	_lc_options.setValue("Seismic/MSPerCM", 50);
	_lc_options.setValue("Seismic/MaxExtTrace", 1.5);
	_lc_options.setValue("Seismic/Margin", 0.5);

	_lc_options.setValue("Synthetic/TraceNum", 10);
	_lc_options.setValue("Synthetic/Gap", 0.5);
	_lc_options.setValue("Synthetic/Color", 0x0);

	_lc_options.setValue("WellSeismic/ILTraceNum", 5);
	_lc_options.setValue("WellSeismic/XLTraceNum", 5);
	_lc_options.setValue("WellSeismic/Color", 0x0);
	_lc_options.setValue("AverageTrace/Color", 0xFF0000);
}
