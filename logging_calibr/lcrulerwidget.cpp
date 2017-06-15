#include "stdafx.h"

#include "lcrulerwidget.h"
#include "lcvalueaxis.h"
#include "lcdefine.h"
#include "lcupdatenotifier.h"
#include "lcdata.h"
#include "lcmainwindow.h"
#include "lcrulercontainer.h"
#include <QGraphicsTextItem>
#define DefaultRulerWidthMM 15.
LCRulerWidget::LCRulerWidget(Qt::Alignment align, QWidget *parent) 
	: LCGraphicsView(parent), _align(align), _scene(new QGraphicsScene()), _axis( nullptr )
{
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setScene(_scene);
	_axis = new LCValueAxis();
}
LCRulerWidget::~LCRulerWidget()
{
}

void LCRulerWidget::onUpdate(const LCUpdateNotifier &update_notifier)
{		
	if (_align == Qt::AlignLeft) {
		axis()->setRange( LCENV::MW->lcData()->timeMin() * 1000, LCENV::MW->lcData()->timeMax() * 1000);
		double tick_min = (int(LCENV::MW->lcData()->timeMin() * 1000 / 100)) * 100;
		double tick_max = (int(LCENV::MW->lcData()->timeMax() * 1000 / 100)) * 100;
		axis()->setTick(tick_min, tick_max, 100);
		setRuler();
	}
	if (_align == Qt::AlignRight) {
		axis()->setRange(LCENV::MW->lcData()->timeMin() * 1000, LCENV::MW->lcData()->timeMax() * 1000);
		double tick_min = (int(LCENV::MW->lcData()->timeMin() * 1000 / 100)) * 100;
		double tick_max = (int(LCENV::MW->lcData()->timeMax() * 1000 / 100)) * 100;
		axis()->setTick(tick_min, tick_max, 100);
		setRuler();
	}
}

void LCRulerWidget::optionsChanged()
{

}
void LCRulerWidget::setAxis(LCValueAxis *axis)
{
	if (axis != _axis) {
		delete _axis;
		_axis = nullptr;
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
		scene_rect.setRight( ((LCRulerContainer*)parent())->widthCM() * LCENV::PixelPerCM);
		scene_rect.setTop( _axis->rangeMin() );
		scene_rect.setBottom( _axis->rangeMax());
	}
	else {
		scene_rect.setLeft(_axis->rangeMin());
		scene_rect.setRight(_axis->rangeMax());
		scene_rect.setTop(0);
		scene_rect.setBottom(((LCRulerContainer*)parent())->widthCM() * LCENV::PixelPerCM);
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
			_scene->addLine(0, value, _scene->width() / 2, value, QPen(Qt::black, 0));
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
