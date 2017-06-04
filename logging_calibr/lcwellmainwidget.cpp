#include "lcwellmainwidget.h"
#include "lcupdatenotifier.h"
#include "lcapplication.h"
#include "lcmainwindow.h"
#include "lcupdatenotifier.h"
#include "lcrulercontainer.h"
#include "lcrulerwidget.h"
#include "lcworkcontainer.h"
#include "lcscrollbar.h"
#include "lcdata.h"
#include "lcupdatenotifier.h"
#include "lcdefine.h"
#include "lcrulerwidget.h"
#include "lcrulertitle.h"

LCWellMainWidget::LCWellMainWidget(QWidget *parent) : QWidget(parent) 
{

	_global_v_layout = new QVBoxLayout();
	_global_label = new QLabel(this);
	_global_label->setText("GeoEast");
	_global_v_layout->addWidget(_global_label);

	_ruler_layout = new QHBoxLayout();
	_left_ruler = new LCRulerContainer(Qt::AlignLeft, this);
	_left_ruler->titleWidget()->setTitleText("Time(ms)");
	_ruler_layout->addWidget(_left_ruler);

	_work_container = new LCWorkContainer(this);
	_ruler_layout->addWidget(_work_container);

	_right_ruler = new LCRulerContainer(Qt::AlignRight, this);
	_right_ruler->rulerWidget()->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	_right_ruler->titleWidget()->setTitleText("TVD(m)\nFrom\nSurface");

	_ruler_layout->addWidget(_right_ruler);

	_global_v_layout->addItem(_ruler_layout);

	_work_h_scrollbar = new LCScrollBar(this);
	_work_h_scrollbar->setOrientation(Qt::Horizontal);
	_global_v_layout->addWidget(_work_h_scrollbar);
	setLayout(_global_v_layout);

	//connect scrollbar signal
	connect(_right_ruler->rulerWidget()->verticalScrollBar(), &QScrollBar::valueChanged,
		_left_ruler->rulerWidget()->verticalScrollBar(), &QScrollBar::setValue);
	connect(_right_ruler->rulerWidget()->verticalScrollBar(), &QScrollBar::valueChanged,
		_work_container, &LCWorkContainer::setDeviceYValue);
}
LCWellMainWidget::~LCWellMainWidget() {}
void LCWellMainWidget::onUpdate(const LCUpdateNotifier &update_notifier)
{
	_left_ruler->onUpdate(update_notifier);
	_work_container->onUpdate(update_notifier);
	_right_ruler->onUpdate(update_notifier);

}
void LCWellMainWidget::optionsChanged()
{}
