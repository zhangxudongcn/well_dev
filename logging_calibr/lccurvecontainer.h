#pragma once
#include <QWidget>
class LCCurveTitle;
class LCCurveWidget;
class QLabel;
class LCUpdateNotifier;
class LCCurveContainer : public QWidget {
public:
	LCCurveContainer(QWidget *parent = Q_NULLPTR);
	~LCCurveContainer();
	float widthCM() const;
	const QString &curveName() const { return _curve_name; }
	LCCurveTitle *curveTitle() const { return _curve_title; }
	LCCurveWidget *curveWidget() const { return _curve_widget; }
	QLabel *nameWidget() const { return _name_widget; }
	virtual void onUpdate(const LCUpdateNotifier &update_notifier);
	virtual void optionsChanged();
	virtual void setCurve( const QString &curve_name);
private:
	QString _curve_name;
	LCCurveTitle *_curve_title;
	LCCurveWidget *_curve_widget;
	QLabel *_name_widget;
};