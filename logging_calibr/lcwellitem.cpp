#include "lcwellitem.h"
#include "lccurveitem.h"
LCWellItem::LCWellItem(QGraphicsItem *parent, Qt::WindowFlags wFlags) : LCBaseItem(parent, wFlags)
{
}
LCWellItem::~LCWellItem()
{}

void LCWellItem::onUpdate(const LCUpdateNotifier &update_notifier)
{
	if (_curve_vec.size() == 0) {
	    for (int i = 0; i < 4; i++) {
			LCCurveItem *curve_item = new LCCurveItem(this);
			((QGraphicsLinearLayout*)layout())->addItem(curve_item);

			_curve_vec.push_back( curve_item );
	    }
	}
	for (auto &item : _curve_vec) {
		item->setTitle("ABC");
		QLineSeries *series = new QLineSeries();
		series->append(0, 6);
		series->append(2, 4);
		series->append(3, 8);
		series->append(7, 4);
		series->append(10, 5);
		item->addSeries(series);
	}
}
