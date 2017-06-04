#pragma once
#include <QWidget>
class QLabel;
class LCRulerTitle : public QWidget {
public:
	LCRulerTitle(QWidget *parent = Q_NULLPTR);
	~LCRulerTitle();
	QLabel *titleLabel() const { return _label; }
	void setTitleText(const QString &text);
private:
	QLabel *_label;
};