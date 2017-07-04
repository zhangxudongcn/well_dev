#include "stdafx.h"
#include "lcxorcontainer.h"
#include "lcupdatenotifier.h"
#include "lcdefine.h"
#include "lcmainwindow.h"
#include "lcdata.h"
LCXorContainer::LCXorContainer( QWidget *parent, Qt::WindowFlags f ) : QWidget( parent, f )
{
	ui.setupUi(this);
}

LCXorContainer::~LCXorContainer()
{}


void LCXorContainer::onUpdate(const LCUpdateNotifier &update_notifier)
{
	if (update_notifier.dataChangedFlag() & LCENV::CurrentWellChanged) {
		setLagXorChart();
	}
}
void LCXorContainer::optionsChanged()
{

}

void LCXorContainer::lagApplaySlot()
{
	setLagXorChart();
}

void LCXorContainer::setLagXorChart()
{
	QChart *chart = ui._lag_xor_chartview->chart();
	if (chart != nullptr) {
		delete chart;
	}
	ui._lag_xor_chartview->setChart(new QChart());
	QSettings &options = LCENV::MW->lcOptions();

	int il_num = options.value("WellSeismic/ILTraceNum").toInt();
	int xl_num = options.value("WellSeismic/XLTraceNum").toInt();
	QVector<QPair<QVector<float>, QVector<float>>> all_trace_data = LCENV::MW->lcData()->wellSeismic(il_num, xl_num);
}

