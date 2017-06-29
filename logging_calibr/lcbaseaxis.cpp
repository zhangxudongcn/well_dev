#include "stdafx.h"
#include "lcbaseaxis.h"

void LCBaseAxis::setAxisPos(const QPointF &pos)
{
	_axis_pos = pos;
}

void LCBaseAxis::setRange(double range_min, double range_max)
{
	_range_min = range_min;
	_range_max = range_max;
}

void LCBaseAxis::setTickLenMM(double len)
{
	_tick_len_mm = len;
}

void LCBaseAxis::setMinorTickCount(int count)
{
	_minor_tick_count = count;
}

void LCBaseAxis::setMinorTickLenMM(double len)
{
	_minor_tick_count = len;
}