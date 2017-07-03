#include "stdafx.h"
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
#include "lclineardepthaxis.h"

LCWellMainWidget::LCWellMainWidget(QWidget *parent) : QWidget(parent) 
{
	_global_v_layout = new QVBoxLayout();
	_global_label = new QLabel(this);

	_global_label->setText("LC");
	_global_v_layout->addWidget(_global_label);
	QSettings &options = LCENV::MW->lcOptions();
	float label_height_cm = options.value("GlobalTitleHeight").toFloat();
	_global_label->setFixedHeight(label_height_cm * LCENV::PixelPerCM);

	_ruler_layout = new QHBoxLayout();
	_left_ruler = new LCRulerContainer(Qt::AlignLeft, this);
	_left_ruler->rulerWidget()->setAxis(new LCLinearAxis(Qt::AlignLeft));
	_left_ruler->titleWidget()->setTitleText("Time(ms)");
	_ruler_layout->addWidget(_left_ruler);

	_work_container = new LCWorkContainer(this);
	_ruler_layout->addWidget(_work_container);

	_right_ruler = new LCRulerContainer(Qt::AlignRight, this);
	_right_ruler->rulerWidget()->setAxis(new LCLinearDepthAxis(Qt::AlignRight));
	_right_ruler->rulerWidget()->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	_right_ruler->titleWidget()->setTitleText("Time-Depth(m)");

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

	connect(_work_h_scrollbar, &LCScrollBar::valueChanged,
		_work_container->horizontalScrollBar(), &QScrollBar::setValue);
}
LCWellMainWidget::~LCWellMainWidget() 
{
}
void LCWellMainWidget::onUpdate(const LCUpdateNotifier &update_notifier)
{
	if (update_notifier.dataChangedFlag() & LCENV::CurrentWellChanged) {
		_left_ruler->rulerWidget()->axis()->setRange(LCENV::MW->lcData()->timeMin() * 1000, LCENV::MW->lcData()->timeMax() * 1000);
		double tick_min = (int(LCENV::MW->lcData()->timeMin() * 1000 / 100)) * 100;
		double tick_max = (int(LCENV::MW->lcData()->timeMax() * 1000 / 100)) * 100;
		_left_ruler->rulerWidget()->axis()->setTick(tick_min, tick_max, 100);
	}
	_left_ruler->onUpdate(update_notifier);
	_work_container->onUpdate(update_notifier);
	if (update_notifier.dataChangedFlag() & LCENV::CurrentWellChanged) {
		LCTimeDepthCurve time_depth_curve = LCENV::MW->lcData()->currentTimeDepthCurve();
		_right_ruler->rulerWidget()->axis()->setRange(LCENV::MW->lcData()->timeMin() * 1000, LCENV::MW->lcData()->timeMax() * 1000);
		double tick_min = (int(time_depth_curve.second.first() / 100)) * 100;
		double tick_max = (int(time_depth_curve.second.back() / 100)) * 100;
		_right_ruler->rulerWidget()->axis()->setTick(tick_min, tick_max, 100);
	}
	_right_ruler->onUpdate(update_notifier);
}
void LCWellMainWidget::optionsChanged()
{}

void LCWellMainWidget::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);
}

void LCWellMainWidget::setWorkScrollBar()
{
	int work_container_width = workContainer()->width();
	int scroll_widget_width = workContainer()->widget()->width();
	LCScrollBar *_scroll_bar = workHScrollBar();
	_scroll_bar->setMaximum(scroll_widget_width - work_container_width);
	_scroll_bar->setMinimum(0);
	_scroll_bar->setPageStep(work_container_width);
}
