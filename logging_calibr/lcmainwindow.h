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
class LCData;
class LCXorContainer;

class LCMainWindow : public QMainWindow
{
	Q_OBJECT
public:
	LCMainWindow(QWidget *parent = Q_NULLPTR);
	virtual ~LCMainWindow();
	LCWellMainWidget *wellMainWidget() const { return _well_main_widget; }
	virtual void onUpdate(const LCUpdateNotifier &update_notifier);
	virtual void optionsChanged();
	LCData *lcData() const { return _lc_data; }
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
	LCData *_lc_data;
	QSettings _lc_options;
	LCXorContainer *_xor_container;
};
