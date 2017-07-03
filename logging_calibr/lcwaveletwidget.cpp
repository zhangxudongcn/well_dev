#include "stdafx.h"
#include <lcwaveletwidget.h>
#include <math.h>
#include "lcdefine.h"
#include "lcmainwindow.h"
#include "lcdata.h"
#include "lcalgorithm.h"
#include "lcupdatenotifier.h"

LCWaveletWidget::LCWaveletWidget(QWidget *parent /* = Q_NULLPTR */)
	: QChartView(new QChart(), parent)
{
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	chart()->setMargins(QMargins());
}

LCWaveletWidget::~LCWaveletWidget()
{

}

void LCWaveletWidget::onUpdate(const LCUpdateNotifier &update_notifier)
{
	if (update_notifier.dataChangedFlag() & LCENV::CurrentWellChanged || update_notifier.dataChangedFlag() & LCENV::WaveletChanged ) {
		QChart *new_chart = new QChart();
		new_chart->setMargins(QMargins());
		QChart *old_chart = chart();
		setChart(new_chart);
		delete old_chart;

		LCWavelet wavelet = LCENV::MW->lcData()->currentWavelet();
		QLineSeries *series = new QLineSeries();
		QVector<float> time = wavelet.first;
		QVector<float> value = wavelet.second;
		for (int index = 0; index < time.size(); index++) {
			series->append(time[index] * 1000, value[index]);
		}
		QChart *chart = this->chart();
		chart->legend()->hide();
		chart->addSeries(series);
		chart->createDefaultAxes();
		QRectF scene_rect = scene()->sceneRect();
		QTransform t = transform();
		QMatrix m = matrix();
		chart->setTitle( wavelet.desc());
	}
}
void LCWaveletWidget::optionsChanged()
{

}