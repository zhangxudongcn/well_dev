#pragma once
#include <QWidget>
class LCUpdateNotifier;
class LCSeismicTitle : public QWidget {
public:
	LCSeismicTitle(QWidget *parent = Q_NULLPTR);
	~LCSeismicTitle();
	virtual void onUpdate(const LCUpdateNotifier &update_notifier);
	virtual void optionsChanged();
};