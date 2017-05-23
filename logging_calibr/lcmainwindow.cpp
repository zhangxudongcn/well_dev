#include "stdafx.h"
#include "lcapplication.h"
#include "lcmainwindow.h"
#include "lcmodel.h"
#include "lcwelldata.h"
#include "lcscene.h"
#include <QFileDialog>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsScene>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLineSeries>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

QT_CHARTS_USE_NAMESPACE
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
	qDebug("file name is %s", file_name.toStdString().c_str());
	LCWellData *w_data = new LCWellData();
	w_data->loadFromLasFile(file_name);
	lcApp()->lcModel()->addWell(w_data);
}

void LCMainWindow::modelChanged()
{
	LCWellData *well_data = lcApp()->lcModel()->wellData(0);
	const QVector<LCSubLogData> &log_data = well_data->logData();

	// test scene
	_lc_scene->setSceneRect(QRectF(0, 0, 1000, 1000));
	QChart *chart = new QChart();
	qDebug( "axis is %X", chart->axisY() );
	chart->legend()->hide();
	chart->setTitle("Simple line chart example");
        QLineSeries *series = new QLineSeries();
	LCSubLogData x_data = log_data[1];
	LCSubLogData y_data = log_data[0];
	for( int index = y_data.size() - 1; index >= 0 ; index-- ) {
		if( x_data[index] != -999.2500 ) {
		    series->append( x_data[index], y_data[index] );
		} else {
		    series->append( x_data.minValue(), y_data[index] );
	        }
	}

	  chart->addSeries(series);
	  chart->resize( 400, 900 );
	  chart->createDefaultAxes();
	  chart->axisY()->setReverse( true );
	  ((QValueAxis*)chart->axisY())->setTickCount( 20 );
	  ((QValueAxis*)chart->axisY())->setMinorTickCount( 20 );
	  ((QValueAxis*)chart->axisY())->setMinorGridLineVisible( false );

    _lc_scene->addItem( chart );
}
