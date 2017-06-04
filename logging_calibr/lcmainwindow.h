#pragma once
#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QSettings>
#include "ui_lcmainwindow.h"
class LCUpdateNotifier;
class QVBoxLayout;
class QHBoxLayout;
class QLabel;
class LCWellMainWidget;
class aiDataWell;
class LCMainWindow : public QMainWindow
{
	Q_OBJECT
public:
	LCMainWindow(QWidget *parent = Q_NULLPTR);
	virtual ~LCMainWindow();
	LCWellMainWidget *wellMainWidget() const { return _well_main_widget; }
	virtual void onUpdate(const LCUpdateNotifier &update_notifier);
	virtual void optionsChanged();
	QSettings &lcOptions() { return _lc_options; }
protected:
	void setDefaultOptions();
protected slots:
	void fileOpenSlot();
protected:
	void setWidget();
	void resetWidget();

private:
	Ui::LCMainWindowClass ui;	
	QHBoxLayout *_global_h_layout;
	QLabel *_global_label;
	LCWellMainWidget *_well_main_widget;
	aiDataWell *_well_data;
	QSettings _lc_options;
};
