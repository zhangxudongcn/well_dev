#pragma once
#include <QGraphicsItemGroup>
#include "lcdefine.h"
#include "lcdata.h"

class QGraphicsLineItem;
class QGraphicsTextItem;

class LCTopItem : public QGraphicsItemGroup {
public:
	LCTopItem(QGraphicsItem *parent = Q_NULLPTR);
	~LCTopItem();
	const QString &topName() const { return _top_name;  }
	void LCTopItem::setTop(const QString &top_name);

	virtual int type() const override { return LCENV::TopItem; }

private:
	QString _top_name;
	QGraphicsLineItem *_line_item;
	QGraphicsTextItem *_text_item;
};