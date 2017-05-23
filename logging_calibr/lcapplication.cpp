#include "stdafx.h"
#include "lcapplication.h"
#include "lcmodel.h"
#include "lcmainwindow.h"
LCApplication *lcApp()
{
	return(LCApplication*)qApp;
}

LCApplication::LCApplication(int &argc, char **argv) : QApplication( argc, argv ), _lc_mainwindow( nullptr )
{
	_lc_model = new LCModel();
	_lc_mainwindow = new LCMainWindow();
	_lc_mainwindow->show();
}

LCApplication::~LCApplication()
{
	delete _lc_model;
}

void LCApplication::setMainWindow(LCMainWindow *mw)
{
	if (mw != _lc_mainwindow) {
		_lc_mainwindow = mw;
	}
}

void LCApplication::modelChanged()
{
    _lc_mainwindow->modelChanged();
}
