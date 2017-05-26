#include "stdafx.h"
#include "lcapplication.h"
#include "lcmainwindow.h"
#include "ai_data_include.h"
LCApplication *lcApp()
{
	return(LCApplication*)qApp;
}

LCApplication::LCApplication(int &argc, char **argv) : QApplication( argc, argv ), _lc_mainwindow( nullptr )
{
	_project = new aiDataProject();
	_project->Load("H:/workspace/well_test");
	//_project->GetItem(aiData::DT_WELL_GROUP, "well_group", true);
	_lc_mainwindow = new LCMainWindow();
	_lc_mainwindow->show();
}

LCApplication::~LCApplication()
{
}

void LCApplication::setMainWindow(LCMainWindow *mw)
{
	if (mw != _lc_mainwindow) {
		_lc_mainwindow = mw;
	}
}
void LCApplication::onUpdate(const LCUpdateNotifier &update_notifier)
{
	_lc_mainwindow->onUpdate(update_notifier);
}