#pragma once
#include <QWidget>
class LCRulerTitle;
class LCRulerWidget;
class QLabel;
class LCUpdateNotifier;
class LCRulerContainer : public QWidget {
public:
	LCRulerContainer(Qt::Alignment align, QWidget *parent = Q_NULLPTR);
	~LCRulerContainer();
	Qt::Alignment alignment() const { return _align; }

	float widthCM() const;
	LCRulerTitle *titleWidget() const { return _title_widget; }
	LCRulerWidget *rulerWidget() const { return _ruler_widget; }
	QLabel *nameWidget() const { return _name_widget; }

	virtual void onUpdate(const LCUpdateNotifier &update_notifier);
	virtual void optionsChanged();
private:
	Qt::Alignment _align;
	double _width_cm;
	LCRulerTitle *_title_widget;
	LCRulerWidget *_ruler_widget;
	QLabel *_name_widget;
};