#pragma once
#include <QWidget>
class LCUpdateNotifier;
class LCSyntheticTitle : public QWidget {
public:
	LCSyntheticTitle(QWidget *parent = Q_NULLPTR);
	~LCSyntheticTitle();
	virtual void onUpdate(const LCUpdateNotifier &update_notifier);
	virtual void optionsChanged();
};