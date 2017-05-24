#include "stdafx.h"
#include "lcscene.h"
#include "lcmodel.h"
#include "lcapplication.h"
#include "lcwelldata.h"
#include <QtCharts>
#include "ai_data_include.h"

QT_CHARTS_USE_NAMESPACE
void LCScene::modelChanged()
{
	setSceneRect(QRectF(0, 0, 1000, 1000));
	aiDataProject *project = lcApp()->project();
	aiDataRefer<aiDataWellGroup> well_group = (aiDataWellGroup*)project->GetItem(aiData::DT_WELL_GROUP, "well_group");
	aiDataRefer<aiDataWell> well = well_group->GetWell( "F02-1_logs" );
	if( well == nullptr ) {}
#if 0
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
