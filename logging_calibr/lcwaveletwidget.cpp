#include "stdafx.h"
#include <lcwaveletwidget.h>
#include "lcalgorithm.h"

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
	QVector<float> aaa = rickerWavelet(200, 0.001, 50);
	QLineSeries *series = new QLineSeries();
	int index = -100;
	for (const auto &item : aaa) {
		series->append(index++, item);
	}
	QChart *chart = this->chart();
	chart->legend()->hide();
	chart->addSeries(series);
	chart->createDefaultAxes();
	QRectF scene_rect = scene()->sceneRect();
	QTransform t = transform();
	QMatrix m = matrix();
	int a = 10;
	//scale(0.5, 0.5);
	//chart->setTitle("Simple line chart example");
}
void LCWaveletWidget::optionsChanged()
{

}