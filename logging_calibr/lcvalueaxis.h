#pragma once
class LCValueAxis {
public:
	LCValueAxis();
	virtual ~LCValueAxis();
	double rangeMin() const { return _range_min; }
	double rangeMax() const { return _range_max; }
	void setRange(double range_min, double range_max);

	double tickMin() const { return _tick_min; }
	double tickMax() const { return _tick_max; }
	double tickStep() const { return _tick_step; }
	void setTick(double tick_min, double tick_max, double tick_step );
	double tickLenMM() const { return _tick_len_mm; }
	void setTickLenMM(double len);
	double labelMin() const { return _label_min; }
	double labelMax() const { return _label_max; }
	double labelStep() const { return _label_step; }
	void setLabel(double label_min, double label_max, double label_step);
	virtual double labelLoc(int index) const { return _label_min + _label_step * index; }

	int minorTickCount() const { return _minor_tick_count; }
	void setMinorTickCount(int count);
	double minorTickLenMM() const { return _minor_tick_len_mm;	};
	void setMinorTickLenMM(double len);
private:
	double _range_min, _range_max;
	double _tick_min, _tick_max, _tick_step;
	double _tick_len_mm;
	double _label_min, _label_max, _label_step;
	bool _depth_label;
	int _minor_tick_count;
	double _minor_tick_len_mm;
};