#pragma once
#include <QMainWindow>
#include "ui_lcmainwindow.h"
class LCScene;
class LCUpdateNotifier;
class LCMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	LCMainWindow(QWidget *parent = Q_NULLPTR);
	virtual ~LCMainWindow();
	QGraphicsView *lcView() const;
    virtual void onUpdate( const LCUpdateNotifier &update_notifier );
protected slots:
	void fileOpenSlot();

private:
	Ui::LCMainWindowClass ui;
	LCScene *_lc_scene;
	QGraphicsView *_lc_view;
};
