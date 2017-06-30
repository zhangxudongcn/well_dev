#pragma once
#include <QGraphicsItemGroup>
#include <QTransform>
#include <QList>
#include "lcgraphicsview.h"
#include "lcvalueaxis.h"
class LCCurveContainer;
class LCUpdateNotifier;
class LCTopItem;
class LCCurveItem;
class LCCurveWidget : public LCGraphicsView {
public:
	LCCurveWidget(QWidget *parent = Q_NULLPTR);
	~LCCurveWidget();

	LCCurveContainer *curveContainer() const { return (LCCurveContainer*)parent(); }
	const QString &curveName() const { return _curve_name;  }
	void setCurveName(const QString &name) { _curve_name = name; }

	float minValue() const { return _min_value; }
	float maxValue() const { return _max_value; }

	const QPolygonF &curvePoints() const { return _curve_points; }
	void setCurvePoints(const QPolygonF &curve_points);

	virtual void onUpdate(const LCUpdateNotifier &update_notifier);
	virtual void optionsChanged();
	QTransform mapToSceneTransform() const;
protected:
	void reset();
	void setCurve();
	void setTops();
	void mousePressEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
private:
	QGraphicsScene *_scene;
	QString _curve_name;
	float _min_value, _max_value;
	QPolygonF _curve_points;
	LCCurveItem* _curve_item;
	QList<LCTopItem*> _top_items;
	QPointF _prev_pos;
	bool _mouse_press;
};
