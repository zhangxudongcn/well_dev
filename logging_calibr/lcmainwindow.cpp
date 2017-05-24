#include "stdafx.h"
#include "lcapplication.h"
#include "lcmainwindow.h"
#include "lcmodel.h"
#include "lcwelldata.h"
#include "lcscene.h"
#include <QFileDialog>
#include <QtWidgets>
#include <ai_data_include.h>
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
	QString file_name = QFileDialog::getOpenFileName(this, tr("Open File") );
	aiDataProject *project = lcApp()->project();
	aiDataRefer<aiDataWellGroup> well_group = (aiDataWellGroup*)project->GetItem(aiData::DT_WELL_GROUP, "well_group");
	aiDataRefer<aiDataWell> well = well_group->GetWell( file_name, true );
	modelChanged();
	/*
	qDebug("file name is %s", file_name.toStdString().c_str());
	LCWellData *w_data = new LCWellData();
	w_data->loadFromLasFile(file_name);
	lcApp()->lcModel()->addWell(w_data);
	*/
}

void LCMainWindow::modelChanged()
{
	_lc_scene->modelChanged();
}
