#pragma once
#include <QWidget>
class QLabel;
class LCUpdateNotifier;
class LCRulerTitle : public QWidget {
public:
	LCRulerTitle(QWidget *parent = Q_NULLPTR);
	~LCRulerTitle();
	QLabel *titleLabel() const { return _label; }
	void setTitleText(const QString &text);

	virtual void onUpdate(const LCUpdateNotifier &update_notifier);
	virtual void optionsChanged();
private:
	QLabel *_label;
};