#include "stdafx.h"
#include "lcvalueaxis.h"
LCValueAxis::LCValueAxis()
{
	_range_min = 0;
	_range_max = 1000;
	_tick_min = 0;
	_tick_max = 1000;
	_tick_step = 100;
	_tick_len_mm = 3;
	_label_min = 0; 
	_label_max = 1000;
	_label_step = 100;
	_minor_tick_count = 0;
	_minor_tick_len_mm = 1;
}
LCValueAxis::~LCValueAxis()
{}
void LCValueAxis::setRange(double range_min, double range_max)
{
	_range_min = range_min;
	_range_max = range_max;
}
void LCValueAxis::setTick(double tick_min, double tick_max, double tick_step)
{
	_tick_min = tick_min;
	_tick_max = tick_max;
	_tick_step = tick_step;
}
void LCValueAxis::setTickLenMM(double len) 
{
	_tick_len_mm = len;
}

void LCValueAxis::setLabel(double label_min, double label_max, double label_step)
{
	_label_min = label_min;
	_label_max = label_max;
	_label_step = label_step;
}


void LCValueAxis::setMinorTickCount( int count )
{
	if (count != _minor_tick_count) {
		_minor_tick_count = count;
	}
}
void LCValueAxis::setMinorTickLenMM(double len)
{
	_minor_tick_len_mm = len;
}
