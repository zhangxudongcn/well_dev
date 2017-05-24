#include "lcwellitem.h"
#include "lcwelldata.h"
LCWellItem::LCWellItem(QGraphicsItem *parent, Qt::WindowFlags wFlags) 
	: QGraphicsWidget(parent, wFlags), _well_data(nullptr)
{
}
LCWellItem::~LCWellItem()
{}

void LCWellItem::setWellData(LCWellData *well_data)
{
	if (_well_data != well_data) {
		_well_data = well_data;
	}
	setCurveItems();
}
void LCWellItem::setCurveItems()
{

}
