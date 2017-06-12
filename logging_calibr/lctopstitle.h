#pragma once
#include <QWidget>
class QLabel;
class LCUpdateNotifier;
class LCTopsTitle : public QWidget {
public:
	LCTopsTitle(QWidget *parent = Q_NULLPTR);
	~LCTopsTitle();
	virtual void onUpdate(const LCUpdateNotifier &update_notifier);
	virtual void optionsChanged();
};