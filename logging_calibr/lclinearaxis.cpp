#include "stdafx.h"
#include "lclinearaxis.h"

int LCLinearAxis::tickNum() const
{
	return (_tick_max - _tick_min) / _tick_step;
}

double LCLinearAxis::tickValue(int index) const
{
	return _tick_min + index * _tick_step;
}

QString LCLinearAxis::tickString(int index) const
{
	QString tick_str;
	if ((index - labelIndexMin()) % labelIndexStep() == 0) {
		tick_str = QString::number( tickMin() + tickStep() * index );
	}
	return tick_str;
}