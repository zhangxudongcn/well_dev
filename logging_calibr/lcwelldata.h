#pragma once
#include "lcdefine.h"
#include <QString>
#include <QList>
#include <QVector>
class LCWellDataPri;
class LCSubLogData : public QVector<double> {
public:
	double minValue() const { return _min_value; }
	double maxValue() const { return _max_value; }
	void setMinMaxValue( double null_value );
private:
	double _min_value, _max_value;
};
class LCWellData {
public:
	LCWellData();
	LCWellData(const QString &las_name);
	virtual ~LCWellData();
	double version() const;
	LC::WrapType wrapType() const;
	double startDepth() const;
	double stopDepth() const;
	double stepDepth() const;
	double nullValue() const;
	const QString &company() const;
	const QString &wellName() const;
	const QString &fieldName() const;
	const QString &location() const;
	const QString &serviceCompany() const;
	const QString &logDate() const;
	const QString &uniqueWellId() const;
	const QList<QString> &mnems() const;
	const QList<QString> &units() const;
	const QList<QString> &descs() const;
	const QVector<LCSubLogData> &logData() const;
	bool loadFromLasFile(const QString &las_name);

private:
	LCWellDataPri *_pri_data;
};
