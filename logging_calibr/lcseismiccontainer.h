#pragma once
#include <QWidget>
class LCSeismicTitle;
class LCSeismicWidget;
class QLabel;
class LCUpdateNotifier;
class LCSeismicContainer : public QWidget {
public:
	LCSeismicContainer(QWidget *parent = Q_NULLPTR);
	~LCSeismicContainer();
	float widthCM() const;
	LCSeismicTitle *seismicTitle() const { return _seismic_title; }
	LCSeismicWidget *seismicWidget() const { return _seismic_widget; }
	QLabel *nameWidget() const { return _name_widget; }
	virtual void onUpdate(const LCUpdateNotifier &update_notifier);
	virtual void optionsChanged();
private:
	LCSeismicTitle *_seismic_title;
	LCSeismicWidget *_seismic_widget;
	QLabel *_name_widget;
};