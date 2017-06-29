#include "stdafx.h"

#include "lcrulerwidget.h"
#include "lcvalueaxis.h"
#include "lclineardepthaxis.h"
#include "lcdefine.h"
#include "lcupdatenotifier.h"
#include "lcdata.h"
#include "lcmainwindow.h"
#include "lcrulercontainer.h"
#include <QGraphicsSimpleTextItem>
#define DefaultRulerWidthMM 15.
LCRulerWidget::LCRulerWidget(Qt::Alignment align, QWidget *parent) 
	: LCGraphicsView(parent), _align(align), _scene(new QGraphicsScene()), _axis( nullptr )
{
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setScene(_scene);
}
LCRulerWidget::~LCRulerWidget()
{
}

void LCRulerWidget::onUpdate(const LCUpdateNotifier &update_notifier)
{
	setRuler();
}

void LCRulerWidget::optionsChanged()
{

}
void LCRulerWidget::setAxis(LCLinearAxis *axis)
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
		scene_rect.setBottom(_axis->rangeMax());// set y scale
		QSettings &options = LCENV::MW->lcOptions();
		float ms_per_cm = options.value("Seismic/MSPerCM").toFloat();
		float y_scale = LCENV::PixelPerCM / ms_per_cm;
		scale(1.0, y_scale);
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
		for (int tick_index = 0; tick_index < axis()->tickNum(); tick_index++) {
			double tick_value = axis()->tickValue( tick_index );
			_scene->addLine( _scene->width() / 2, tick_value, _scene->width(), tick_value, QPen( Qt::black, 0) );
			QGraphicsSimpleTextItem *tick_item = _scene->addSimpleText( axis()->tickString(tick_index ));
			QRectF br = tick_item->boundingRect();
			tick_item->setPos( _scene->width() / 2 - br.width(), tick_value - br.height() / 2);
		}
		break;
	}
	case Qt::AlignRight: {
		for (int tick_index = 0; tick_index < axis()->tickNum(); tick_index++) {
			double tick_value = axis()->tickValue(tick_index);
			_scene->addLine(0, tick_value, _scene->width() / 2, tick_value, QPen(Qt::black, 0));
			QGraphicsSimpleTextItem *tick_item = _scene->addSimpleText(axis()->tickString(tick_index));
			QRectF br = tick_item->boundingRect();
			tick_item->setPos(_scene->width() / 2, tick_value - br.height() / 2);
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
