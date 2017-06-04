#pragma once
#include <QScrollBar>
class LCScrollBar : public QScrollBar {
public:
	LCScrollBar(QWidget *parent = Q_NULLPTR) : QScrollBar(parent) {};
	~LCScrollBar() {};
};
