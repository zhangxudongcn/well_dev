#pragma once
#include <QtWidgets/QApplication>
class LCModel;
class LCMainWindow;
class LCUpdateNotifier;
class LCApplication : public QApplication
{
public:
	LCApplication( int &argc, char **argv);
	virtual ~LCApplication();
	LCMainWindow *lcMainWindow() const { return _lc_mainwindow; }
	void setMainWindow(LCMainWindow *mw);
	virtual void onUpdate(const LCUpdateNotifier &update_notifier);
private:
	LCMainWindow *_lc_mainwindow;
}; 
extern LCApplication *lcApp();


