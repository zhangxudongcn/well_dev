#pragma once
#include <QtWidgets/QApplication>
class LCModel;
class LCMainWindow;
class aiDataProject;
class LCUpdateNotifier;
class LCApplication : public QApplication
{
public:
	LCApplication( int &argc, char **argv);
	virtual ~LCApplication();
	aiDataProject *project() const {		return _project;	};
	LCMainWindow *lcMainWindow() const { return _lc_mainwindow; }
	void setMainWindow(LCMainWindow *mw);
	virtual void onUpdate(const LCUpdateNotifier &update_notifier);
private:
	aiDataProject *_project;
	LCMainWindow *_lc_mainwindow;
}; 
extern LCApplication *lcApp();


