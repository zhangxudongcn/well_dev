#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_lcmainwindow.h"
class QGraphicsView;
class LCScene;
class LCMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	LCMainWindow(QWidget *parent = Q_NULLPTR);
	virtual ~LCMainWindow();
	QGraphicsView *lcView() const;
    virtual void modelChanged();
protected slots:
	void fileOpenSlot();

private:
	Ui::LCMainWindowClass ui;
	LCScene *_lc_scene;
	QGraphicsView *_lc_view;
};
