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
LCRulerContainer::LCRulerContainer(Qt::Alignment align, QWidget *parent) 
	: QWidget(parent), _align( align )
{
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
	_title_widget = new LCRulerTitle(this);
	_ruler_widget = new LCRulerWidget(align, this);
	_name_widget = new QLabel("Ruler", this);

	_name_widget->setAlignment(Qt::AlignCenter);

	int ruler_width_pixel = widthCM() * LCENV::PixelPerCM;
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
float LCRulerContainer::widthCM() const
{
	QSettings &options = LCENV::MW->lcOptions();
	float ruler_width_cm = options.value("Ruler/RulerWidth").toFloat();
	return ruler_width_cm;
}

void LCRulerContainer::onUpdate(const LCUpdateNotifier &update_notifier)
{
	_title_widget->onUpdate(update_notifier);
	_ruler_widget->onUpdate(update_notifier);
}

void LCRulerContainer::optionsChanged()
{

}