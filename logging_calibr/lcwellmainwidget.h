#pragma once
#include <QWidget>
class QVBoxLayout;
class QHBoxLayout;
class QLabel;
class LCRulerContainer;
class LCWorkContainer;
class LCScrollBar;
class aiDataWell;
class LCUpdateNotifier;
class LCWellMainWidget : public QWidget {
public:
	LCWellMainWidget(QWidget *parent = Q_NULLPTR);
	~LCWellMainWidget();
	LCRulerContainer *leftRuler() const { return _left_ruler; }
	LCRulerContainer *rightRuler() const { return _right_ruler; }
	LCWorkContainer *workContainer() const { return _work_container; }
	virtual void onUpdate(const LCUpdateNotifier &update_notifier);
	virtual void optionsChanged();
private:
	QVBoxLayout *_global_v_layout;
	QLabel *_global_label;

	QHBoxLayout *_ruler_layout;
	LCRulerContainer *_left_ruler;
	LCWorkContainer *_work_container;
	LCRulerContainer *_right_ruler;
	LCScrollBar *_work_h_scrollbar;
};