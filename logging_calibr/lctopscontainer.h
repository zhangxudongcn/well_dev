#pragma once
#include <QWidget>
class LCTopsTitle;
class LCTopsWidget;
class QLabel;
class LCUpdateNotifier;
class LCTopsContainer : public QWidget {
public:
	LCTopsContainer(QWidget *parent = Q_NULLPTR);
	~LCTopsContainer();
	float widthCM() const;
	LCTopsTitle *topsTitle() const { return _tops_title; }
	LCTopsWidget *topsWidget() const { return _tops_widget; }
	QLabel *nameWidget() const { return _name_widget; }
	virtual void onUpdate(const LCUpdateNotifier &update_notifier);
	virtual void optionsChanged();
private:
	LCTopsTitle *_tops_title;
	LCTopsWidget *_tops_widget;
	QLabel *_name_widget;
};