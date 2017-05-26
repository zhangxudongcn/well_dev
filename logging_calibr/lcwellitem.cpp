#include "lcwellitem.h"
#include "lccurveitem.h"
LCWellItem::LCWellItem(QGraphicsItem *parent, Qt::WindowFlags wFlags) : QGraphicsWidget(parent, wFlags)
{
	resize(1000, 1000);
}
LCWellItem::~LCWellItem()
{}

void LCWellItem::onUpdate(const LCUpdateNotifier &update_notifier)
{
	if (_curve_vec.size() == 0) {
		QGraphicsLinearLayout *layout = new QGraphicsLinearLayout(Qt::Horizontal, this);
	    for (int i = 0; i < 4; i++) {
			LCCurveItem *curve_item = new LCCurveItem(this);
			curve_item->setBackgroundBrush(Qt::red);
			layout->addItem(curve_item);
			_curve_vec.push_back( curve_item );
	    }
		setLayout(layout);
	}
	for (auto &item : _curve_vec) {
		item->setTitle("ABC");
		item->resize(300, 1000);

		QLineSeries *series = new QLineSeries();
		series->append(0, 6);
		series->append(2, 4);
		series->append(3, 8);
		series->append(7, 4);
		series->append(10, 5);
		*series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);
		item->addSeries(series);
		item->createDefaultAxes();
	}
	_curve_vec[0]->scroll(0, 50);
}
