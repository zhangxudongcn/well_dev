#pragma once
#include <QObject>
#include <QPointF>
class LCBaseAxis : QObject {
public:
public:
	LCBaseAxis( Qt::Alignment align ) : _align( align), _axis_pos( 0., 0. ) {};
	virtual ~LCBaseAxis() {};
	Qt::Alignment alignment() const { return _align; }

	QPointF axisPos() const { return _axis_pos; }
	virtual void setAxisPos(const QPointF &pos);

	double rangeMin() const { return _range_min; }
	double rangeMax() const { return _range_max; }
	void setRange(double range_min, double range_max);

	virtual int tickNum() const = 0;
	virtual double tickValue(int index) const = 0;

	double tickLenMM() const { return _tick_len_mm; }
	void setTickLenMM(double len);

	virtual QString tickString( int index ) const = 0;

	int minorTickCount() const { return _minor_tick_count; }
	void setMinorTickCount(int count);
	double minorTickLenMM() const { return _minor_tick_len_mm; };
	void setMinorTickLenMM(double len);
signals:
	void axisChanged();
private:
	Qt::Alignment _align;
	QPointF _axis_pos;
	double _range_min, _range_max;
	double _tick_len_mm;
	int _minor_tick_count;
	double _minor_tick_len_mm;
};