#include "stdafx.h"

#include "lcrulertitle.h"
#include "lcdefine.h"
#include "lcmainwindow.h"
#include "lcupdatenotifier.h"
#include <QLabel>
#include <QVBoxLayout>
LCRulerTitle::LCRulerTitle(QWidget *parent ) : QWidget(parent)
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	QSettings &options = LCENV::MW->lcOptions();
	setFixedHeight(options.value("WorkTitleHeight").toFloat() * LCENV::PixelPerCM);

	QVBoxLayout *layout = new QVBoxLayout();
	_label = new QLabel(this);
	_label->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);
	layout->addWidget(_label);
	setLayout(layout);
}
LCRulerTitle::~LCRulerTitle()
{}

void LCRulerTitle::setTitleText(const QString &text)
{
	_label->setText(text);
}

void LCRulerTitle::onUpdate(const LCUpdateNotifier &update_notifier)
{

}
void LCRulerTitle::optionsChanged()
{

}