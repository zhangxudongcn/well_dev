#include "stdafx.h"
#include "lccurvetitle.h"
#include "lcmainwindow.h"
#include "lcdefine.h"
#include <QLabel>
#include <QVBoxLayout>
LCCurveTitle::LCCurveTitle(QWidget *parent) : QWidget(parent)
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	QSettings &options = LCENV::MW->lcOptions();
	setFixedHeight( options.value( "WorkTitleHeight" ).toFloat() * LCENV::PixelPerCM );
	QVBoxLayout *layout = new QVBoxLayout();
	layout->addWidget(new QLabel("Title", this));
	setLayout(layout);
}
LCCurveTitle::~LCCurveTitle()
{}