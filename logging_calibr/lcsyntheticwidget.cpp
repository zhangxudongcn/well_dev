
#include "lcsyntheticwidget.h"
#include "lcupdatenotifier.h"

LCSyntheticWidget::LCSyntheticWidget(QWidget *parent) : LCGraphicsView(parent), _scene(new QGraphicsScene())
{
	setScene(_scene);
}
LCSyntheticWidget::~LCSyntheticWidget()
{}

void LCSyntheticWidget::onUpdate(const LCUpdateNotifier &update_notifier)
{

}

void LCSyntheticWidget::optionsChanged()
{

}