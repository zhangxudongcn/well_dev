#pragma once
#include <QWidget>
class QLabel;
class LCUpdateNotifier;
class LCGraphicsView;
class LCCurveContainer;
class LCCurveTitle : public QWidget {
public:
	LCCurveTitle(QWidget *parent = Q_NULLPTR);
	~LCCurveTitle();	
	LCCurveContainer *curveContainer() const { return (LCCurveContainer*)parent(); }

	virtual void onUpdate(const LCUpdateNotifier &update_notifier);
	virtual void optionsChanged();
private:
	LCGraphicsView *_title_widget;
};