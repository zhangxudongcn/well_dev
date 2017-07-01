#include "stdafx.h"
#include "lcxorcontainer.h"
#include "lcxorwidget.h"
LCXorContainer::LCXorContainer( QWidget *parent, Qt::WindowFlags f ) : QWidget( parent, f )
{
	_lag_xor_widget = new LCXorWidget(this);
	_rotation_xor_widget = new LCXorWidget(this);
}

LCXorContainer::~LCXorContainer()
{}


void LCXorContainer::onUpdate(const LCUpdateNotifier &update_notifier)
{

}
void LCXorContainer::optionsChanged()
{

}