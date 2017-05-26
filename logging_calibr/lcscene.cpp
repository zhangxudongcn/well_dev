#include "stdafx.h"
#include "lcscene.h"
#include "lcapplication.h"
#include "lcwellitem.h"

void LCScene::onUpdate(const LCUpdateNotifier &update_notifier)
{
	//setSceneRect(QRectF(0, 0, 1000, 1000));
#if 0
	QGraphicsWidget *a = new QGraphicsWidget();
	QGraphicsLinearLayout *layout = new QGraphicsLinearLayout();
	QChart *aa = new QChart();
	aa->resize(100, 100);
	aa->setBackgroundBrush(Qt::red);
	layout->addItem(aa);
	QChart *aaa = new QChart();
	aaa->setBackgroundBrush(Qt::blue);
	aaa->resize(100, 100);
	layout->addItem(aaa);
	a->setLayout(layout);
	addItem(a);
	return;
#endif
	if (_well_item == nullptr) {
		_well_item = new LCWellItem();
		addItem(_well_item);
	}
	_well_item->onUpdate(update_notifier);
	return;
#if 0
	aiDataProject *project = lcApp()->project();
	aiDataRefer<aiDataWellGroup> well_group = (aiDataWellGroup*)project->GetItem(aiData::DT_WELL_GROUP, "well_group", true);
	aiDataRefer<aiDataWell> well = well_group->GetWell( "F02-1_logs" );
	if( well == nullptr ) {}
	LCWellData *well_data = lcApp()->lcModel()->wellData(0);

	const QVector<LCSubLogData> &log_data = well_data->logData();

	// test scene
	QChart *chart = new QChart();
	qDebug("axis is %X", chart->axisY());
	chart->legend()->hide();
	chart->setTitle("We must be <b>bold</b>, very <b>bold</b>");
	QLineSeries *series = new QLineSeries();
	LCSubLogData x_data = log_data[1];
	LCSubLogData y_data = log_data[0];
	for (int index = y_data.size() - 1; index >= 0; index--) {
		if (x_data[index] != -999.2500) {
			series->append(x_data[index], y_data[index]);
		}
		else {
			series->append(x_data.minValue(), y_data[index]);
		}
	}

	chart->addSeries(series);
	chart->resize(500, 900);
	chart->createDefaultAxes();
	chart->axisY()->setReverse(true);
	((QValueAxis*)chart->axisY())->setTickCount(20);
	((QValueAxis*)chart->axisY())->setMinorTickCount(20);
	((QValueAxis*)chart->axisY())->setMinorGridLineVisible(false);

	//((QValueAxis*)chart->axisY())->hide();

	addItem(chart);
#endif
}
