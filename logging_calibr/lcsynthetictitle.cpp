#include "lcsynthetictitle.h"
#include "lcupdatenotifier.h"
#include "lcdefine.h"
#include "lcmainwindow.h"
#include <QLabel>
#include <QVBoxLayout>
LCSyntheticTitle::LCSyntheticTitle(QWidget *parent) : QWidget(parent)
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	QSettings &options = LCENV::MW->lcOptions();
	setFixedHeight(options.value("WorkTitleHeight").toFloat() * LCENV::PixelPerCm);
	QVBoxLayout *layout = new QVBoxLayout();
	layout->addWidget(new QLabel("Title", this));
	setLayout(layout);
}
LCSyntheticTitle::~LCSyntheticTitle()
{}

void LCSyntheticTitle::onUpdate(const LCUpdateNotifier &update_notifier)
{

}

void LCSyntheticTitle::optionsChanged()
{

}