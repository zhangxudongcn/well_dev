#pragma once
#include <QWidget>
#include <QtCharts>
using namespace QtCharts;
#include "ui_lcxorcontainer.h"
class LCUpdateNotifier;
class LCXorWidget;
class QSpinBox;
class QPushButton;
class LCXorContainer : public QWidget {
	Q_OBJECT
public:
	LCXorContainer(QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
	~LCXorContainer();
	virtual void onUpdate(const LCUpdateNotifier &update_notifier);
	virtual void optionsChanged();
	protected slots:
	void lagApplaySlot();
protected:
	void setLagXorChart();
private:
	Ui::LCXorContainerUi ui;
};