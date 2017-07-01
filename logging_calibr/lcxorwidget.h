#pragma once
#include <QtCharts>
using namespace QtCharts;

class LCXorWidget : public QChartView {
public:
	LCXorWidget(QWidget *parent = Q_NULLPTR);
	~LCXorWidget();
};