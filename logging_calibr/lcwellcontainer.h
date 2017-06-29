#pragma once
#include <QWidget>
class LCCurveContainer;
class QHBoxLayout;
class LCUpdateNotifier;
class LCWellContainer : public QWidget{
public:
	LCWellContainer(QWidget *parent = Q_NULLPTR);
	~LCWellContainer();	
	float widthCM() const;
	QList<LCCurveContainer*> curves() const { return _curve_containers; }
	virtual void onUpdate(const LCUpdateNotifier &update_notifier);
	virtual void optionsChanged();
	void setWell();
public slots:
	virtual void setDeviceYValue(int value);

private:
	QList<LCCurveContainer*> _curve_containers;
};