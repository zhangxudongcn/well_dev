#pragma once
#include "lcbaseaxis.h"
class LCLinearAxis : public LCBaseAxis {
public:
	LCLinearAxis(Qt::Alignment align) : LCBaseAxis(align), _label_index_min( 0 ), _label_index_step( 1 ) {};
	~LCLinearAxis() {};

	double tickMin() const { return _tick_min; }
	double tickMax() const { return _tick_max; }
	double tickStep() const { return _tick_step; }
	void setTick(double tick_min, double tick_max, double tick_step) {
		_tick_min = tick_min;
		_tick_max = tick_max;
		_tick_step = tick_step;
	}
	int labelIndexMin() const { return _label_index_min; }
	int labelIndexStep() const { return _label_index_step; }
	void setLabel(int label_min, int label_step) {
		_label_index_min = label_min;
		_label_index_step = label_step;
	}

	int tickNum() const override;
	double tickValue(int index) const override;
	QString tickString(int index) const override;
private:
	double _tick_min, _tick_max, _tick_step;
	int _label_index_min, _label_index_step;
};