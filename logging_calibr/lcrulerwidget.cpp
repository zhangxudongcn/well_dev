#include "lcrulerwidget.h"
#include "lcvalueaxis.h"
#include "lcdefine.h"
#include "lcupdatenotifier.h"
#include "lcdata.h"
#include <QGraphicsTextItem>
#define DefaultRulerWidthMM 15.
LCRulerWidget::LCRulerWidget(Qt::Alignment align, QWidget *parent) : LCGraphicsView(parent), _align(align), _scene(new QGraphicsScene())
{
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setScene(_scene);
	setAxis(new LCValueAxis());
}
LCRulerWidget::~LCRulerWidget()
{
}

void LCRulerWidget::onUpdate(const LCUpdateNotifier &update_notifier)
{
	QVector<float> depth_vector = LCENV::WellData->GetWell("F0")->GetCurve("DEPTH");
	axis()->setRange(depth_vector.first(), depth_vector.back());
	double tick_min = (int(depth_vector.first() / 100) + 1) * 100;
	double tick_max = (int(depth_vector.back() / 100) ) * 100;
	axis()->setTick(tick_min, tick_max, 100);
	setRuler();
}

void LCRulerWidget::optionsChanged()
{

}
void LCRulerWidget::setAxis(LCValueAxis *axis)
{
	if (axis != _axis) {
		_axis = axis;
		setRuler();
	}
}

void LCRulerWidget::setRuler()
{
	_scene->clear();
	if (_axis == nullptr) {
		return;
	}
	QRectF scene_rect = _scene->sceneRect();
	if (_align == Qt::AlignLeft || _align == Qt::AlignRight) {
		scene_rect.setLeft(0);
		scene_rect.setRight(width());
		scene_rect.setTop( _axis->rangeMin() );
		scene_rect.setBottom( _axis->rangeMax());
	}
	else {
		scene_rect.setLeft(_axis->rangeMin());
		scene_rect.setRight(_axis->rangeMax());
		scene_rect.setTop(0);
		scene_rect.setBottom(height());
	}
	_scene->setSceneRect(scene_rect);
	switch (_align) {
	case Qt::AlignLeft: {
		for (double value = _axis->tickMin(); value <= _axis->tickMax(); value += _axis->tickStep()) {
			_scene->addLine( _scene->width() / 2, value, _scene->width(), value, QPen( Qt::black) );
			QGraphicsTextItem *tick_item = _scene->addText(QString::number(value));
			QRectF br = tick_item->boundingRect();
			tick_item->setPos( _scene->width() / 2 - br.width(), value - br.height() / 2);
		}
		break;
	}
	case Qt::AlignRight: {
		for (double value = _axis->tickMin(); value <= _axis->tickMax(); value += _axis->tickStep()) {
		_scene->addLine(0, value, _scene->width() / 2, value, QPen(Qt::black));
		QGraphicsTextItem *tick_item = _scene->addText(QString::number(value));
		QRectF br = tick_item->boundingRect();
		tick_item->setPos(_scene->width() / 2, value - br.height() / 2);
	}
		break;
	}
	case Qt::AlignTop: {
		break;
	}
	case Qt::AlignBottom: {
		break;
	}
	default: {

	}
	}
}
