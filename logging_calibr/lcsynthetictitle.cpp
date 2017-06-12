#include "lcsynthetictitle.h"
#include "lcupdatenotifier.h"
#include "lcdefine.h"
#include "lcmainwindow.h"
#include "lcwaveletwidget.h"
#include <QLabel>
#include <QVBoxLayout>
LCSyntheticTitle::LCSyntheticTitle(QWidget *parent) : QWidget(parent)
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	QSettings &options = LCENV::MW->lcOptions();
	setFixedHeight(options.value("WorkTitleHeight").toFloat() * LCENV::PixelPerCM);
	QVBoxLayout *layout = new QVBoxLayout();
	layout->setContentsMargins(QMargins());
	layout->setSpacing(0);
	_wavelet_widget = new LCWaveletWidget(this);
	layout->addWidget(_wavelet_widget);
	setLayout(layout);
}
LCSyntheticTitle::~LCSyntheticTitle()
{}

void LCSyntheticTitle::onUpdate(const LCUpdateNotifier &update_notifier)
{
	_wavelet_widget->onUpdate(update_notifier);
}

void LCSyntheticTitle::optionsChanged()
{

}