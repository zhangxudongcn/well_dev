#pragma once
#include <QWidget>
class QLabel;
class LCUpdateNotifier;
class LCRulerWidget;
class LCCurveTitle : public QWidget {
public:
	LCCurveTitle(QWidget *parent = Q_NULLPTR);
	~LCCurveTitle();
	virtual void onUpdate(const LCUpdateNotifier &update_notifier);
	virtual void optionsChanged();
private:
	LCRulerWidget *_ruler_widget;
};