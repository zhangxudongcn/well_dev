#include "lcrulercontainer.h"
#include "lcrulertitle.h"
#include "lcrulerwidget.h"
#include "lcupdatenotifier.h"
#include "lcdefine.h"
#include "lcmainwindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QScrollBar>
#include <QSize>
#define DefaultRulerWidthCM 2.0
LCRulerContainer::LCRulerContainer(Qt::Alignment align, QWidget *parent) 
	: QWidget(parent), _align( align ), _width_cm(DefaultRulerWidthCM)
{
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
	_title_widget = new LCRulerTitle(this);
	_ruler_widget = new LCRulerWidget(align, this);
	_name_widget = new QLabel("Ruler", this);

	_name_widget->setAlignment(Qt::AlignCenter);

	QSettings &options = LCENV::MW->lcOptions();
	int ruler_width_pixel = options.value("RulerWidth").toFloat() * LCENV::PixelPerCm;
	if (_ruler_widget->verticalScrollBarPolicy() != Qt::ScrollBarAlwaysOff) {
		setFixedWidth( ruler_width_pixel + 20 );
	}
	else {
		setFixedWidth(ruler_width_pixel);
	}
	QBoxLayout *layout;
	if (align == Qt::AlignLeft || align == Qt::AlignRight) {
		layout = new QVBoxLayout();
	}
	else {
		layout = new QHBoxLayout();
	}
	layout->setContentsMargins(QMargins());
	layout->setSpacing(0);
	layout->addWidget(_title_widget);
	layout->addWidget(_ruler_widget);
	layout->addWidget(_name_widget);
	setLayout(layout);
}
LCRulerContainer::~LCRulerContainer()
{
}
void LCRulerContainer::setWidthCM(double width)
{
	_width_cm = width;
}

void LCRulerContainer::onUpdate(const LCUpdateNotifier &update_notifier)
{
	_ruler_widget->onUpdate(update_notifier);
}

void LCRulerContainer::optionsChanged()
{

}