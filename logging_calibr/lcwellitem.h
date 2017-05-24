#pragma once
#include <QGraphicsWidget>
class LCWellData;
class LCWellItem : public QGraphicsWidget {
public:
	LCWellItem(QGraphicsItem *parent = Q_NULLPTR, Qt::WindowFlags wFlags = Qt::WindowFlags());
	~LCWellItem();
	const LCWellData *wellData() const {
		return _well_data;
	};
	void setWellData( LCWellData *well_data);
protected:
	void setCurveItems();
private:
	LCWellData *_well_data;

};