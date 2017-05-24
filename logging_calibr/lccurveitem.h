#pragma once
#include <QGraphicsWidget>
class LCSubLogData;
class LCCurveItem :	public QGraphicsWidget
{
public:
	LCCurveItem(QGraphicsItem *parent = Q_NULLPTR, Qt::WindowFlags wFlags = Qt::WindowFlags());
	virtual ~LCCurveItem();
	void setCurveData( const LCSubLogData &sub_log_data);
};

