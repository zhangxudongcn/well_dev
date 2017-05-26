#include "stdafx.h"
#include "lcapplication.h"
#include "lcmainwindow.h"
#include "lcscene.h"
#include "lcupdatenotifier.h"
#include <QGraphicsView>
LCMainWindow::LCMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	_lc_scene = new LCScene();	
	_lc_scene->setObjectName(QStringLiteral("_lc_scene"));

	_lc_view = new QGraphicsView( _lc_scene, ui._central_widget);
	_lc_view->setObjectName(QStringLiteral("_lc_view"));

	ui._h_layout->addWidget(_lc_view);	

}

LCMainWindow::~LCMainWindow()
{
}

void LCMainWindow::fileOpenSlot()
{	
	onUpdate(LCUpdateNotifier());
	return;
	/*
	aiDataProject *project = lcApp()->project();
	aiDataRefer<aiDataWellGroup> well_group = (aiDataWellGroup*)project->GetItem(aiData::DT_WELL_GROUP, "WellGroup1");
	aiDataRefer<aiDataWell> well = well_group->GetWell( "F02-1" );
	qDebug("file name is %s", file_name.toStdString().c_str());
	LCWellData *w_data = new LCWellData();
	w_data->loadFromLasFile(file_name);
	lcApp()->lcModel()->addWell(w_data);
	*/
}
void LCMainWindow::onUpdate(const LCUpdateNotifier &update_notifier)
{
	_lc_scene->onUpdate(update_notifier);
}
