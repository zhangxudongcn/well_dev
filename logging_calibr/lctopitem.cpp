#include "lctopitem.h"
#include "lcmainwindow.h"
#include "lcdata.h"
#include "ai_data_include.h"
#include <QGraphicsScene>

LCTopItem::LCTopItem(QGraphicsItem *parent  ) : QGraphicsItemGroup(parent), _line_item( nullptr ), _text_item( nullptr )
{

}
LCTopItem::~LCTopItem()
{

}

void LCTopItem::setTop(const QString &top_name)
{
	aiDataWell *well_data = LCENV::MW->lcData()->wellData();
	_top_name = top_name;
	aiDataWell::Top top = well_data->GetTop( top_name );
	if (_line_item != nullptr) {
		delete _line_item;
		_line_item = nullptr;
	}
	if (_text_item != nullptr) {
		delete _text_item;
		_text_item = nullptr;
	}
	float x0 = scene()->sceneRect().left();
	float y0 = top.fDepth;
	float x1 = scene()->sceneRect().right();
	float y1 = top.fDepth;
	_line_item = new QGraphicsLineItem(x0, y0, x1, y1, this);
	QPen pen(QColor(LCENV::MW->lcData()->wellGroup()->GetTopColor(_top_name)), 1);
	pen.setCosmetic(true);
	_line_item->setPen(pen);

	_text_item = new QGraphicsTextItem(_top_name, this);
	_text_item->setDefaultTextColor(QColor(LCENV::MW->lcData()->wellGroup()->GetTopColor(_top_name)));
	_text_item->setPos(x0, y0);
}
