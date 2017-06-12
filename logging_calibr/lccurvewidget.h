#pragma once
#include <QGraphicsItemGroup>
#include <QTransform>
#include "lcgraphicsview.h"
#include "lcvalueaxis.h"
class LCCurveContainer;
class LCUpdateNotifier;
class LCCurveWidget : public LCGraphicsView {
public:
	LCCurveWidget(QWidget *parent = Q_NULLPTR);
	~LCCurveWidget() {};

	LCCurveContainer *curveContainer() const { return (LCCurveContainer*)parent(); }
	const QString &curveName() const { return _curve_name;  }
	void setCurveName(const QString &name) { _curve_name = name; }

	double rangeExtPrec() const { return _range_ext_prec; }
	void setValueRangeExt(double perc);

	const QList<QPolygonF> &curves() const { return _curves; }
	void setCurves(const QList<QPolygonF> &curves);

	const QList<LCValueAxis> &vAxis() const { return _v_axis; }
	void setVertAxis(const QList<LCValueAxis> &axis);

	const QList<LCValueAxis> &hAxis() const { return _h_axis; }
	void setHoriAxis(const QList<LCValueAxis> &axis);

	virtual void onUpdate(const LCUpdateNotifier &update_notifier);
	virtual void optionsChanged();

	QTransform mapToDeviceTransform() const { return _map_to_device_matrix; }
private:
	QGraphicsScene *_scene;
	QString _curve_name;
	double _range_ext_prec;
	QList<QPolygonF> _curves;
	QList<LCValueAxis> _v_axis;
	QList<LCValueAxis> _h_axis;
	QGraphicsItemGroup *_curve_item_group;
	QGraphicsItemGroup *_v_axis_item_group;
	QGraphicsItemGroup *_h_axis_item_group;
	QTransform _map_to_device_matrix;

};
