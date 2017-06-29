#include "stdafx.h"
#include "lccurvetitle.h"
#include "lcmainwindow.h"
#include "lcrulerwidget.h"
#include "lcdefine.h"
#include "lcupdatenotifier.h"
#include <QLabel>
#include <QVBoxLayout>
LCCurveTitle::LCCurveTitle(QWidget *parent) : QWidget(parent)
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	QSettings &options = LCENV::MW->lcOptions();
	setFixedHeight( options.value( "WorkTitleHeight" ).toFloat() * LCENV::PixelPerCM );
	QVBoxLayout *layout = new QVBoxLayout();
	_ruler_widget = new LCRulerWidget(Qt::AlignTop, this);
	layout->addWidget( _ruler_widget);
	setLayout(layout);
}
LCCurveTitle::~LCCurveTitle()
{}


void LCCurveTitle::onUpdate(const LCUpdateNotifier &update_notifier)
{
	if (update_notifier.dataChangedFlag() & LCENV::CurrentWellChanged) {

	}
}
void LCCurveTitle::optionsChanged()
{

}