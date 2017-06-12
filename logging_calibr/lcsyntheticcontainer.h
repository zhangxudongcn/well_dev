#pragma once
#include <QWidget>
class LCSyntheticTitle;
class LCSyntheticWidget;
class QLabel;
class LCUpdateNotifier;
class LCSyntheticContainer : public QWidget {
public:
	LCSyntheticContainer(QWidget *parent = Q_NULLPTR);
	~LCSyntheticContainer();
	float widthCM() const;
	LCSyntheticTitle *syntheticTitle() const { return _synthetic_title; }
	LCSyntheticWidget *syntheticWidget() const { return _synthetic_widget; }
	QLabel *nameWidget() const { return _name_widget; }
	virtual void onUpdate(const LCUpdateNotifier &update_notifier);
	virtual void optionsChanged();
private:
	LCSyntheticTitle *_synthetic_title;
	LCSyntheticWidget *_synthetic_widget;
	QLabel *_name_widget;

};