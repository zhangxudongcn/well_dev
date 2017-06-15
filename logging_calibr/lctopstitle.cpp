#include "stdafx.h"

#include "lctopstitle.h"
#include "lcmainwindow.h"
#include "lcdefine.h"
#include <QLabel>
#include <QVBoxLayout>
LCTopsTitle::LCTopsTitle(QWidget *parent) : QWidget(parent)
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	QSettings &options = LCENV::MW->lcOptions();
	setFixedHeight( options.value( "WorkTitleHeight" ).toFloat() * LCENV::PixelPerCM );
	QVBoxLayout *layout = new QVBoxLayout();
	layout->addWidget(new QLabel("Title", this));
	setLayout(layout);
}
LCTopsTitle::~LCTopsTitle()
{}


void LCTopsTitle::onUpdate(const LCUpdateNotifier &update_notifier)
{

}
void LCTopsTitle::optionsChanged()
{

}