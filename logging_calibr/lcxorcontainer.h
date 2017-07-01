#pragma once
#include <QScrollArea>
#include <QWidget>
class LCUpdateNotifier;
class LCXorWidget;
class LCXorContainer : public QWidget {
public:
	LCXorContainer( QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~LCXorContainer();
	virtual void onUpdate(const LCUpdateNotifier &update_notifier);
	virtual void optionsChanged();
private:
	LCXorWidget *_lag_xor_widget;
	LCXorWidget *_rotation_xor_widget;
};