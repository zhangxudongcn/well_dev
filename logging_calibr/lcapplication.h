#pragma once
#include <QtWidgets/QApplication>
class LCModel;
class LCMainWindow;
class LCApplication : public QApplication
{
public:
	LCApplication( int &argc, char **argv);
	virtual ~LCApplication();
	LCModel *lcModel() const {		return _lc_model;	};
	LCMainWindow *lcMainWindow() const { return _lc_mainwindow; }
	void setMainWindow(LCMainWindow *mw);
    virtual void modelChanged();
private:
	LCModel *_lc_model;
	LCMainWindow *_lc_mainwindow;
}; 
extern LCApplication *lcApp();


