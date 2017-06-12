#pragma once
#include <QtCharts>
using namespace QtCharts;
class LCUpdateNotifier;
class LCWaveletWidget : public QChartView {
public:
	LCWaveletWidget(QWidget *parent = Q_NULLPTR);
	~LCWaveletWidget();
	virtual void onUpdate(const LCUpdateNotifier &update_notifier);
	virtual void optionsChanged();
private:
};