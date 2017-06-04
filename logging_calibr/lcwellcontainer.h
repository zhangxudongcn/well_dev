#pragma once
#include <QWidget>
class LCCurveContainer;
class QHBoxLayout;
class LCUpdateNotifier;
class LCWellContainer : public QWidget{
public:
	LCWellContainer(QWidget *parent = Q_NULLPTR);
	~LCWellContainer();	
	double widthCM() const;
	double titleHeightCM() const { return _title_height_cm; }
	void setTitleHeightCM(double height);
	QList<LCCurveContainer*> curves() const { return _curves; }
	virtual void onUpdate(const LCUpdateNotifier &update_notifier);
	virtual void optionsChanged();
	void setWell();
public slots:
	virtual void setDeviceYValue(int value);

private:
	double _title_height_cm;
	QList<LCCurveContainer*> _curves;
};